# Lessons Learned

This document records the main problems encountered while migrating the STM32F103 firmware from Arduino C++ to native C with STM32Cube HAL. It also explains why the same ELF behaved differently in Renode and Wokwi.

## 1. Arduino hid board initialization

The Arduino framework supplied several pieces of runtime infrastructure automatically:

- MCU startup and clock initialization
- GPIO and UART wrappers
- SysTick interrupt handling
- The `setup()` and `loop()` runtime

After changing to STM32Cube HAL, the application became responsible for the hardware-facing initialization and interrupt handlers. A successful build therefore did not guarantee that delays, UART, and GPIO would work at runtime.

The native C entry point now calls `HAL_Init()`, configures GPIO and USART1 explicitly, and then enters a normal `while (1)` loop.

## 2. `HAL_Delay()` stopped after the first message

### Symptom

Renode printed the startup text and first LED state, then produced no more output:

```text
Hello from STM32F103 C Firmware!
sum(10, 32) = 42
Blink STM32 loop executed. Pin PC13 state: 1
```

This showed that startup, GPIO, UART, and `sum()` were working. Execution stopped at the first `HAL_Delay(1000)`.

### Cause

`HAL_Delay()` waits for the HAL millisecond counter to advance. The counter is incremented by `HAL_IncTick()`, normally called from the SysTick interrupt handler.

STM32Cube's startup file provides only a weak default interrupt handler. Because the application did not define `SysTick_Handler()`, the HAL tick never advanced and `HAL_Delay()` waited forever.

### Solution

Define the handler in the application:

```c
void SysTick_Handler(void)
{
    HAL_IncTick();
}
```

This fixed the stalled loop in both Renode and Wokwi.

### Lesson

When firmware reaches the first delay and then freezes, inspect the system tick before investigating UART or GPIO. Framework migration often removes interrupt handlers that were previously supplied automatically.

## 3. Renode delays were nine times too fast

### Symptom

After fixing SysTick, `HAL_Delay(1000)` completed in approximately 111 ms of virtual time:

```text
virt: 0.11s  state: 0
virt: 0.22s  state: 1
virt: 0.33s  state: 0
```

### Cause

The firmware uses the STM32F103 reset-default 8 MHz HSI system clock. Renode's built-in `stm32f103.repl` platform configures its NVIC/SysTick model for 72 MHz.

The firmware loaded a SysTick reload value calculated for 8 MHz, but Renode consumed it at 72 MHz:

$$
1000\text{ ms} \times \frac{8\text{ MHz}}{72\text{ MHz}} \approx 111\text{ ms}
$$

### Solution

Set Renode's writable NVIC frequency to match the firmware clock in `blue_pill.resc`:

```renode
nvic Frequency 8000000
```

The resulting UART timestamps are one virtual second apart.

### Lesson

A simulator's peripheral clock configuration must agree with the clock assumptions compiled into the firmware. Correct code can have incorrect timing when the simulated SysTick frequency and `SystemCoreClock` disagree.

## 4. Explicit clock configuration prevented Wokwi startup

### Symptom

The native C firmware worked in Renode but initially produced no UART output and no blinking in Wokwi.

### Previous implementation

The application called `HAL_RCC_OscConfig()` and `HAL_RCC_ClockConfig()` to select HSI at 8 MHz, even though this was already the reset state.

Both HAL functions inspect and poll RCC status bits. On failure, the application entered an infinite loop before GPIO and UART initialization. This made the failure appear as a completely dead firmware image.

### Why removing `configure_system_clock()` is valid

On STM32F103 reset:

- HSI is enabled.
- HSI is selected as the system clock.
- The system clock is 8 MHz.
- AHB and APB prescalers are set to division by one.

Before `main()`, STM32Cube's startup code calls `SystemInit()`. The CMSIS `SystemCoreClock` state therefore starts consistently at 8 MHz. `HAL_Init()` can configure SysTick using that value without switching clocks again.

The removed function was not increasing the clock or selecting a different source. It was redundantly writing the current reset configuration. Removing it reduced the number of RCC registers the simulator needed to model and eliminated pre-UART failure paths.

This does not mean clock configuration should always be omitted. It is appropriate while the firmware intentionally uses the reset-default 8 MHz HSI clock. If the project later needs 72 MHz, USB, or precise peripheral clocks, it should add a deliberate HSE/PLL configuration and validate that configuration in hardware and both simulators.

### Lesson

Do not configure clocks merely because generated examples contain a clock function. Define the clock required by the application, and avoid reprogramming the reset state when no change is needed. Simulator models are often less complete around oscillator-ready and clock-switch status behavior.

## 5. The Wokwi LED was wired to the wrong pin

### Symptom

The application drove PC13, but the external LED in `diagram.json` was connected to PB9.

### Solution

Connect the LED to the pin used by both C and Rust firmware:

```json
["stm32:C13", "led1:A", "green", []]
```

USART1 remains connected through PA9 and PA10:

- PA9, MCU TX, connects to serial monitor RX.
- PA10, MCU RX, connects to serial monitor TX.

### Lesson

Serial log messages that say an LED state changed only prove that the firmware executed the GPIO call. They do not prove that the simulator diagram is connected to that GPIO.

## 6. PlatformIO toolchain selection on ARM64

The STM32 platform's default STM32Cube toolchain constraint requested an obsolete package range that was unavailable for this development container. An ARM GCC 12 package was already installed and supported by the current platform.

The STM32 environment therefore pins it explicitly:

```ini
platform_packages =
    platformio/toolchain-gccarmnoneeabi@~1.120301.0
```

### Lesson

A package-resolution failure is not necessarily a compiler or source-code failure. Inspect the platform's package constraints and the packages already available for the host architecture.

## 7. Keep Unity out of production dependencies

Adding Unity to `lib_deps` caused it to be compiled into normal firmware builds. Its custom configuration was intended only for target tests, so production compilation then depended on a test-only header.

The solution was to let PlatformIO inject Unity for `pio test` and keep `unity_config.h` under the test tree. Host tests were moved outside PlatformIO's embedded test discovery directory.

### Lesson

Separate production libraries, embedded target tests, and host tests. Test framework configuration should not affect the production ELF.

## Debugging approach that worked

The useful sequence was:

1. Find the last observable event in UART logs.
2. Identify the next operation in source code.
3. Form a narrow hypothesis about that operation.
4. Make one small change.
5. Rebuild immediately.
6. Run Renode for a fixed amount of virtual time.
7. Compare virtual timestamps, not only host timestamps.
8. Verify the simulator wiring independently from firmware behavior.

The critical clue was that the first blink message appeared. That ruled out ELF loading, reset vectors, UART initialization, and most GPIO setup, and pointed directly to `HAL_Delay()` and SysTick.

## Current clock contract

The project currently assumes:

| Component | Frequency |
| --- | ---: |
| STM32F103 firmware system clock | 8 MHz HSI |
| HAL `SystemCoreClock` | 8 MHz |
| Wokwi STM32 execution | Reset-default 8 MHz HSI |
| Renode NVIC/SysTick override | 8 MHz |

Keeping this contract explicit prevents timing regressions. Any future change to 72 MHz must update firmware clock initialization and the corresponding simulator configuration together.
