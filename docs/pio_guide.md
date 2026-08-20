# PlatformIO Guide

This project uses [PlatformIO Core](https://platformio.org/install/cli) to build the C/Arduino firmware for the ESP32-C3.

## Environment

The active environment is defined in [firmware-c/platformio.ini](firmware-c/platformio.ini):

```ini
[env:esp32-c3-devkitm-1]
platform = espressif32
board = esp32-c3-devkitm-1
framework = arduino
monitor_speed = 115200
build_unflags = -Os
build_flags = -Og -g3
lib_deps =
    throwtheswitch/Unity@^2.5.2
```

- `board`: ESP32-C3-DevKitM-1 (RISC-V, 160 MHz, 320 KB RAM, 4 MB flash)
- `framework`: Arduino
- `build_flags`: `-Og -g3` keeps debug symbols and a debug-friendly optimization level for GDB stepping in Renode.
- `lib_deps`: Unity test framework for target-side tests.

## Build the C firmware

```bash
cd firmware-c
pio run
```

The generated ELF is written to:

```
firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

To build only a specific environment (if you add more later):

```bash
pio run -e esp32-c3-devkitm-1
```

To force a clean rebuild:

```bash
pio run -t clean
pio run
```

## Upload to real hardware

If a physical ESP32-C3-DevKitM-1 is connected:

```bash
cd firmware-c
pio run -t upload
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

```bash
cd firmware-c
pio test
```

This builds [firmware-c/test/test_sum.cpp](firmware-c/test/test_sum.cpp) as a test binary and runs it on the target (or uploads it to real hardware). The test output is printed over UART.

To build the test binary without uploading:

```bash
pio test --without-uploading
```

## Useful commands

| Command | Description |
| --- | --- |
| `pio run` | Build the firmware |
| `pio run -t clean` | Clean build artifacts |
| `pio run -t upload` | Build and upload to hardware |
| `pio device monitor` | Open serial monitor |
| `pio test` | Run Unity tests |
| `pio test --without-uploading` | Build tests but do not upload |
| `pio project config` | Show resolved project configuration |
| `pio pkg list` | List installed packages/libraries |

## VS Code tasks

The following tasks are available in [.vscode/tasks.json](.vscode/tasks.json):

- **Build C Firmware** — runs `pio run`
- **Test C Host** — compiles and runs the host-side `sum` tests
- **Test C Target** — runs `pio test`

Run them with **Terminal > Run Task** or `Ctrl+Shift+P` → **Tasks: Run Task**.
