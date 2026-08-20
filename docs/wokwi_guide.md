# Wokwi Guide

[Wokwi](https://wokwi.com) is a browser-based and VS Code-integrated electronics simulator. This project uses it to visually verify that the ESP32-C3 firmware blinks the LED on GPIO8 and prints messages over UART.

## Wiring

The circuit is defined in [diagram.json](diagram.json):

- `esp:8` → red LED anode (`led1:A`)
- `esp:GND.1` → LED cathode (`led1:C`)
- `esp:TX` → serial monitor RX
- `esp:RX` → serial monitor TX

```json
{
    "version": 1,
    "author": "DevContainer",
    "editor": "wokwi",
    "parts": [
        {
            "type": "wokwi-led",
            "id": "led1",
            "top": -50,
            "left": 50,
            "attrs": { "color": "red" }
        },
        {
            "type": "board-esp32-c3-devkitm-1",
            "id": "esp",
            "top": 0,
            "left": 0,
            "attrs": {}
        }
    ],
    "connections": [
        ["esp:TX", "$serialMonitor:RX", "", []],
        ["esp:RX", "$serialMonitor:TX", "", []],
        ["esp:8", "led1:A", "green", ["v0"]],
        ["esp:GND.1", "led1:C", "black", ["v0"]]
    ]
}
```

## Firmware selection

The firmware loaded by Wokwi is configured in [wokwi.toml](wokwi.toml). Only one ELF can be active at a time.

### C firmware

```toml
[wokwi]
version = 1
firmware = "firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf"
elf = "firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf"
```

### Rust firmware

```toml
[wokwi]
version = 1
firmware = "firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust"
elf = "firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust"
```

## Build the firmware

### C

```bash
cd firmware-c
pio run
```

Output:

```
firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

### Rust

```bash
cd firmware-rust
cargo build --release
```

Output:

```
firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust
```

## Start the simulator

### In VS Code

1. Open [diagram.json](diagram.json).
2. Make sure [wokwi.toml](wokwi.toml) points to the firmware you want to simulate.
3. Run the command **Wokwi: Start Simulator** (`Ctrl+Shift+P` → type "Wokwi").
4. The simulator panel opens showing the board and the LED.
5. Open the serial monitor to see the firmware output.

### In a browser

1. Go to [https://wokwi.com](https://wokwi.com).
2. Create a new ESP32-C3 project.
3. Upload or paste the firmware ELF and diagram.
4. Start the simulation.

> **Note:** The project notes mention that [diagram.json](diagram.json) should be edited in a separate VS Code window outside this container, because Wokwi may block editing inside the dev container.

## Expected behavior

After starting the simulation:

1. The red LED connected to GPIO8 blinks once per second.
2. The serial monitor shows the firmware boot message:

   ```text
   Hello from ESP32-C3 C Firmware!
   sum(10, 32) = 42
   ```

   or for Rust:

   ```text
   Hello from ESP32-C3 Rust Firmware!
   sum(10, 32) = 42
   ```

3. Every second a new line appears:

   ```text
   Blink C loop executed. Pin 8 state: 1
   Blink C loop executed. Pin 8 state: 0
   ```

## Troubleshooting

| Symptom | Cause | Fix |
| --- | --- | --- |
| LED does not blink | Wrong ELF selected | Check [wokwi.toml](wokwi.toml) and rebuild |
| No serial output | Monitor not open or wrong baud rate | Open serial monitor; baud is `115200` |
| Cannot edit diagram.json | Wokwi blocks editing inside container | Open the file in another VS Code window |
| Simulator does not start | Wokwi extension not installed | Install the Wokwi VS Code extension |

## Limitations

- Wokwi is interactive and visual, but it does **not** support GDB debugging.
- For breakpoints, stepping, and deterministic test runs, use [Renode](renode_guide.md) instead.
