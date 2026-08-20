# Renode Guide

[Renode](https://renode.io) is a deterministic machine emulator. In this project it emulates the ESP32-C3, loads the compiled firmware ELF, and exposes a GDB server for source-level debugging.

The platform description is generated from a Zephyr device-tree source using [dts2repl](https://github.com/antmicro/dts2repl). See [repl_guide.md](repl_guide.md) for how the REPL is created.

## Start the simulation

Make sure the firmware is built first:

```bash
cd firmware-c
pio run
```

Then start Renode from the `sim/` directory:

```bash
cd sim
renode setup.resc
```

[sim/setup.resc](sim/setup.resc) performs the following steps:

1. Creates a machine named `esp32-c3`.
2. Loads the platform description from [sim/esp32c3_devkitm_generated_offline.repl](sim/esp32c3_devkitm_generated_offline.repl). See [repl_guide.md](repl_guide.md) for how this REPL is generated from the official Zephyr ESP32-C3-DevKitM device tree.
3. Loads the firmware ELF into the virtual machine.
4. Opens the UART analyzer window.
5. Starts a GDB server on `localhost:3333`.
6. Prints a configuration message.

The default script loads the C firmware:

```renode
$bin?=@../firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

To use the Rust firmware, comment out the C line and uncomment the Rust line in [sim/setup.resc](sim/setup.resc):

```renode
$bin?=@../firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust
```

> **Important:** [sim/setup.resc](sim/setup.resc) uses relative paths, so it must be started from the `sim/` directory. The VS Code task already does this; if you run Renode manually, use `cd sim` first.

## Run the virtual CPU

After Renode starts, emulation is paused. Start it from the Renode monitor:

```renode
start
```

Or start it from GDB after attaching:

```gdb
(gdb) monitor start
```

The UART analyzer will show the firmware boot messages, for example:

```text
Hello from ESP32-C3 C Firmware!
sum(10, 32) = 42
Blink C loop executed. Pin 8 state: 1
...
```

## Stop the simulation

In the Renode monitor:

```renode
quit
```

Or from another terminal:

```bash
pkill -f "renode.*setup.resc"
```

## Debug with GDB

### C firmware

```bash
riscv32-esp-elf-gdb \
  -ex "target remote localhost:3333" \
  -ex "monitor start" \
  firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

### Rust firmware

```bash
riscv32-esp-elf-gdb \
  -ex "target remote localhost:3333" \
  -ex "monitor start" \
  firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust
```

The GDB path in this container is:

```text
/root/.platformio/packages/toolchain-riscv32-esp/bin/riscv32-esp-elf-gdb
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

Build and load the firmware, then start emulation. Check the UART analyzer for:

```text
Hello from ESP32-C3 C Firmware!
sum(10, 32) = 42
```

If `sum(10, 32)` prints `42`, the `sum` library works on the simulated target.

### Unity target tests

Build the Unity test binary:

```bash
cd firmware-c
pio test --without-uploading
```

Find the generated test ELF:

```bash
find .pio/build/esp32-c3-devkitm-1 -name '*.elf' -type f
```

Point Renode at the test ELF in [sim/setup.resc](sim/setup.resc), then start emulation. The UART analyzer shows Unity output:

```text
test_sum.cpp:15:test_sum_positive_numbers:PASS
...
-----------------------
4 Tests 0 Failures 0 Ignored
```

## Headless Renode

For CI or automated checks, run Renode without the GUI:

```bash
renode --disable-xwt --console setup.resc
```

Use the `--port` option or a script to capture UART output for assertions.

## UART output in console mode

If Renode cannot start its GUI (common in containers), it falls back to console mode. In that case the UART analyzer window does not open, but UART data is still captured:

- A log file `sim/uart0.log` is created and overwritten on each run.
- You can tail it while the simulation runs:

  ```bash
  cd sim
  tail -f uart0.log
  ```

- Alternatively, read the file after starting emulation:

  ```bash
  cat sim/uart0.log
  ```

> **Note:** The ESP32-C3 model in this project is intentionally minimal. It is intended for learning how to load an ELF and attach GDB, not for bit-accurate peripheral emulation. If the firmware does not print, verify that `Serial`/`println` writes to the expected UART0 address and that the clock/interrupt setup required by the real HAL is not causing early hangs.

## VS Code integration

The launch configurations in [.vscode/launch.json](.vscode/launch.json) automate:

1. Starting Renode in the background (`preLaunchTask`).
2. Attaching GDB to `localhost:3333`.
3. Running `monitor start` to begin emulation.
4. Stopping Renode when debugging ends (`postDebugTask`).

Select **Debug C Firmware in Renode** or **Debug Rust Firmware in Renode** and press `F5`.

## Troubleshooting

| Symptom | Cause | Fix |
| --- | --- | --- |
| `Could not find file '${ORIGIN}/esp32c3.repl'` | `${ORIGIN}` is not expanded when the script is included from an absolute path | Start Renode from the `sim/` directory, or use the VS Code task |
| `There was an error executing command 'sysbus LoadELF $bin'` / signature mismatch | The firmware ELF does not exist at the configured path | Build the firmware first (`pio run` or `cargo build --release`) |
| `Cannot load ELF` | ELF path in `setup.resc` is wrong or firmware not built | Build the firmware and check the path |
| `Unable to connect to localhost:3333` | Renode is not running or port is in use | Start Renode first or kill stale processes |
| GDB cannot find source | ELF was built without `-g3` | Rebuild with debug flags |
| Orphan Renode process after debug | Cleanup task did not run | Run `pkill -f "renode.*setup.resc"` |
