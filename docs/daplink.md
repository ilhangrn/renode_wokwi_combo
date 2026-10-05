# DAPLink v2 and pyOCD Guide for STM32F103C8 Blue Pill

This guide flashes and debugs the CubeIDE C firmware on a physical Blue Pill
using a DAPLink v2 CMSIS-DAP probe, pyOCD, and the VS Code Cortex-Debug
extension.

The firmware used by both pyOCD and Wokwi is:

```text
blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf
```

pyOCD flashes this ELF to hardware. Wokwi loads the same ELF into its simulator.
Their configuration files are separate.

## Requirements

- STM32F103C8 Blue Pill
- DAPLink v2 or another CMSIS-DAP probe
- pyOCD
- Arm GNU toolchain, including `arm-none-eabi-gdb`
- VS Code Cortex-Debug extension

Verify the tools:

```sh
pyocd --version
arm-none-eabi-gdb --version
```

## Wiring

| DAPLink | Blue Pill | Purpose |
| --- | --- | --- |
| SWDIO | PA13 | SWD data |
| SWCLK | PA14 | SWD clock |
| GND | GND | Common ground |
| nRESET | NRST / R | Reset and connect-under-reset |
| VTref | 3V3 | Target-voltage sensing |

Keep `BOOT0=0` for normal operation. The `nRESET` connection is strongly
recommended because it lets pyOCD recover a target before its firmware starts.

Power the Blue Pill from one source only. If it is powered separately, connect
its 3.3 V rail to the probe's voltage-sense/VTref input, not to another power
output. Check the probe documentation before using a pin labelled `3V3` as a
power source.

## Install STM32F103C8 Target Support

The DAPLink firmware may identify itself as a NUCLEO-F103RB:

```text
Arm DAPLink CMSIS-DAP ... stm32f103rb
```

That is the board profile stored in the probe firmware, not the Blue Pill MCU.
Always override it with the real target, `stm32f103c8`.

Check the probe and install the ST device family pack:

```sh
pyocd list
pyocd pack find STM32F103C8
pyocd pack install STM32F103C8
pyocd list --targets | grep -i stm32f103c8
```

The last command should list `stm32f103c8` from `Keil.STM32F1xx_DFP`.

## Keep SWD Enabled in Firmware

In STM32CubeMX, open **System Core > SYS** and set **Debug** to
**Serial Wire**. This reserves PA13 and PA14 and prevents generated code from
disabling SWD.

The generated `HAL_MspInit()` must keep SWD enabled. Disabling JTAG alone is
safe:

```c
__HAL_AFIO_REMAP_SWJ_NOJTAG();
```

Do not use this setting when the board must remain debuggable:

```c
__HAL_AFIO_REMAP_SWJ_DISABLE();
```

That macro disables both JTAG and SWD. After such firmware starts, pyOCD will
usually report `SWD/JTAG communication failure (No ACK)`.

The CubeMX project also records this choice as:

```text
SYS.Debug=Serial_Wire
```

## Build the Firmware

From the repository root:

```sh
make -C blue_cube_proj/bluepill_demo/Debug all
```

Expected output includes:

```text
Finished building target: bluepill_demo.elf
```

If the installed Arm GCC rejects `-fcyclomatic-complexity`, remove that option
from these generated rules or regenerate the project with a compatible
STM32CubeIDE toolchain:

```text
blue_cube_proj/bluepill_demo/Debug/Core/Src/subdir.mk
blue_cube_proj/bluepill_demo/Debug/Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
```

## Flash with pyOCD

Normal flash command:

```sh
pyocd flash -t stm32f103c8 \
	blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf
```

For initial recovery, or when the existing firmware disabled SWD, connect
`nRESET` and use a low clock with connect-under-reset:

```sh
pyocd flash -t stm32f103c8 -f 100000 \
	-O connect_mode=under-reset \
	blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf
```

Successful output shows erase and programming progress reaching 100%.

### Recovery Without an nRESET Wire

1. Set the Blue Pill `BOOT0` jumper to `1`.
2. Power-cycle or reset the board so it starts the ROM bootloader.
3. Run the normal pyOCD flash command.
4. Set `BOOT0` back to `0`.
5. Power-cycle the board.

Connecting `nRESET` is more reliable for normal debugging.

## Configure Cortex-Debug

Install the **Cortex-Debug** VS Code extension. Add this configuration to the
`configurations` array in `.vscode/launch.json`:

```json
{
		"name": "Debug Blue Pill (DAPLink / pyOCD)",
		"type": "cortex-debug",
		"request": "launch",
		"servertype": "pyocd",
		"cwd": "${workspaceFolder}",
		"executable": "${workspaceFolder}/blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf",
		"targetId": "stm32f103c8",
		"interface": "swd",
		"overrideGDBServerStartedRegex": "GDB server (?:started (?:at|on)|listening on) port",
		"runToEntryPoint": "main"
}
```

Use `targetId`, not `device`. Cortex-Debug converts `targetId` to pyOCD's
`--target stm32f103c8` argument.

The regex override handles both old and current pyOCD startup messages. Without
it, Cortex-Debug 1.12.1 can report a timeout even though pyOCD is already
listening successfully.

## Start a Debug Session

1. Build the firmware.
2. Connect and power the Blue Pill and DAPLink.
3. Open **Run and Debug** with `Cmd+Shift+D` on macOS.
4. Select **Debug Blue Pill (DAPLink / pyOCD)**.
5. Press `F5`.

Cortex-Debug starts pyOCD, programs the ELF, launches GDB, and runs to `main`.
You can then set breakpoints, step through code, and inspect variables.

## Troubleshooting

### `Target type stm32f103c8 not recognized`

Install the device pack:

```sh
pyocd pack install STM32F103C8
```

### `SWD/JTAG communication failure (No ACK)`

Check all of the following:

- Blue Pill is powered.
- Probe and target share ground.
- SWDIO goes to PA13 and SWCLK goes to PA14.
- `nRESET` is connected for connect-under-reset.
- Firmware uses `__HAL_AFIO_REMAP_SWJ_NOJTAG()`, not
	`__HAL_AFIO_REMAP_SWJ_DISABLE()`.
- Retry the low-frequency connect-under-reset flash command.

### `PyOCD GDB Server: Timeout`

First run pyOCD directly on spare ports:

```sh
pyocd gdbserver --target stm32f103c8 \
	--port 50020 --telnet-port 50021
```

If it prints `GDB server listening on port 50020`, hardware is working. Add the
`overrideGDBServerStartedRegex` property shown in the launch configuration.
Stop the direct server with `Ctrl+C` before starting VS Code debugging.

### Probe Is Busy

Stop other debug sessions and check for a stale server:

```sh
pgrep -fl 'pyocd.*gdbserver'
```

Only one pyOCD process should use the DAPLink probe at a time.

## Wokwi

Wokwi uses the same ELF through `sim/wokwi/stm32f103/wokwi.toml`:

```toml
firmware = "../../../blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf"
elf = "../../../blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf"
```

Wokwi does not use pyOCD or `.vscode/launch.json`; those are for physical
hardware debugging.
