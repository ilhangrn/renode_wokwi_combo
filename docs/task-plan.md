# Task Plan: demo_renode

Date: 2026-08-20
Project type: PlatformIO firmware + Wokwi/Renode simulation + VS Code Dev Container

## TREE
demo_renode/
├── .devcontainer/
│   ├── devcontainer.json
│   └── Dockerfile
├── firmware-c/
│   ├── src/
│   │   ├── main_esp32c3.cpp
│   │   ├── main_stm32f103.cpp
│   │   └── math/
│   │       ├── sum.c
│   │       └── sum.h
│   ├── platformio.ini
│   └── test/
├── firmware-rust/
│   ├── src/
│   │   ├── lib.rs
│   │   ├── main_esp32c3.rs
│   │   ├── main_stm32f103.rs
│   │   └── math/
│   │       └── mod.rs
│   ├── Cargo.toml
│   └── .cargo/
│       └── config.toml
├── sim/
│   └── stm32f103_bluepill/
│       └── blue_pill.resc
├── wokwi/
│   ├── esp32c3/
│   │   ├── diagram.json
│   │   └── wokwi.toml
│   └── stm32f103/
│       ├── diagram.json
│       └── wokwi.toml
├── note.md
└── task-plan.md

## 1) Current Status

- Two boards are supported:
  - **ESP32-C3-DevKitM-1** (RISC-V) — simulated with **Wokwi** only.
  - **STM32F103 Blue Pill** (ARM Cortex-M3) — simulated with **Wokwi** and **Renode**.
- The physical ESP32 board is the **Freenove Wrover v3**, which is **not supported by Renode**.
- `.devcontainer/devcontainer.json` exists with PlatformIO, Rust, Renode, and Wokwi extensions.
- `.devcontainer/Dockerfile` installs PlatformIO, Rust toolchain, Renode, ARM cross-compiler, and GDB.
- `firmware-c/platformio.ini` defines environments for both boards.
- `firmware-c/src/main_esp32c3.cpp` and `firmware-c/src/main_stm32f103.cpp` contain LED blink + serial log loops.
- `firmware-rust/Cargo.toml` uses features to select the ESP32-C3 or STM32F103 HAL.
- `firmware-rust/src/main_esp32c3.rs` and `firmware-rust/src/main_stm32f103.rs` are the board-specific binaries.
- Wokwi diagrams and firmware selectors exist for both boards.
- Renode simulation script exists for STM32F103 Blue Pill.
- `.vscode/tasks.json` and `.vscode/launch.json` provide build, simulation, and debug automation.
- Documentation split into focused guides under `docs/`.

## 2) Primary Goal

Build and verify embedded firmware for ESP32-C3 and STM32F103 Blue Pill inside an isolated dev container. Use Wokwi for visual simulation of both boards and Renode for deterministic emulation and GDB debugging of the STM32F103.

## 3) Milestones

### M1 - Environment and Toolchain Baseline

- [x] Dev container with PlatformIO, Rust, Renode, Wokwi, and ARM toolchain installed.
- [ ] Rebuild and reopen the project in the Dev Container.
- [ ] Verify tools are available in container:
  - `platformio`, `pio`
  - `cargo`, `rustc`
  - `renode`
  - `arm-none-eabi-gdb`
  - Wokwi VS Code extension
- [ ] Document verified tool versions in project notes.

Definition of done:
- Container builds without manual fixes.
- All required CLI tools resolve from PATH.

### M2 - Firmware Project Bootstrap

- [x] Populate `firmware-c/platformio.ini` with both board environments.
- [x] Add board-specific firmware apps in `firmware-c/src/main_esp32c3.cpp` and `firmware-c/src/main_stm32f103.cpp`.
- [x] Add board-specific firmware apps in `firmware-rust/src/main_esp32c3.rs` and `firmware-rust/src/main_stm32f103.rs`.
- [ ] Run first successful builds:
  - `cd firmware-c && pio run`
  - `cd firmware-rust && cargo build --release --target riscv32imac-unknown-none-elf --features esp32c3 --bin firmware-rust-esp32c3`
  - `cd firmware-rust && cargo build --release --target thumbv7m-none-eabi --features stm32f103 --bin firmware-rust-stm32f103`
- [ ] Confirm ELF output paths for Wokwi and Renode loading.

Definition of done:
- Build succeeds and generates ELF binaries for both boards in both C and Rust.

### M3 - Wokwi Simulation Wiring

- [x] Create `wokwi/esp32c3/diagram.json` with LED on GPIO8 and serial monitor wiring.
- [x] Create `wokwi/stm32f103/diagram.json` with LED on PC13 and serial monitor wiring.
- [x] Create board-specific `wokwi.toml` files to select firmware ELFs.
- [ ] Validate Wokwi simulation for both boards: LEDs blink and serial output matches expectations.

Definition of done:
- Wokwi simulator starts from VS Code for both boards and shows the expected behavior.

### M4 - Renode Simulation Wiring (STM32F103)

- [x] Create `sim/stm32f103_bluepill/blue_pill.resc` using Renode's built-in platform.
- [ ] Run Renode manually and confirm the virtual platform boots and prints to USART1.
- [ ] Confirm GDB server starts on `localhost:3333`.

Definition of done:
- Renode boots the virtual STM32F103 Blue Pill and the firmware runs.

### M5 - VS Code Build/Run/Debug Automation

- [x] Add `.vscode/tasks.json`:
  - [x] Build C Firmware (ESP32-C3) and (STM32F103).
  - [x] Build Rust Firmware (ESP32-C3) and (STM32F103).
  - [x] Start Renode Simulation (STM32 C) and (STM32 Rust).
  - [x] Stop Renode.
  - [x] Test C Host.
  - [x] Test C Target (ESP32-C3) and (STM32F103).
  - [x] Test Rust Host.
- [x] Add `.vscode/launch.json` for STM32 GDB attach from VS Code.
- [ ] Validate one-click build/test/debug flow from VS Code.

Definition of done:
- All build, test, and debug tasks run successfully from the command palette.

### M6 - Testing Quality Checks

- [x] Add host-side `sum` tests for C.
- [x] Add host-side `sum` tests for Rust.
- [x] Add target-side Unity tests for C.
- [ ] Run all tests and confirm they pass on both boards.

Definition of done:
- Host and target tests pass reliably for both boards.

### M7 - Optional CI Build and Simulation Gate

- [ ] Add a CI workflow that builds all firmware tracks.
- [ ] Add at least one Renode headless smoke check for STM32F103.
- [ ] Add at least one Wokwi-based smoke check or screenshot assertion.
- [ ] Publish logs/artifacts for failed runs.

Definition of done:
- Pull request workflow fails when a build/simulation fails and exposes useful logs.

## 4) Execution Order

1. Fix container build and verify tools (including ARM toolchain).
2. Create PlatformIO config and board-specific firmware files.
3. Update Rust crate for multi-board builds with Cargo features.
4. Wire Wokwi diagrams for both boards and validate visual simulation.
5. Wire Renode script for STM32F103 and validate emulation.
6. Add VS Code tasks + launch for single-command build/simulate/debug.
7. Stabilize test behavior across both boards.
8. Add CI automation (optional but recommended).

## 5) Risks and Mitigations

- Risk: Wokwi extension behavior differs inside a dev container.
- Mitigation: Document host-vs-container usage and keep `diagram.json` editable in a separate VS Code window.

- Risk: Target board mismatch between simulation and physical hardware.
- Mitigation: Clearly document the simulated boards (ESP32-C3-DevKitM-1, STM32F103 Blue Pill) and physical board (Freenove Wrover v3) separately.

- Risk: Cargo feature interactions between ESP32 and STM32 HALs.
- Mitigation: Use `required-features` on `[[bin]]` targets and avoid enabling both board features simultaneously.

- Risk: Renode package source changes or URL breaks.
- Mitigation: Pin Renode version and keep a fallback install path documented.

- Risk: ARM GDB path mismatch in container.
- Mitigation: Provide `arm-none-eabi-gdb` symlink to `gdb-multiarch` and reference it in launch config.

## 6) Acceptance Criteria (Project-Level)

- [ ] Containerized environment is reproducible across machines.
- [ ] Firmware builds without host-specific dependencies for both boards and both languages.
- [ ] Wokwi simulation runs and shows expected LED/serial behavior for both boards.
- [ ] Renode launches the STM32F103 virtual platform and exposes a GDB server reliably.
- [ ] VS Code can attach and debug the STM32F103 firmware with breakpoints.
- [ ] Tests pass on host and target for both boards.
- [ ] Workflow is scriptable for CI.

## 7) Immediate Next Actions

- [x] Confirm board selection and simulation approach (ESP32-C3 Wokwi only; STM32F103 Wokwi + Renode).
- [x] Add STM32F103 firmware files, build configs, and simulation files.
- [ ] Rebuild dev container and verify all tools.
- [ ] Run first builds to validate artifacts and toolchains (`pio run` and `cargo build` for both boards).
- [ ] Validate Wokwi simulation for both boards from VS Code.
- [ ] Validate Renode simulation and GDB debug flow for STM32F103.
- [ ] Add CI workflow for build and simulation checks.
