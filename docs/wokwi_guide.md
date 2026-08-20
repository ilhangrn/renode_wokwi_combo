# Wokwi Guide

[Wokwi](https://wokwi.com) is a browser-based and VS Code-integrated electronics simulator. This project uses it to visually verify that the firmware blinks the on-board LED and prints messages over UART for both supported boards.

Board-specific Wokwi files live under [wokwi/](wokwi/):

- [wokwi/esp32c3/](wokwi/esp32c3/) — ESP32-C3-DevKitM-1
- [wokwi/stm32f103/](wokwi/stm32f103/) — STM32F103 Blue Pill

## ESP32-C3 wiring

The circuit is defined in [wokwi/esp32c3/diagram.json](wokwi/esp32c3/diagram.json):

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

## STM32F103 Blue Pill wiring

The circuit is defined in [wokwi/stm32f103/diagram.json](wokwi/stm32f103/diagram.json):

- `stm:PC13` → red LED anode (`led1:A`)
- `stm:GND.1` → LED cathode (`led1:C`)
- `stm:PA9` → serial monitor RX (USART1 TX)
- `stm:PA10` → serial monitor TX (USART1 RX)

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
            "type": "board-stm32-bluepill",
            "id": "stm",
            "top": 0,
            "left": 0,
            "attrs": {}
        }
    ],
    "connections": [
        ["stm:PA9", "$serialMonitor:RX", "", []],
        ["stm:PA10", "$serialMonitor:TX", "", []],
        ["stm:PC13", "led1:A", "green", ["v0"]],
        ["stm:GND.1", "led1:C", "black", ["v0"]]
    ]
}
```

## Firmware selection

The firmware loaded by Wokwi is configured in the board-specific `wokwi.toml`. Only one ELF can be active at a time.

### ESP32-C3

[wokwi/esp32c3/wokwi.toml](wokwi/esp32c3/wokwi.toml):

```toml
[wokwi]
version = 1
firmware = "../../firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf"
elf = "../../firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf"
```

To use the Rust ELF:

```toml
firmware = "../../firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust-esp32c3"
elf = "../../firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust-esp32c3"
```

### STM32F103 Blue Pill

[wokwi/stm32f103/wokwi.toml](wokwi/stm32f103/wokwi.toml):

```toml
[wokwi]
version = 1
firmware = "../../firmware-c/.pio/build/stm32f103_bluepill/firmware.elf"
elf = "../../firmware-c/.pio/build/stm32f103_bluepill/firmware.elf"
```

To use the Rust ELF:

```toml
firmware = "../../firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103"
elf = "../../firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103"
```

## Build the firmware

### ESP32-C3 C

```bash
cd firmware-c
pio run -e esp32-c3-devkitm-1
```

Output:

```
firmware-c/.pio/build/esp32-c3-devkitm-1/firmware.elf
```

### ESP32-C3 Rust

```bash
cd firmware-rust
cargo build --release --target riscv32imac-unknown-none-elf --features esp32c3 --bin firmware-rust-esp32c3
```

Output:

```
firmware-rust/target/riscv32imac-unknown-none-elf/release/firmware-rust-esp32c3
```

### STM32F103 C

```bash
cd firmware-c
pio run -e stm32f103_bluepill
```

Output:

```
firmware-c/.pio/build/stm32f103_bluepill/firmware.elf
```

### STM32F103 Rust

```bash
cd firmware-rust
cargo build --release --target thumbv7m-none-eabi --features stm32f103 --bin firmware-rust-stm32f103
```

Output:

```
firmware-rust/target/thumbv7m-none-eabi/release/firmware-rust-stm32f103
```

## Start the simulator

### In VS Code

1. Open the `diagram.json` for the board you want to simulate:
   - ESP32-C3: [wokwi/esp32c3/diagram.json](wokwi/esp32c3/diagram.json)
   - STM32F103: [wokwi/stm32f103/diagram.json](wokwi/stm32f103/diagram.json)
2. Make sure the corresponding `wokwi.toml` points to the firmware you want to simulate.
3. Run the command **Wokwi: Start Simulator** (`Ctrl+Shift+P` → type "Wokwi").
4. The simulator panel opens showing the board and the LED.
5. Open the serial monitor to see the firmware output.

### In a browser

1. Go to [https://wokwi.com](https://wokwi.com).
2. Create a new project for the board you want to simulate (ESP32-C3 or STM32F103 Blue Pill).
3. Upload or paste the firmware ELF and diagram.
4. Start the simulation.

> **Note:** The project notes mention that `diagram.json` should be edited in a separate VS Code window outside this container, because Wokwi may block editing inside the dev container.

## Expected behavior

### ESP32-C3

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

### STM32F103 Blue Pill

1. The red LED connected to PC13 blinks once per second.
2. The serial monitor shows the firmware boot message:

   ```text
   Hello from STM32F103 C Firmware!
   sum(10, 32) = 42
   ```

   or for Rust:

   ```text
   Hello from STM32F103 Rust Firmware!
   sum(10, 32) = 42
   ```

3. Every second a new line appears:

   ```text
   Blink STM32 loop executed. Pin 13 state: 1
   Blink STM32 loop executed. Pin 13 state: 0
   ```

## Troubleshooting

| Symptom | Cause | Fix |
| --- | --- | --- |
| LED does not blink | Wrong ELF selected | Check the board-specific `wokwi.toml` and rebuild |
| No serial output | Monitor not open or wrong baud rate | Open serial monitor; baud is `115200` |
| Cannot edit diagram.json | Wokwi blocks editing inside container | Open the file in another VS Code window |
| Simulator does not start | Wokwi extension not installed | Install the Wokwi VS Code extension |

## Limitations

- Wokwi is interactive and visual, but it does **not** support GDB debugging.
- For breakpoints, stepping, and deterministic machine emulation on the STM32F103 Blue Pill, use [Renode](renode_guide.md) instead.
