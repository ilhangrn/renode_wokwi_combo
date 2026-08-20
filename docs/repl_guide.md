# REPL Generation Guide

Some boards do not ship with a ready-to-use Renode `.repl` platform description. This project uses [dts2repl](https://github.com/antmicro/dts2repl) to generate a REPL file from the official Zephyr device-tree sources for the **ESP32-C3-DevKitM** board.

## Files

| File | Purpose |
| --- | --- |
| [sim/esp32c3_devkitm.dts](sim/esp32c3_devkitm.dts) | Project-specific top-level DTS referencing the Zephyr ESP32-C3-DevKitM sources |
| [sim/esp32c3_devkitm_flat.dts](sim/esp32c3_devkitm_flat.dts) | Preprocessed (flattened) DTS produced by `gcc` |
| [sim/esp32c3_devkitm_generated.repl](sim/esp32c3_devkitm_generated.repl) | REPL produced by `dts2repl` (downloads ROM/SVD from the network) |
| [sim/esp32c3_devkitm_generated_offline.repl](sim/esp32c3_devkitm_generated_offline.repl) | Offline-friendly REPL used by [setup.resc](sim/setup.resc) |
| [sim/include/](sim/include/) | Minimal stub headers (kept for fallback/reference) |
| [sim/generate_repl.sh](sim/generate_repl.sh) | One-command script to regenerate the REPLs |
| `/workspaces/zephyr` | Full Zephyr repository cloned from upstream |

## Prerequisites

The `dts2repl` tool is already installed in the dev container:

```bash
/opt/pio-venv/bin/dts2repl --help
```

The generation script expects a Zephyr clone at `/workspaces/zephyr`. If your clone is elsewhere, set the `ZEPHYR_DIR` environment variable.

## Regenerate the REPL

The easiest way is to use the helper script:

```bash
cd sim
./generate_repl.sh
```

This performs the following steps automatically.

### 1. Preprocess the DTS

```bash
cd sim
gcc -E -P -x assembler-with-cpp \
    -I include/ \
    -I /workspaces/zephyr/dts/common \
    -I /workspaces/zephyr/include \
    -I /workspaces/zephyr/dts \
    -I /workspaces/zephyr/dts/riscv/espressif/esp32c3 \
    -I /workspaces/zephyr/dts/vendor/espressif \
    -I /workspaces/zephyr/boards/espressif/esp32c3_devkitm \
    esp32c3_devkitm.dts -o esp32c3_devkitm_flat.dts
```

This expands all `#include` directives and macros into a single flattened DTS file using the real Zephyr headers.

### 2. Generate the REPL

```bash
/opt/pio-venv/bin/dts2repl esp32c3_devkitm_flat.dts -o esp32c3_devkitm_generated.repl
```

`dts2repl` will:

- Map `espressif,riscv` to `CPU.RiscV32`
- Map `espressif,esp32-uart` to `UART.ESP32_UART`
- Map memory nodes to `Memory.MappedMemory`
- Apply the bundled `espressif,esp32c3` overlay, which adds ESP32-C3-specific CSRs, ROM, and peripheral tags

### 3. Create the offline variant

The generated REPL references remote files (ESP32-C3 ROM ELF and an SVD). For offline/container use, the script creates a local copy with those lines disabled. The result is [sim/esp32c3_devkitm_generated_offline.repl](sim/esp32c3_devkitm_generated_offline.repl).

## Use the generated REPL in Renode

[sim/setup.resc](sim/setup.resc) loads the offline REPL by default:

```renode
mach create "esp32-c3"
machine LoadPlatformDescription @esp32c3_devkitm_generated_offline.repl
```

To use the fully automatic REPL (with remote downloads), change the line to:

```renode
machine LoadPlatformDescription @esp32c3_devkitm_generated.repl
```

## Download the ROM for full boot accuracy

The offline REPL skips the ESP32-C3 boot ROM. This is fine for loading and running a pre-linked ELF, but the real boot ROM is required for accurate reset/boot behavior.

To download it manually:

```bash
cd sim
curl -LO https://dl.antmicro.com/projects/renode/esp32c3_rev3_rom.elf-s_556332-d68afeb5bd7ab7904e7d5d3adf4d670df9d19c96
```

Then uncomment the `LoadELF @esp32c3_rev3_rom.elf` line in [sim/esp32c3_devkitm_generated_offline.repl](sim/esp32c3_devkitm_generated_offline.repl).

## What changed from the stub-based REPL

Using the full Zephyr sources instead of the local stub headers gives us:

- Real board model string (`Espressif ESP32C3-DevkitM`)
- Correct 4 MB flash partition layout from [esp32c3_mini_n4.dtsi](esp32c3_mini_n4.dtsi)
- Accurate `chosen` nodes (`zephyr,sram`, `zephyr,console`, `zephyr,flash`, etc.)
- Valid Zephyr macro values (DT_SIZE_K, clock IDs, interrupt source IDs)
- A generated REPL that stays in sync with upstream Zephyr whenever you re-run the script

## Notes and limitations

- Only nodes with known Renode mappings are emitted. The ESP32-C3 interrupt controller (`espressif,esp32-intc`), GPIO, timers, and other peripherals are currently skipped because dts2repl has no model for them.
- The old stub-based files ([sim/esp32c3.dts](sim/esp32c3.dts), [sim/esp32c3_common.dtsi](sim/esp32c3_common.dtsi), [sim/esp32c3_generated.repl](sim/esp32c3_generated.repl), etc.) are kept for reference but are no longer used by [setup.resc](sim/setup.resc).
- For a production project, keep the Zephyr clone updated and re-run [sim/generate_repl.sh](sim/generate_repl.sh) after major Zephyr upgrades.
