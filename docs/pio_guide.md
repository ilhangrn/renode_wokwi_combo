# PlatformIO Guide

This project uses [PlatformIO Core](https://platformio.org/install/cli) to build the C/Arduino firmware for the ESP32-C3 and STM32F103 Blue Pill.

## Environments

The active environments are defined in [firmware-c/platformio.ini](firmware-c/platformio.ini):

```ini
[platformio]
default_envs = esp32-c3-devkitm-1, stm32f103_bluepill

[env:esp32-c3-devkitm-1]
platform = espressif32
board = esp32-c3-devkitm-1
framework = arduino
monitor_speed = 115200
build_unflags = -Os
build_flags = -Og -g3
lib_deps =
    throwtheswitch/Unity@^2.5.2
src_filter = +<*> -<main_stm32f103.cpp>

[env:stm32f103_bluepill]
platform = ststm32
board = bluepill_f103c8
framework = arduino
monitor_speed = 115200
build_flags = -Og -g3
lib_deps =
    throwtheswitch/Unity@^2.5.2
src_filter = +<*> -<main_esp32c3.cpp>
```

- `esp32-c3-devkitm-1`: ESP32-C3-DevKitM-1 (RISC-V, 160 MHz, 320 KB RAM, 4 MB flash)
- `stm32f103_bluepill`: STM32F103C8 Blue Pill (ARM Cortex-M3, 72 MHz, 20 KB RAM, 64 KB flash)
- `build_flags`: `-Og -g3` keeps debug symbols and a debug-friendly optimization level.
- `lib_deps`: Unity test framework for target-side tests.
- `src_filter`: selects the board-specific `main_*.cpp` file for each environment.

## Build the C firmware

Build both environments:

```bash
cd firmware-c
pio run
```

Build only the ESP32-C3:

```bash
cd firmware-c
pio run -e esp32-c3-devkitm-1
```

Build only the STM32F103 Blue Pill:

```bash
cd firmware-c
pio run -e stm32f103_bluepill
```

The generated ELFs are written to:

```
firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
firmware-c/.pio/build/stm32f103_bluepill/firmware.elf
```

To force a clean rebuild:

```bash
pio run -t clean
pio run
```

## Upload to real hardware

If a physical board is connected:

```bash
cd firmware-c
pio run -e <environment> -t upload
pio device monitor
```

The monitor baud rate is `115200`.

## Run tests

### Host-side tests

The host test runner does not depend on PlatformIO; it compiles the `sum` library with `gcc`:

```bash
cd firmware-c/test
gcc desktop_test_sum.c ../src/math/sum.c -I../src -o desktop_test_sum
./desktop_test_sum
```

Expected output:

```text
desktop_test_sum starting...
  PASS: test_sum_positive_numbers
  PASS: test_sum_negative_numbers
  PASS: test_sum_zero
  PASS: test_sum_commutative

Results: 4 passed, 0 failed
```

### Target-side Unity tests

Run tests for both environments:

```bash
cd firmware-c
pio test
```

Run tests for a specific environment:

```bash
cd firmware-c
pio test -e esp32-c3-devkitm-1
pio test -e stm32f103_bluepill
```

This builds [firmware-c/test/test_sum.cpp](firmware-c/test/test_sum.cpp) as a test binary and runs it on the target (or uploads it to real hardware). The test output is printed over UART.

To build the test binary without uploading:

```bash
pio test -e stm32f103_bluepill --without-uploading
```

## Useful commands

| Command | Description |
| --- | --- |
| `pio run` | Build all environments |
| `pio run -e <env>` | Build a specific environment |
| `pio run -t clean` | Clean build artifacts |
| `pio run -e <env> -t upload` | Build and upload to hardware |
| `pio device monitor` | Open serial monitor |
| `pio test` | Run Unity tests for all environments |
| `pio test -e <env>` | Run Unity tests for a specific environment |
| `pio test --without-uploading` | Build tests but do not upload |
| `pio project config` | Show resolved project configuration |
| `pio pkg list` | List installed packages/libraries |

## VS Code tasks

The following tasks are available in [.vscode/tasks.json](.vscode/tasks.json):

- **Build C Firmware (ESP32-C3)** — runs `pio run -e esp32-c3-devkitm-1`
- **Build C Firmware (STM32F103)** — runs `pio run -e stm32f103_bluepill`
- **Test C Host** — compiles and runs the host-side `sum` tests
- **Test C Target (ESP32-C3)** — runs `pio test -e esp32-c3-devkitm-1`
- **Test C Target (STM32F103)** — runs `pio test -e stm32f103_bluepill`

Run them with **Terminal > Run Task** or `Ctrl+Shift+P` → **Tasks: Run Task**.
