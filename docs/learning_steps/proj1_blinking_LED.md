# Project 1: Blinking LED and UART Logs

## Goal

Build a minimal STM32F103C8 application that toggles PC13 once per second and
prints the pin state through USART1. Run the same ELF in Wokwi and on a physical
Blue Pill.

## Concepts

- STM32Cube project structure
- GPIO output
- USART transmit
- HAL initialization and SysTick
- Building an ELF
- Wokwi simulation
- DAPLink flashing and source debugging

## Hardware and Wokwi Parts

- STM32F103C8 Blue Pill
- LED on PC13
- USART1 on PA9/PA10
- Wokwi serial monitor
- Wokwi logic analyzer

## CubeMX Configuration

1. Select STM32F103C8Tx.
2. Set PC13 to `GPIO_Output`.
3. Enable USART1 in asynchronous mode at 115200 baud, 8 data bits, no parity,
	 and one stop bit.
4. Set **System Core > SYS > Debug** to **Serial Wire**.
5. Keep the reset-default 8 MHz HSI clock for this project.
6. Generate code for STM32CubeIDE.

## Firmware Steps

1. Call `HAL_Init()`.
2. Initialize GPIO and USART1.
3. In the main loop, toggle PC13.
4. Format the current pin state into a small fixed-size buffer.
5. Send the buffer with `HAL_UART_Transmit()`.
6. Delay for 1000 ms.

Core loop:

```c
while (1)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

	char message[48];
	snprintf(message, sizeof(message),
					 "Pin PC13 state: %d\r\n",
					 HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));

	HAL_UART_Transmit(&huart1, (uint8_t *)message,
										strlen(message), HAL_MAX_DELAY);
	HAL_Delay(1000);
}
```

## Build

From the repository root:

```sh
make -C blue_cube_proj/bluepill_demo/Debug all
```

Expected ELF:

```text
blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf
```

## Wokwi Verification

1. Select `sim/wokwi/stm32f103/wokwi.toml` as the Wokwi configuration.
2. Start the simulator.
3. Confirm the LED changes state once per second.
4. Confirm the terminal prints alternating PC13 states.
5. Stop the simulator to save the VCD capture.
6. Open `wokwi-stm32-signals.vcd` in a waveform viewer and inspect `LED` and
	 `UART_TX`.

## Hardware Verification

1. Connect SWDIO, SWCLK, GND, VTref, and nRESET from DAPLink to the Blue Pill.
2. Build the firmware.
3. Select **Debug Blue Pill (DAPLink / pyOCD)** in VS Code.
4. Press `F5` and stop at `main`.
5. Set a breakpoint on `HAL_GPIO_TogglePin()`.
6. Continue and inspect the pin state and message buffer.

## Completion Checklist

- [x] Firmware builds without errors.
- [x] Wokwi LED toggles every second.
- [x] UART terminal prints once per second.
- [x] VCD file contains LED and UART transitions.
- [x] DAPLink flashes the same ELF to hardware.
- [x] VS Code stops at a breakpoint and displays local variables.

## Experiment

Change the delay to 250 ms. Predict the LED frequency before running the
simulation, then confirm it from VCD timestamps.

## Next Project

Continue with [Project 2: Button Input and Debouncing](proj2_button_debounce.md).
