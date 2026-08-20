# Renode Guide

[Renode](https://renode.io) is a deterministic machine emulator. In this project it emulates the **STM32F103 Blue Pill**, loads the compiled firmware ELF, and exposes a GDB server for source-level debugging.

The ESP32-C3 target is **not supported by Renode**, so Renode is only used for the STM32F103. The previous ESP32-C3 Renode setup is kept at the end of this guide as an archived reference.

## Start the simulation

Make sure the STM32 firmware is built first. From the repository root:

```bash
cd firmware-c
pio run -e stm32f103_bluepill
```

Then start Renode from the STM32 simulation directory:

```bash
cd ../sim/stm32f103_bluepill
renode setup.resc
```

[sim/stm32f103_bluepill/setup.resc](sim/stm32f103_bluepill/setup.resc) performs the following steps:

1. Creates a machine named `stm32f103_bluepill`.
2. Loads Renode's built-in STM32F103 Blue Pill platform description.
3. Loads the firmware ELF into the virtual machine.
4. Sets the vector table offset to `Reset_Handler`.
5. Opens the USART1 analyzer window.
6. Starts a GDB server on `localhost:3333`.
7. Starts emulation.

The default script loads the C firmware:

```renode
$bin?=@../../firmware-c/.pio/build/stm32f103_bluepill/firmware.elf
```

To use the Rust firmware, comment out the C line and uncomment the Rust line in [sim/stm32f103_bluepill/setup.resc](sim/stm32f103_bluepill/setup.resc):

```renode
$bin?=@../../firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103
```

> **Important:** [sim/stm32f103_bluepill/setup.resc](sim/stm32f103_bluepill/setup.resc) uses relative paths, so it must be started from the `sim/stm32f103_bluepill/` directory. The VS Code task already does this; if you run Renode manually, use `cd sim/stm32f103_bluepill` first.

## Run the virtual CPU

[sim/stm32f103_bluepill/setup.resc](sim/stm32f103_bluepill/setup.resc) calls `start`, so emulation begins automatically. If you attach GDB before `start`, you can control execution from the debugger.

Or start/pause emulation from GDB after attaching:

```gdb
(gdb) monitor start
(gdb) monitor pause
```

The USART1 analyzer will show the firmware boot messages, for example:

```text
Hello from STM32F103 C Firmware!
sum(10, 32) = 42
Blink STM32 loop executed. Pin 13 state: 1
...
```

## Stop the simulation

In the Renode monitor:

```renode
quit
```

Or from another terminal:

```bash
pkill -f "renode.*stm32f103_bluepill/setup.resc"
```

## Debug with GDB

The container provides `arm-none-eabi-gdb` (a symlink to `gdb-multiarch`).

### C firmware

```bash
arm-none-eabi-gdb \
  -ex "target remote localhost:3333" \
  firmware-c/.pio/build/stm32f103_bluepill/firmware.elf
```

### Rust firmware

```bash
arm-none-eabi-gdb \
  -ex "target remote localhost:3333" \
  firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103
```

The GDB path in this container is:

```text
/usr/local/bin/arm-none-eabi-gdb
```

### Common GDB commands

```gdb
(gdb) load              # reload the ELF
(gdb) break setup       # break in Arduino setup()
(gdb) break loop
(gdb) break main        # break in Rust main (mangled name may differ)
(gdb) continue
(gdb) step
(gdb) next
(gdb) info registers
(gdb) backtrace
(gdb) monitor reset     # reset the virtual machine
(gdb) monitor start     # start emulation
(gdb) monitor pause     # pause emulation
(gdb) quit
```

## Run tests in Renode

### Smoke test: verify the application runs

Build and load the firmware, then start emulation. Check the USART1 analyzer for:

```text
Hello from STM32F103 C Firmware!
sum(10, 32) = 42
```

If `sum(10, 32)` prints `42`, the `sum` library works on the simulated target.

### Unity target tests

Build the Unity test binary for STM32:

```bash
cd firmware-c
pio test -e stm32f103_bluepill --without-uploading
```

Find the generated test ELF:

```bash
find .pio/build/stm32f103_bluepill -name '*.elf' -type f
```

Point Renode at the test ELF in [sim/stm32f103_bluepill/setup.resc](sim/stm32f103_bluepill/setup.resc), then start emulation. The USART1 analyzer shows Unity output:

```text
test_sum.cpp:15:test_sum_positive_numbers:PASS
...
-----------------------
4 Tests 0 Failures 0 Ignored
```

## Headless Renode

For CI or automated checks, run Renode without the GUI:

```bash
cd sim/stm32f103_bluepill
renode --disable-xwt --console setup.resc
```

Use the `--port` option or a script to capture USART output for assertions.

## VS Code integration

The launch configurations in [.vscode/launch.json](.vscode/launch.json) automate:

1. Starting Renode in the background (`preLaunchTask`).
2. Attaching GDB to `localhost:3333`.
3. Stopping Renode when debugging ends (`postDebugTask`).

Select **Debug STM32 C Firmware in Renode** or **Debug STM32 Rust Firmware in Renode** and press `F5`.

## Troubleshooting

| Symptom | Cause | Fix |
| --- | --- | --- |
| `Could not find file 'platforms/boards/stm32f103_bluepill.repl'` | Wrong Renode platform path or missing built-in platform | Verify Renode version and platform path |
| `There was an error executing command 'sysbus LoadELF $bin'` / signature mismatch | The firmware ELF does not exist at the configured path | Build the firmware first (`pio run -e stm32f103_bluepill` or `cargo build ...`) |
| `Cannot load ELF` | ELF path in `setup.resc` is wrong or firmware not built | Build the firmware and check the path |
| `Unable to connect to localhost:3333` | Renode is not running or port is in use | Start Renode first or kill stale processes |
| GDB cannot find source | ELF was built without `-g3` | Rebuild with debug flags |
| Orphan Renode process after debug | Cleanup task did not run | Run `pkill -f "renode.*stm32f103_bluepill/setup.resc"` |

---

# Archived: ESP32-C3 Renode setup

> The following section documents the previous ESP32-C3 Renode setup. The ESP32-C3-DevKitM-1 board is **not supported by Renode** and the `sim/` folder no longer contains ESP32 scripts. This content is kept only for reference.

[Renode](https://renode.io) is a deterministic machine emulator. The archived setup emulated the ESP32-C3, loaded the compiled firmware ELF, and exposed a GDB server for source-level debugging.

The platform description was generated from a Zephyr device-tree source using [dts2repl](https://github.com/antmicro/dts2repl). See [repl_guide.md](repl_guide.md) for how the REPL was created.

## Start the simulation (archived)

```bash
cd firmware-c
pio run
```

Then start Renode from the `sim/` directory:

```bash
cd sim
renode setup.resc
```

The archived `sim/setup.resc` performed the following steps:

1. Created a machine named `esp32-c3`.
2. Loaded the platform description from `sim/esp32c3_devkitm_generated_offline.repl`.
3. Loaded the firmware ELF into the virtual machine.
4. Opened the UART analyzer window.
5. Started a GDB server on `localhost:3333`.

The default script loaded the C firmware:

```renode
$bin?=@../firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

To use the Rust firmware:

```renode
$bin?=@../firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust
```

## Debug with GDB (archived)

```bash
riscv32-esp-elf-gdb \
  -ex "target remote localhost:3333" \
  -ex "monitor start" \
  firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

The GDB path in this container was:

```text
/root/.platformio/packages/toolchain-riscv32-esp/bin/riscv32-esp-elf-gdb
```
