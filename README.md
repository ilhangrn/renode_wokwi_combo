# Renode Wokwi Combo

Learning project for embedded firmware development across C and Rust, using two MCUs and two simulator workflows.

- Boards:
  - ESP32-C3-DevKitM-1 (Wokwi simulation)
  - STM32F103 Blue Pill (Wokwi and Renode simulation)
- Firmware tracks:
  - [firmware-c/](firmware-c/) (PlatformIO, Arduino-style)
  - [firmware-rust/](firmware-rust/) (bare-metal Rust)

## Project goals

- Build equivalent firmware behavior in C and Rust.
- Simulate quickly in Wokwi.
- Debug deterministically in Renode for STM32.
- Keep a repeatable local workflow in a dev container.

Each firmware prints a startup message, computes `sum(10, 32)`, and blinks LED every second.

## Repository layout

- [docs/](docs/): command guides and workflows
- [firmware-c/](firmware-c/): C firmware, PlatformIO environments and tests
- [firmware-rust/](firmware-rust/): Rust firmware, targets and tests
- [sim/stm32f103_bluepill/](sim/stm32f103_bluepill/): Renode setup script for STM32
- [wokwi/](wokwi/): Wokwi diagrams and board-specific firmware selectors

## Prerequisites

Recommended: open this project in the provided dev container.

See [docs/dev_guide.md](docs/dev_guide.md) for full setup details.

Main tools used:

- PlatformIO (`pio`)
- Rust toolchain + embedded targets
- Renode
- ARM and RISC-V GDB toolchains

## Build firmware

### C firmware (PlatformIO)

Build ESP32-C3:

```bash
cd firmware-c
pio run -e esp32-c3-devkitm-1
```

Build STM32F103:

```bash
cd firmware-c
pio run -e stm32f103_bluepill
```

Outputs:

- `firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf`
- `firmware-c/.pio/build/stm32f103_bluepill/firmware.elf`

### Rust firmware

Build ESP32-C3:

```bash
cd firmware-rust
cargo build --release --target riscv32imac-unknown-none-elf --features esp32c3 --bin firmware-rust-esp32c3
```

Build STM32F103:

```bash
cd firmware-rust
cargo build --release --target thumbv7m-none-eabi --features stm32f103 --bin firmware-rust-stm32f103
```

Outputs:

- `firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust-esp32c3`
- `firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103`

## Test

### C host test

```bash
cd firmware-c/test
gcc desktop_test_sum.c ../src/math/sum.c -I../src -o desktop_test_sum
./desktop_test_sum
```

### C target tests (Unity via PlatformIO)

```bash
cd firmware-c
pio test -e esp32-c3-devkitm-1
pio test -e stm32f103_bluepill
```

### Rust host tests

```bash
cd firmware-rust
cargo test --lib
cargo test --test test_sum
```

## Simulation

### Wokwi (ESP32 + STM32)

1. Build firmware for the target board.
2. Point board-specific `wokwi.toml` to the selected ELF:
   - [wokwi/esp32c3/wokwi.toml](wokwi/esp32c3/wokwi.toml)
   - [wokwi/stm32f103/wokwi.toml](wokwi/stm32f103/wokwi.toml)
3. Open and run diagram:
   - [wokwi/esp32c3/diagram.json](wokwi/esp32c3/diagram.json)
   - [wokwi/stm32f103/diagram.json](wokwi/stm32f103/diagram.json)

### Renode (STM32 only)

ESP32-C3 is not currently supported by Renode in this project workflow.

1. Build STM32 firmware (C or Rust).
2. Start Renode:

```bash
cd sim/stm32f103_bluepill
renode blue_pill.resc
```

3. Attach GDB:

```bash
arm-none-eabi-gdb -ex "target remote localhost:3333" firmware-c/.pio/build/stm32f103_bluepill/firmware.elf
```

To run Rust firmware in Renode, point [sim/stm32f103_bluepill/blue_pill.resc](sim/stm32f103_bluepill/blue_pill.resc) to the Rust ELF path.

## VS Code tasks

This repo includes preconfigured tasks in [.vscode/tasks.json](.vscode/tasks.json) for:

- Building C/Rust firmware for both boards
- Starting and stopping Renode
- Running host and target tests

Run from Terminal -> Run Task.

## Documentation index

- [docs/dev_guide.md](docs/dev_guide.md): full project overview and milestones
- [docs/pio_guide.md](docs/pio_guide.md): PlatformIO build and test flow
- [docs/sim_guide.md](docs/sim_guide.md): simulation strategy and tool selection
- [docs/wokwi_guide.md](docs/wokwi_guide.md): Wokwi board wiring and usage
- [docs/renode_guide.md](docs/renode_guide.md): Renode setup and STM32 debugging
- [docs/repl_guide.md](docs/repl_guide.md): archived REPL generation reference

## Current status

See [task-plan.md](task-plan.md) for active milestones and remaining validation steps.