# Wokwi Components and Parts

Wokwi supports microcontrollers, sensors, input controls, displays, motors,
logic devices, and virtual test equipment. This list follows the official
[Supported Hardware](https://docs.wokwi.com/getting-started/supported-hardware)
catalog.

Support for a part means Wokwi can simulate it. Firmware must still initialize
the correct GPIO peripheral and implement or include the part's communication
protocol.

## Microcontrollers and Boards

| Family | Supported devices |
| --- | --- |
| STM32 | STM32F103C8 Blue Pill, STM32C031, STM32L031 |
| AVR | ATmega328P, Arduino Uno, Arduino Nano, ATmega2560, Arduino Mega, ATtiny85 |
| Raspberry Pi | RP2040 and Raspberry Pi Pico |
| ESP32 Xtensa | ESP32, ESP32-S2, ESP32-S3 |
| ESP32 RISC-V | ESP32-C3, C5, C6, C61, H2, P4, S31 |

Some newer ESP32 devices have beta or alpha support. Check the official catalog
for current status.

This repository uses the `board-stm32-bluepill` board.

## Sensors

| Component | Measures or detects | Interface |
| --- | --- | --- |
| HC-SR04 | Ultrasonic distance | Trigger and echo GPIO |
| DHT22 | Temperature and humidity | Single digital data wire |
| DS1307 RTC | Date and time, with NV SRAM | I2C |
| PIR motion sensor | Movement of warm objects | Digital output |
| NTC thermistor | Temperature | Analog voltage |
| DS18B20 | Temperature | One-Wire |
| BMP180 | Barometric pressure and temperature | I2C |
| MPU6050 | 3-axis acceleration, rotation, and temperature | I2C |
| Photoresistor/LDR | Light level | Analog voltage |
| MQ2 gas sensor | Combustible gas concentration | Analog/digital output |
| HX711 load cell | Weight and force | Clock and data GPIO |
| MFRC522 RFID reader | RFID/NFC cards | SPI |

## Input Controls

| Component | Typical use |
| --- | --- |
| Pushbutton, 6 mm or 12 mm | Momentary digital input |
| SPDT slide switch | Persistent two-position input |
| 8-position DIP switch | Configuration bits or parallel input |
| 4x4 keypad | Numeric or command entry |
| Analog joystick | Two analog axes and one pushbutton |
| Potentiometer | Adjustable analog voltage |
| Slide potentiometer | Adjustable linear analog voltage |
| KY-040 rotary encoder | Rotation and pushbutton input |

## LEDs and Lighting

| Component | Description |
| --- | --- |
| Standard LED | Single-color 5 mm LED |
| RGB LED | Independent red, green, and blue channels |
| LED bar graph | Ten LED segments |
| WS2812/NeoPixel LED | Individually addressable RGB LED |
| WS2812 LED ring | Circular addressable LED array |
| WS2812 LED strip | Linear addressable LED array |
| WS2812 LED matrix | Grid of addressable LEDs |
| NeoPixel meter | NeoPixel frame-rate and power monitor |
| NLSF595 LED driver | SPI tri-color LED driver |

Standard LED colors include red, green, blue, yellow, orange, white, and purple.
Set the color through the part's `attrs` object:

```json
{
	"type": "wokwi-led",
	"id": "led1",
	"top": 120,
	"left": -60,
	"attrs": {
		"color": "green"
	}
}
```

## Displays

| Component | Interface or format |
| --- | --- |
| LCD 1602 | 16 columns by 2 rows, parallel or I2C adapter |
| LCD 2004 | 20 columns by 4 rows, parallel or I2C adapter |
| Nokia 5110 LCD | 84x48 monochrome, SPI |
| ILI9341 TFT LCD | 240x320 color, SPI |
| ILI9341 touch LCD | TFT plus FT6206 capacitive touch over I2C |
| SSD1306 OLED | 128x64 monochrome, I2C |
| SH1107 OLED | 128x128 monochrome, I2C |
| MAX7219 dot matrix | 8x8 LED matrix, serial interface |
| Seven-segment display | One to four digits |
| TM1637 display | Four-digit module |
| 2.9-inch e-paper | Low-refresh persistent display |
| PAL TV | Monochrome analog PAL display |

## Motors and Motion

| Component | Description |
| --- | --- |
| Micro servo | Position-controlled servo motor |
| Bipolar stepper motor | Two-coil stepper motor |
| A4988 | Bipolar stepper motor driver |
| Biaxial stepper motor | Two concentric stepper motors |

## Communication Parts

| Component | Description |
| --- | --- |
| IR receiver | 38 kHz infrared receiver |
| IR remote | 20-key, 38 kHz infrared remote |
| microSD card | SPI storage device |

UART, I2C, and SPI connections between a board and parts are created directly
with wires. The serial monitor is a virtual UART endpoint and does not require a
physical component.

## Digital Logic

| Component | Function |
| --- | --- |
| NOT | Inverter |
| AND | Logical AND |
| OR | Logical OR |
| XOR | Exclusive OR |
| NAND | Inverted AND |
| MUX | Multiplexer |
| D flip-flop | Clocked one-bit storage |
| DSR flip-flop | D flip-flop with set/reset |
| 74HC595 | 8-bit serial-in, parallel-out shift register |
| 74HC165 | 8-bit parallel-in, serial-out shift register |

## General Parts and Instruments

| Component | Typical use |
| --- | --- |
| Resistor | Pull-up, pull-down, or LED current limiting |
| Piezo buzzer | Tones and alarms |
| Clock generator | Configurable digital clock source |
| Relay module | MCU-controlled switching |
| DPDT relay | Double-pole, double-throw switching |
| Breadboard | Visual circuit layout and wiring |
| Logic analyzer | Capture up to eight digital channels |
| Text element | Labels and diagram annotations |

Useful virtual endpoints also include:

- Serial monitor for UART input and output
- Logic analyzer for timing and protocol inspection
- GDB integration for source-level debugging where supported

## Adding a Part

Use either method:

1. Open the Wokwi diagram editor, click **Add part**, select a component, and
	 draw its connections.
2. Add the component manually to the `parts` array and its wires to the
	 `connections` array in `diagram.json`.

A connection has the form:

```json
[
	"stm32:C13",
	"led1:A",
	"green",
	["h0"]
]
```

The first two values are pin endpoints. The third is wire color. The final array
contains optional wire-routing instructions.

## STM32F103C8 Interface Notes

Common Blue Pill pins include:

| Interface | Default pins |
| --- | --- |
| USART1 | PA9 TX, PA10 RX |
| I2C1 | PB6 SCL, PB7 SDA |
| SPI1 | PA5 SCK, PA6 MISO, PA7 MOSI, PA4 NSS |
| SWD | PA13 SWDIO, PA14 SWCLK |
| User LED | PC13, active low on most Blue Pill boards |

Pins can often be remapped through STM32 alternate-function configuration.
Avoid reusing PA13 and PA14 when debugging through DAPLink.

## Simulation Limits

- Wokwi models documented behavior, not every electrical characteristic.
- Unsupported peripherals inside an MCU may behave differently or be absent.
- Analog behavior is simplified compared with physical components.
- Timing can differ from real hardware under heavy simulation load.
- A library may assume a board or pin layout different from the Blue Pill.

Use Wokwi for fast functional testing, then verify timing, voltage, current, and
signal integrity on physical hardware.
