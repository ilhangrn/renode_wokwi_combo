# Task Plan: demo_renode

Date: 2026-07-29
Project type: PlatformIO firmware + Renode simulation + VS Code Dev Container
# TREE
demo_renode/
├── .devcontainer/
│   ├── devcontainer.json
│   └── Dockerfile
├── firmware-c/
│   ├── src/
│   │   └── main.c
│   └── platformio.ini
├── firmware-rust/
│   ├── src/
│   │   └── main.rs
│   ├── Cargo.toml
│   └── .cargo/
│       └── config.toml
├── sim/
│   ├── esp32c3.repl
│   └── setup.resc
└── README.md

## 1) Current Status (Observed)

- guide.md exists and describes a full reproducible workflow.
- .devcontainer/devcontainer.json exists with PlatformIO and Renode extensions.
- .devcontainer/Dockerfile exists but Renode install URL is incomplete and needs correction.
- platformio.ini is populated for esp32dev (Arduino framework).
- src/main.c contains a working LED blink + serial log loop.
- board_setup.resc is still empty.
- Cargo.toml and src/main.rs were added (parallel Rust firmware track).
- No .vscode task/debug automation is present yet.

## 2) Primary Goal

Build and debug embedded firmware fully inside an isolated dev container, using Renode for deterministic simulation and GDB-based debugging from VS Code.

## 3) Milestones

## M1 - Environment and Toolchain Baseline

- [ ] Fix Renode installation in .devcontainer/Dockerfile (use a valid package source/version).
- [ ] Rebuild and reopen the project in the Dev Container.
- [ ] Verify tools are available in container: platformio, renode, and arm-none-eabi-gdb.
- [ ] Document verified tool versions in project notes.

Definition of done:
- Container builds without manual fixes.
- All required CLI tools resolve from PATH.

## M2 - Firmware Project Bootstrap

- [x] Populate platformio.ini with a target board/environment suitable for Renode.
- [x] Add a minimal firmware app in src/main.c (startup + observable behavior via serial/log).
- [ ] Run first successful build (pio run).
- [ ] Confirm ELF output path for simulator loading.

Definition of done:
- Build succeeds and generates an ELF binary.

## M3 - Renode Simulation Wiring

- [ ] Implement board_setup.resc to:
- [ ] create machine,
- [ ] load platform description,
- [ ] load firmware ELF,
- [ ] start GDB server on port 3333 with autostart disabled.
- [ ] Run Renode script manually and confirm GDB server startup message.

Definition of done:
- Renode boots the virtual platform and waits for debugger attach on localhost:3333.

## M4 - VS Code Build/Run/Debug Automation

- [ ] Add .vscode/tasks.json:
- [ ] build task (PlatformIO build),
- [ ] background Renode task with problem matcher,
- [ ] cleanup task for stopping background simulation.
- [ ] Add .vscode/launch.json for cppdbg attach to localhost:3333.
- [ ] Validate one-click debug flow with F5.

Definition of done:
- F5 performs build, starts Renode, attaches debugger, and supports breakpoints/step execution.

## M5 - Deterministic Debug Quality Checks

- [ ] Verify source-level stepping is stable (debug-oriented build flags if needed).
- [ ] Validate reset/restart cycle and post-debug cleanup.
- [ ] Confirm no orphan Renode processes after debug stop.

Definition of done:
- Repeatable debug session with clean startup/shutdown behavior.

## M6 - Optional CI Simulation Gate

- [ ] Add a CI workflow that builds firmware and runs headless Renode checks.
- [ ] Add at least one smoke-level simulation test or scripted run.
- [ ] Publish logs/artifacts for failed runs.

Definition of done:
- Pull request workflow fails when build/simulation fails and exposes useful logs.

## 4) Execution Order

1. Fix container build and verify tools.
2. Create PlatformIO config and minimal firmware.
3. Wire Renode script and validate manual simulation.
4. Add VS Code tasks + launch for single-command debugging.
5. Stabilize debug behavior and cleanup.
6. Add CI automation (optional but recommended).

## 5) Risks and Mitigations

- Risk: Renode package source changes or URL breaks.
- Mitigation: Pin Renode version and keep a fallback install path documented.

- Risk: Target board/platform mismatch between PlatformIO and Renode model.
- Mitigation: Choose a board with known Renode support first, then iterate.

- Risk: Debugger path mismatch in container.
- Mitigation: Detect debugger path during container startup and reference it in launch config.

## 6) Acceptance Criteria (Project-Level)

- [ ] Containerized environment is reproducible across machines.
- [ ] Firmware builds without host-specific dependencies.
- [ ] Renode launches and exposes GDB server reliably.
- [ ] VS Code can attach and debug with breakpoints.
- [ ] Workflow is scriptable for CI.

## 7) Immediate Next Actions

- [x] Decide target board for first bring-up (currently set to esp32dev in platformio.ini).
- [ ] Run first build to validate artifacts and toolchain (pio run).
- [ ] Choose one primary track for debugging flow (PlatformIO C in src/main.c or Rust in src/main.rs).
- [ ] Implement board_setup.resc for the chosen target and verify GDB server startup.
- [ ] Add .vscode/tasks.json and .vscode/launch.json, then run end-to-end dry run: build -> simulate -> debug attach.
