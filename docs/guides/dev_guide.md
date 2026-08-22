# Goal

This is a learning project for embedded coding, tools, and simulation workflows. It supports two boards:

- **ESP32-C3-DevKitM-1** (RISC-V core) — simulated with **Wokwi** only.
- **STM32F103 Blue Pill** (ARM Cortex-M3) — simulated with **Wokwi** and **Renode**.

The physical ESP32 board available is the **Freenove Wrover v3**, which is **not supported by Renode**, so the ESP32 target does not use Renode. The STM32F103 Blue Pill is supported by Renode and is used to demonstrate deterministic machine emulation and GDB debugging.

We keep two parallel firmware implementations:

- **firmware-c/** — Arduino-style C++ firmware built with PlatformIO.
- **firmware-rust/** — Bare-metal Rust firmware built with board-specific HALs (`esp-hal` for ESP32-C3, `stm32f1xx-hal` for STM32F103).

Each firmware blinks an on-board LED and prints a heartbeat message over UART:

- **ESP32-C3:** LED on **GPIO8**.
- **STM32F103:** LED on **PC13**.

# Structure

```
demo_renode/
├── .devcontainer/          # VS Code Dev Container setup
│   ├── devcontainer.json
│   └── Dockerfile
├── docs/                   # Guides and documentation
│   ├── dev_guide.md        # This file
│   ├── pio_guide.md        # PlatformIO commands and tests
│   ├── repl_guide.md       # REPL generation from device tree (archived ESP32-C3 reference)
│   ├── renode_guide.md     # Renode simulation and GDB debug
│   ├── sim_guide.md        # Simulation workflow overview
│   └── wokwi_guide.md      # Wokwi visual simulation
├── firmware-c/             # C/Arduino firmware (PlatformIO)
│   ├── platformio.ini
│   ├── src/
│   │   ├── main_esp32c3.cpp
│   │   ├── main_stm32f103.cpp
│   │   └── math/
│   │       ├── sum.c
│   │       └── sum.h
│   └── test/
│       ├── desktop_test_sum.c
│       └── test_sum.cpp
├── firmware-rust/          # Rust firmware (board-specific HALs)
│   ├── Cargo.toml
│   ├── .cargo/
│   │   └── config.toml
│   ├── src/
│   │   ├── lib.rs
│   │   ├── main_esp32c3.rs
│   │   ├── main_stm32f103.rs
│   │   └── math/
│   │       └── mod.rs
│   └── tests/
│       └── test_sum.rs
├── sim/                                   # Renode simulation scripts
│   └── stm32f103_bluepill/                # STM32F103 Blue Pill setup
│       └── blue_pill.resc
├── wokwi/                                 # Wokwi diagrams and firmware selection
│   ├── esp32c3/                           # ESP32-C3-DevKitM-1 diagram
│   │   ├── diagram.json
│   │   └── wokwi.toml
│   └── stm32f103/                         # STM32F103 Blue Pill diagram
│       ├── diagram.json
│       └── wokwi.toml
├── note.md                 # Developer scratch notes
└── task-plan.md            # Project milestones and TODOs
```

# Prerequisites

This project is designed to run inside the provided VS Code Dev Container.

1. Open the workspace in VS Code.
2. Run **Dev Containers: Reopen in Container**.
3. Wait for the container build; it installs:
   - PlatformIO Core (`pio`)
   - Rust toolchain with `riscv32imac-unknown-none-elf` and `thumbv7m-none-eabi` targets
   - Renode portable package (`renode`)
   - ARM cross-compiler (`gcc-arm-none-eabi`) and GDB (`gdb-multiarch`)
   - VS Code extensions for PlatformIO, Rust, Renode, and Wokwi

# Build the firmware

## C version (PlatformIO)

Both board environments are defined in [firmware-c/platformio.ini](firmware-c/platformio.ini). Build one or both:

```bash
cd firmware-c
pio run -e esp32-c3-devkitm-1
pio run -e stm32f103_bluepill
```

Output ELFs:

```
firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
firmware-c/.pio/build/stm32f103_bluepill/firmware.elf
```

The C firmware uses the Arduino framework, configures the board LED as an output, and toggles it every second while logging the pin state to UART.

## Rust version

The Rust crate uses Cargo features to select the board HAL. Build one or both:

```bash
cd firmware-rust

# ESP32-C3
cargo build --release --target riscv32imac-unknown-none-elf --features esp32c3 --bin firmware-rust-esp32c3

# STM32F103
cargo build --release --target thumbv7m-none-eabi --features stm32f103 --bin firmware-rust-stm32f103
```

Output ELFs:

```
firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust-esp32c3
firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103
```

### Rust linker strategy by target

This repository uses a target-scoped linker setup, which is the recommended approach for multi-board embedded Rust projects.

- Shared linker flags per target are configured in [firmware-rust/.cargo/config.toml](firmware-rust/.cargo/config.toml).
- **ESP32-C3 (`riscv32imac-unknown-none-elf`)** uses the `esp-hal` linker flow (`-Tlinkall.x`) and does not use an STM32 memory script.
- **STM32F103 (`thumbv7m-none-eabi`)** uses `cortex-m-rt` (`-Tlink.x`) plus a board memory layout at [firmware-rust/linker/stm32f103/memory.x](firmware-rust/linker/stm32f103/memory.x).

Why this matters:

- It prevents one board's memory map from breaking another board's link step.
- It keeps linker behavior explicit and maintainable as more boards are added.

# Simulate with Wokwi

[Wokwi](https://wokwi.com) provides a browser/visual simulation for both boards. Board-specific diagrams and firmware selectors live under [wokwi/](wokwi/).

## ESP32-C3

1. Make sure [wokwi/esp32c3/wokwi.toml](wokwi/esp32c3/wokwi.toml) points to the firmware you want to simulate.
2. Open [wokwi/esp32c3/diagram.json](wokwi/esp32c3/diagram.json) in VS Code and start the Wokwi simulator.
3. Observe the LED blinking on GPIO8 and the serial monitor output.

## STM32F103 Blue Pill

1. Make sure [wokwi/stm32f103/wokwi.toml](wokwi/stm32f103/wokwi.toml) points to the firmware you want to simulate.
2. Open [wokwi/stm32f103/diagram.json](wokwi/stm32f103/diagram.json) in VS Code and start the Wokwi simulator.
3. Observe the LED blinking on PC13 and the serial monitor output.

See [wokwi_guide.md](wokwi_guide.md) for full wiring details.

# Simulate with Renode

[Renode](https://renode.io) provides deterministic machine emulation with a GDB server. It is used for the **STM32F103 Blue Pill** only.

Build the firmware first, then start Renode from the STM32 simulation directory:

```bash
cd firmware-c && pio run -e stm32f103_bluepill
cd ../sim/stm32f103_bluepill
renode blue_pill.resc
```

[sim/stm32f103_bluepill/blue_pill.resc](sim/stm32f103_bluepill/blue_pill.resc) loads the Renode platform description, loads the selected firmware ELF, opens the USART1 analyzer, starts a GDB server on `localhost:3333`, and begins emulation.

By default the script loads the C firmware. To switch to the Rust firmware, edit the `$bin?` line in [sim/stm32f103_bluepill/blue_pill.resc](sim/stm32f103_bluepill/blue_pill.resc):

```renode
$bin?=@../../firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103
```

Attach with the ARM GDB binary:

```bash
arm-none-eabi-gdb -ex "target remote localhost:3333" \
  firmware-c/.pio/build/stm32f103_bluepill/firmware.elf
```

See [renode_guide.md](renode_guide.md) for full details.

# Testing

Both firmware tracks include a small `sum(a, b)` library that is exercised by host-side unit tests.

## C

Host test runner:

```bash
cd firmware-c/test
gcc desktop_test_sum.c ../src/math/sum.c -I../src -o desktop_test_sum
./desktop_test_sum
```

Target test runner (Unity) per board:

```bash
cd firmware-c
pio test -e esp32-c3-devkitm-1
pio test -e stm32f103_bluepill
```

The Unity test file is [firmware-c/test/test_sum.cpp](firmware-c/test/test_sum.cpp).

## Rust

Host unit tests are in [firmware-rust/src/math/mod.rs](firmware-rust/src/math/mod.rs) and integration tests are in [firmware-rust/tests/test_sum.rs](firmware-rust/tests/test_sum.rs).

```bash
cd firmware-rust
cargo test --lib      # unit tests
cargo test --test test_sum  # integration tests
```

# Detailed guides

For command-level details, see the focused guides:

- [PlatformIO workflow](pio_guide.md) — build, upload, and test the C firmware.
- [Wokwi workflow](wokwi_guide.md) — visual simulation, wiring, and firmware selection.
- [Simulation overview](sim_guide.md) — when to use Wokwi vs Renode and how they fit together.
- [Renode workflow](renode_guide.md) — start emulation, attach GDB, and run tests for STM32F103.
- [REPL generation](repl_guide.md) — archived; REPL generation for the previous ESP32-C3 Renode setup.

# Current status and next steps

See [task-plan.md](task-plan.md) for the full milestone checklist.

Completed:

- [x] Dev container with PlatformIO, Rust, Renode, and ARM toolchain installed.
- [x] C firmware builds for ESP32-C3 and STM32F103 with PlatformIO.
- [x] Rust firmware builds for ESP32-C3 and STM32F103 with cargo.
- [x] Wokwi diagrams and configurations for both boards.
- [x] Renode simulation script for STM32F103 Blue Pill.
- [x] `.vscode/tasks.json` for one-click build/simulate/test tasks.
- [x] `.vscode/launch.json` for STM32 GDB attach from VS Code.
- [x] Unit tests for a basic `sum` library in both C and Rust.
- [x] Documentation split into focused guides under `docs/`.

Still pending:

- [ ] Validate end-to-end Wokwi simulation flow for both boards.
- [ ] Validate end-to-end Renode debug flow for STM32F103.
- [ ] Add CI workflow for build and simulation checks.

# Learning milestones

## Hello world with Wokwi

### ESP32-C3 C version

- Build: `cd firmware-c && pio run -e esp32-c3-devkitm-1`
- Point [wokwi/esp32c3/wokwi.toml](wokwi/esp32c3/wokwi.toml) to the C ELF.
- Start Wokwi simulator from [wokwi/esp32c3/diagram.json](wokwi/esp32c3/diagram.json).
- Expected output: red LED on GPIO8 blinks once per second; serial monitor shows `Blink C loop executed...`.

### ESP32-C3 Rust version

- Build: `cd firmware-rust && cargo build --release --target riscv32imac-unknown-none-elf --features esp32c3 --bin firmware-rust-esp32c3`
- Point [wokwi/esp32c3/wokwi.toml](wokwi/esp32c3/wokwi.toml) to the Rust ELF.
- Start Wokwi simulator from [wokwi/esp32c3/diagram.json](wokwi/esp32c3/diagram.json).
- Expected output: red LED on GPIO8 blinks once per second; serial monitor shows `Blink Rust loop executed...`.

### STM32F103 C version

- Build: `cd firmware-c && pio run -e stm32f103_bluepill`
- Point [wokwi/stm32f103/wokwi.toml](wokwi/stm32f103/wokwi.toml) to the C ELF.
- Start Wokwi simulator from [wokwi/stm32f103/diagram.json](wokwi/stm32f103/diagram.json).
- Expected output: red LED on PC13 blinks once per second; serial monitor shows `Blink STM32 loop executed...`.

### STM32F103 Rust version

- Build: `cd firmware-rust && cargo build --release --target thumbv7m-none-eabi --features stm32f103 --bin firmware-rust-stm32f103`
- Point [wokwi/stm32f103/wokwi.toml](wokwi/stm32f103/wokwi.toml) to the Rust ELF.
- Start Wokwi simulator from [wokwi/stm32f103/diagram.json](wokwi/stm32f103/diagram.json).
- Expected output: red LED on PC13 blinks once per second; serial monitor shows `Blink STM32 loop executed...`.

## Hello world with Renode (STM32F103 only)

### C version

- Build: `cd firmware-c && pio run -e stm32f103_bluepill`
- Ensure [sim/stm32f103_bluepill/blue_pill.resc](sim/stm32f103_bluepill/blue_pill.resc) points to the C ELF.
- Run: `cd sim/stm32f103_bluepill && renode blue_pill.resc`
- Attach GDB to `localhost:3333` and debug.
- Expected output: USART1 analyzer shows `Hello from STM32F103 C Firmware!` and loop messages.

### Rust version

- Build: `cd firmware-rust && cargo build --release --target thumbv7m-none-eabi --features stm32f103 --bin firmware-rust-stm32f103`
- Edit [sim/stm32f103_bluepill/blue_pill.resc](sim/stm32f103_bluepill/blue_pill.resc) to use the Rust ELF.
- Run: `cd sim/stm32f103_bluepill && renode blue_pill.resc`
- Attach GDB to `localhost:3333` and debug.
- Expected output: USART1 analyzer shows `Hello from STM32F103 Rust Firmware!` and loop messages.

## Notes

- The ESP32-C3 target is **not** supported by Renode; use Wokwi for visual simulation.
- The archived ESP32-C3 Renode reference (from an earlier version of this project) remains in [renode_guide.md](renode_guide.md) and [repl_guide.md](repl_guide.md) for reference.

