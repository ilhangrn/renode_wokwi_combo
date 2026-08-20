# Goal
This is a learning project for embedded coding, tools, and simulation workflows. The current target is the **ESP32-C3** (RISC-V core) on the **ESP32-C3-DevKitM-1** board.

We keep two parallel firmware implementations:

- **firmware-c/** — Arduino-style C++ firmware built with PlatformIO.
- **firmware-rust/** — Bare-metal Rust firmware built with `esp-hal`.

Both firmwares blink the LED on **GPIO8** and print a heartbeat message over UART.

# Structure

```
demo_renode/
├── .devcontainer/          # VS Code Dev Container setup
│   ├── devcontainer.json
│   └── Dockerfile
├── docs/                   # Guides and documentation
│   ├── dev_guide.md        # This file
│   ├── pio_guide.md        # PlatformIO commands and tests
│   ├── repl_guide.md       # REPL generation from device tree
│   ├── renode_guide.md     # Renode simulation and GDB debug
│   ├── sim_guide.md        # Simulation workflow overview
│   └── wokwi_guide.md      # Wokwi visual simulation
├── firmware-c/             # C/Arduino firmware (PlatformIO)
│   ├── platformio.ini
│   ├── src/
│   │   ├── main.cpp
│   │   └── math/
│   │       ├── sum.c
│   │       └── sum.h
│   └── test/
│       ├── desktop_test_sum.c
│       └── test_sum.cpp
├── firmware-rust/          # Rust firmware (esp-hal)
│   ├── Cargo.toml
│   ├── src/
│   │   ├── lib.rs
│   │   ├── main.rs
│   │   └── math/
│   │       └── mod.rs
│   └── tests/
│       └── test_sum.rs
├── sim/                                   # Renode simulation scripts
│   ├── esp32c3_devkitm.dts                # Project top-level DTS (Zephyr)
│   ├── esp32c3_devkitm_flat.dts           # Flattened DTS
│   ├── esp32c3_devkitm_generated.repl     # dts2repl output (with remote ROM/SVD)
│   ├── esp32c3_devkitm_generated_offline.repl # Offline-friendly REPL (used)
│   ├── esp32c3.repl                       # Legacy hand-written platform description
│   ├── esp32c3_common.dtsi                # Zephyr device-tree source (reference)
│   ├── esp32c3.dts                        # Old stub-based top-level DTS (reference)
│   ├── esp32c3_generated.repl             # Old stub-based generated REPL (reference)
│   ├── esp32c3_generated_offline.repl     # Old offline REPL (reference)
│   ├── generate_repl.sh                   # Script to regenerate REPLs from Zephyr
│   ├── include/                           # Stub Zephyr headers (reference)
│   └── setup.resc                         # Simulation startup script
├── diagram.json            # Wokwi wiring diagram
├── wokwi.toml              # Wokwi firmware selection
├── note.md                 # Developer scratch notes
└── task-plan.md            # Project milestones and TODOs
```

# Prerequisites

This project is designed to run inside the provided VS Code Dev Container.

1. Open the workspace in VS Code.
2. Run **Dev Containers: Reopen in Container**.
3. Wait for the container build; it installs:
   - PlatformIO Core (`pio`)
   - Rust toolchain with `riscv32imac-unknown-none-elf` target
   - Renode portable package (`renode`)
   - VS Code extensions for PlatformIO, Rust, Renode, and Wokwi

# Build the firmware

## C version (PlatformIO)

```bash
cd firmware-c
pio run
```

Output ELF:

```
firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

The C firmware uses the Arduino framework, configures GPIO8 as an output, and toggles the LED every second while logging the pin state to UART.

## Rust version (esp-hal)

```bash
cd firmware-rust
cargo build --release
```

Output ELF:

```
firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust
```

The Rust firmware uses `esp-hal` with `#![no_std]` and `#![no_main]`, toggles GPIO8, and prints the LED state every second.

# Simulate with Wokwi

[Wokwi](https://wokwi.com) provides a browser/visual simulation of the ESP32-C3 and the LED.

1. Make sure [wokwi.toml](wokwi.toml) points to the firmware you want to simulate:

   - **C:** set `firmware` and `elf` to `firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf`.
   - **Rust:** set them to `firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust`.

2. Open [diagram.json](diagram.json) in VS Code with the Wokwi extension (or use the **Wokwi: Start Simulator** command).
3. Observe the LED blinking on GPIO8 and the serial monitor output.

Wiring in [diagram.json](diagram.json):

- `esp:8` → LED anode (red)
- `esp:GND.1` → LED cathode (black)
- `esp:TX` / `esp:RX` → serial monitor

# Testing

Both firmware tracks include a small `sum(a, b)` library that is exercised by host-side unit tests.

## C

Host test runner:

```bash
cd firmware-c/test
gcc desktop_test_sum.c ../src/math/sum.c -I../src -o desktop_test_sum
./desktop_test_sum
```

Target test runner (Unity on the ESP32-C3):

```bash
cd firmware-c
pio test
```

The Unity test file is [firmware-c/test/test_sum.cpp](firmware-c/test/test_sum.cpp).

## Rust

Host unit tests are in [firmware-rust/src/math/mod.rs](firmware-rust/src/math/mod.rs) and integration tests are in [firmware-rust/tests/test_sum.rs](firmware-rust/tests/test_sum.rs).

```bash
cd firmware-rust
cargo test --lib      # unit tests
cargo test --test test_sum  # integration tests
```

# Simulate with Renode

[Renode](https://renode.io) provides deterministic machine emulation with a GDB server for debugging.

## Start the simulation

Build the firmware first, then run Renode from the `sim/` directory:

```bash
cd firmware-c && pio run
cd ../sim
renode setup.resc
```

[sim/setup.resc](sim/setup.resc) performs the following steps:

1. Creates a machine named `esp32-c3`.
2. Loads the platform description from [sim/esp32c3_devkitm_generated_offline.repl](sim/esp32c3_devkitm_generated_offline.repl). This REPL is generated from the official Zephyr ESP32-C3-DevKitM device tree using [dts2repl](https://github.com/antmicro/dts2repl); see [repl_guide.md](repl_guide.md) for details.
3. Loads the firmware ELF configured by `$bin?`.
4. Opens the UART analyzer window.
5. Starts a GDB server on `localhost:3333`.

By default the script loads the C firmware. To switch to the Rust firmware, comment out the C line and uncomment the Rust line in [sim/setup.resc](sim/setup.resc):

```renode
$bin?=@../firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust
```

[sim/setup.resc](sim/setup.resc) uses relative paths, so it must be started from the `sim/` directory.

## Debug with GDB

Attach with a RISC-V GDB binary, for example:

```bash
riscv32-esp-elf-gdb -ex "target remote localhost:3333" \
  firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

or for Rust:

```bash
riscv32-esp-elf-gdb -ex "target remote localhost:3333" \
  firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust
```

Typical GDB workflow:

```gdb
(gdb) monitor start
(gdb) load
(gdb) break main
(gdb) continue
(gdb) step
(gdb) info registers
```

Because Renode starts the GDB server before emulation begins, use `monitor start` or start emulation from the Renode monitor to run the CPU.

# Detailed guides

For command-level details, see the focused guides:

- [PlatformIO workflow](pio_guide.md) — build, upload, and test the C firmware.
- [REPL generation](repl_guide.md) — generate the Renode platform description from device tree.
- [Renode workflow](renode_guide.md) — start emulation, attach GDB, and run tests in simulation.
- [Wokwi workflow](wokwi_guide.md) — visual simulation, wiring, and firmware selection.
- [Simulation overview](sim_guide.md) — when to use Wokwi vs Renode and how they fit together.

# Current status and next steps

See [task-plan.md](task-plan.md) for the full milestone checklist.

Completed:

- [x] Dev container with Renode, PlatformIO, and Rust installed.
- [x] C firmware builds with PlatformIO and prints/blinks on GPIO8.
- [x] Rust firmware builds with `cargo build --release` and prints/blinks on GPIO8.
- [x] Renode platform description and startup script created.
- [x] Wokwi diagram and configuration created.
- [x] `.vscode/tasks.json` for one-click build/simulate/test tasks.
- [x] `.vscode/launch.json` for GDB attach from VS Code.
- [x] Unit tests for a basic `sum` library in both C and Rust.
- [x] Documentation split into focused guides under `docs/`.

Still pending:

- [ ] Validate end-to-end debug flow with breakpoints and stepping.
- [ ] Add CI workflow for headless build and simulation checks.

# Learning milestones

For first projects we use an ESP32-C3 target; later versions may target STM32, Raspberry Pi, or other devices.

## Hello world with Wokwi

### C version

- Build: `cd firmware-c && pio run`
- Point [wokwi.toml](wokwi.toml) to the C ELF.
- Start Wokwi simulator from [diagram.json](diagram.json).
- Expected output: red LED on GPIO8 blinks once per second; serial monitor shows `Blink C loop executed...`.

### Rust version

- Build: `cd firmware-rust && cargo build --release`
- Point [wokwi.toml](wokwi.toml) to the Rust ELF.
- Start Wokwi simulator from [diagram.json](diagram.json).
- Expected output: red LED on GPIO8 blinks once per second; serial monitor shows `Blink Rust loop executed...`.

## Hello world with Renode

### C version

- Build: `cd firmware-c && pio run`
- Ensure [sim/setup.resc](sim/setup.resc) points to the C ELF.
- Run: `cd sim && renode setup.resc`
- Attach GDB to `localhost:3333`, set breakpoints in `setup`/`loop`, and continue.
- Expected output: UART analyzer shows `Hello from ESP32-C3 C Firmware!` and loop messages.

### Rust version

- Build: `cd firmware-rust && cargo build --release`
- Edit [sim/setup.resc](sim/setup.resc) to use the Rust release ELF.
- Run: `cd sim && renode setup.resc`
- Attach GDB to `localhost:3333` and debug.
- Expected output: UART analyzer shows `Hello from ESP32-C3 Rust Firmware!` and loop messages.

