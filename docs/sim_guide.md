# Simulation Guide

This project supports two simulation workflows for the ESP32-C3 firmware:

| Tool | Type | Best for | Debug support |
| --- | --- | --- | --- |
| [Wokwi](https://wokwi.com) | Visual/browser-based | Fast interactive checks, LED wiring, serial output | Limited |
| [Renode](https://renode.io) | Deterministic machine emulation | GDB debugging, repeatable tests, CI automation | Full GDB server |

Both simulators use the same compiled ELF files produced by `pio run` and `cargo build --release`.

## Quick comparison

### Wokwi

- Opens inside VS Code or the browser.
- Renders the ESP32-C3 board, the red LED on GPIO8, and the serial monitor.
- Good for visually verifying that the firmware blinks the LED and prints messages.
- Does not support breakpoints or GDB.

### Renode

- Runs as a headless or GUI emulator.
- Loads the platform description from [sim/esp32c3.repl](sim/esp32c3.repl).
- Starts a GDB server on `localhost:3333`.
- Supports source-level debugging with `riscv32-esp-elf-gdb`.
- Better for automated tests and CI.

## Choosing a simulator

- Use **Wokwi** when you want a quick visual confirmation that the firmware runs.
- Use **Renode** when you need GDB debugging or reproducible test runs.

## Build outputs used by simulators

| Firmware | Build command | ELF path |
| --- | --- | --- |
| C/Arduino | `cd firmware-c && pio run` | `firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf` |
| Rust | `cd firmware-rust && cargo build --release` | `firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust` |

## Wokwi workflow

1. Build the firmware.
2. Edit [wokwi.toml](wokwi.toml) to point to the ELF you just built.
3. Open [diagram.json](diagram.json) and start the Wokwi simulator.
4. Watch the LED blink and read the serial monitor.

See [wokwi_guide.md](wokwi_guide.md) for full details.

## Renode workflow

1. Build the firmware:

   ```bash
   cd firmware-c && pio run
   # or
   cd firmware-rust && cargo build --release
   ```

2. Make sure [sim/setup.resc](sim/setup.resc) points to the ELF you just built.
3. Run from the `sim/` directory:

   ```bash
   cd sim
   renode setup.resc
   ```

4. In the Renode monitor, type `start` to run the CPU.
5. (Optional) Attach GDB to `localhost:3333` for debugging.

See [renode_guide.md](renode_guide.md) for full details.

## VS Code tasks

The following simulation-related tasks are in [.vscode/tasks.json](.vscode/tasks.json):

- **Start Renode Simulation (C)**
- **Start Renode Simulation (Rust)**
- **Stop Renode**

Run them from **Terminal > Run Task** or `Ctrl+Shift+P` → **Tasks: Run Task**.

## Debugging from VS Code

The launch configurations in [.vscode/launch.json](.vscode/launch.json) combine build, simulation, and debug attach:

- **Debug C Firmware in Renode**
- **Debug Rust Firmware in Renode**

Press `F5` to start a one-click debug session.

## Testing in simulation

| Test type | Tool | Command |
| --- | --- | --- |
| Host unit tests (C) | gcc | see [pio_guide.md](pio_guide.md) |
| Target unit tests (C) | PlatformIO Unity | `cd firmware-c && pio test` |
| Host unit tests (Rust) | cargo | `cd firmware-rust && cargo test --lib` |
| Smoke test in Renode | Renode UART output | `cd sim && renode setup.resc` then `start` |

See the individual guides for detailed test commands and expected output.
