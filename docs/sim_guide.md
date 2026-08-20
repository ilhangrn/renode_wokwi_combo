# Simulation Guide

This project supports two boards with different simulation tools:

| Board | Tool | Type | Best for | Debug support |
| --- | --- | --- | --- | --- |
| ESP32-C3-DevKitM-1 | [Wokwi](https://wokwi.com) | Visual/browser-based | Fast interactive checks, LED wiring, serial output | Limited |
| STM32F103 Blue Pill | [Wokwi](https://wokwi.com) | Visual/browser-based | Fast interactive checks, LED wiring, serial output | Limited |
| STM32F103 Blue Pill | [Renode](https://renode.io) | Deterministic machine emulation | GDB debugging, repeatable tests, CI automation | Full GDB server |

The ESP32-C3 target is **not supported by Renode**, so it uses Wokwi only. The STM32F103 Blue Pill is supported by both Wokwi and Renode.

Both simulators use the compiled ELF files produced by `pio run` and `cargo build`.

## Quick comparison

### Wokwi

- Opens inside VS Code or the browser.
- Renders the board, the LED, and the serial monitor.
- Good for visually verifying that the firmware blinks the LED and prints messages.
- Does not support breakpoints or GDB.

### Renode

- Runs as a headless or GUI emulator.
- Loads the platform description from Renode's built-in STM32F103 model.
- Starts a GDB server on `localhost:3333`.
- Supports source-level debugging with `arm-none-eabi-gdb`.
- Better for automated tests and CI.

## Choosing a simulator

- Use **Wokwi** when you want a quick visual confirmation that the firmware runs.
- Use **Renode** when you need GDB debugging or reproducible test runs on the STM32F103.

## Build outputs used by simulators

| Board | Firmware | Build command | ELF path |
| --- | --- | --- | --- |
| ESP32-C3 | C/Arduino | `cd firmware-c && pio run -e esp32-c3-devkitm-1` | `firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf` |
| ESP32-C3 | Rust | `cd firmware-rust && cargo build --release --target riscv32imac-unknown-none-elf --features esp32c3 --bin firmware-rust-esp32c3` | `firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust-esp32c3` |
| STM32F103 | C/Arduino | `cd firmware-c && pio run -e stm32f103_bluepill` | `firmware-c/.pio/build/stm32f103_bluepill/firmware.elf` |
| STM32F103 | Rust | `cd firmware-rust && cargo build --release --target thumbv7m-none-eabi --features stm32f103 --bin firmware-rust-stm32f103` | `firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103` |

## Wokwi workflow

1. Build the firmware for the board you want to simulate.
2. Edit the board-specific `wokwi.toml` to point to the ELF you just built:
   - ESP32-C3: [wokwi/esp32c3/wokwi.toml](wokwi/esp32c3/wokwi.toml)
   - STM32F103: [wokwi/stm32f103/wokwi.toml](wokwi/stm32f103/wokwi.toml)
3. Open the corresponding `diagram.json` and start the Wokwi simulator.
4. Watch the LED blink and read the serial monitor.

See [wokwi_guide.md](wokwi_guide.md) for full details.

## Renode workflow (STM32F103 only)

1. Build the firmware:

   ```bash
   cd firmware-c && pio run -e stm32f103_bluepill
   # or
   cd firmware-rust && cargo build --release --target thumbv7m-none-eabi --features stm32f103 --bin firmware-rust-stm32f103
   ```

2. Make sure [sim/stm32f103_bluepill/setup.resc](sim/stm32f103_bluepill/setup.resc) points to the ELF you just built.
3. Run from the simulation directory:

   ```bash
   cd sim/stm32f103_bluepill
   renode setup.resc
   ```

4. The simulation starts automatically.
5. (Optional) Attach GDB to `localhost:3333` for debugging.

See [renode_guide.md](renode_guide.md) for full details.

## VS Code tasks

The following simulation-related tasks are in [.vscode/tasks.json](.vscode/tasks.json):

- **Build C Firmware (ESP32-C3)**
- **Build C Firmware (STM32F103)**
- **Build Rust Firmware (ESP32-C3)**
- **Build Rust Firmware (STM32F103)**
- **Start Renode Simulation (STM32 C)**
- **Start Renode Simulation (STM32 Rust)**
- **Stop Renode**
- **Test C Host**
- **Test C Target (ESP32-C3)**
- **Test C Target (STM32F103)**
- **Test Rust Host**

Run them from **Terminal > Run Task** or `Ctrl+Shift+P` → **Tasks: Run Task**.

## Debugging from VS Code

The launch configurations in [.vscode/launch.json](.vscode/launch.json) combine build, simulation, and debug attach for STM32F103:

- **Debug STM32 C Firmware in Renode**
- **Debug STM32 Rust Firmware in Renode**

Press `F5` to start a one-click debug session.

## Testing

| Test type | Tool | Command |
| --- | --- | --- |
| Host unit tests (C) | gcc | see [pio_guide.md](pio_guide.md) |
| Target unit tests (C) ESP32-C3 | PlatformIO Unity | `cd firmware-c && pio test -e esp32-c3-devkitm-1` |
| Target unit tests (C) STM32F103 | PlatformIO Unity | `cd firmware-c && pio test -e stm32f103_bluepill` |
| Host unit tests (Rust) | cargo | `cd firmware-rust && cargo test --lib` |
| Smoke test in Renode | Renode UART output | `cd sim/stm32f103_bluepill && renode setup.resc` |

See the individual guides for detailed test commands and expected output.
