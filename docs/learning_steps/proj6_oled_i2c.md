# Project 6: SSD1306 OLED over I2C

## Goal

Initialize the SSD1306 OLED at address `0x3C` through I2C1 and display changing
application data.

## Concepts

- I2C addressing and bus transactions
- Device initialization sequences
- Command and data modes
- Framebuffers
- Logic-analyzer protocol decoding

## Existing Wokwi Wiring

The project diagram already contains:

- PB6 to OLED SCL
- PB7 to OLED SDA
- 3.3 V to OLED VCC
- GND to OLED GND
- Analyzer channels named `I2C_SCL` and `I2C_SDA`

## CubeMX Steps

1. Enable I2C1.
2. Confirm PB6 is SCL and PB7 is SDA.
3. Configure standard mode at 100 kHz.
4. Regenerate code.
5. Confirm Serial Wire remains enabled.

## Address Rule

The display's 7-bit address is `0x3C`. STM32 HAL transfer functions expect it
shifted left by one:

```c
#define SSD1306_ADDRESS (0x3CU << 1)
```

## Firmware Steps

Build the driver in small stages:

1. Call `HAL_I2C_IsDeviceReady()` and report success through UART.
2. Write an `ssd1306_write_command(uint8_t command)` function.
3. Write an `ssd1306_write_data(const uint8_t *data, size_t length)` function.
4. Send the SSD1306 initialization sequence.
5. Clear the display RAM.
6. Draw a fixed checkerboard or border pattern.
7. Add a small font or reusable driver and display ADC/button values.

Use finite I2C timeouts. Check every HAL return status and report failures.

The control byte is normally:

- `0x00` for commands
- `0x40` for display data

A 128x64 monochrome framebuffer requires:

$$
128 \times 64 / 8 = 1024\text{ bytes}
$$

This fits in the STM32F103C8's RAM, but it is large enough to track deliberately.

## Wokwi Verification

1. Start simulation with terminal mode enabled.
2. Confirm UART reports the device at address `0x3C`.
3. Confirm the OLED shows the test pattern.
4. Stop simulation and open the VCD capture.
5. Decode I2C in PulseView or inspect SCL/SDA edges in Surfer.
6. Identify the address byte, command control byte, and acknowledgment bits.

## Debug Exercise

Set breakpoints around initialization, not during each byte transfer. Inspect HAL
status and the display buffer.

## Completion Checklist

- [ ] I2C1 runs at 100 kHz.
- [ ] Device-ready probe succeeds at `0x3C`.
- [ ] Initialization returns no HAL errors.
- [ ] OLED shows a fixed pattern.
- [ ] OLED later shows changing application data.
- [ ] VCD contains active I2C clock and data lines.

## Experiments

- Change the I2C speed to 400 kHz and compare VCD timing.
- Update only changed display pages instead of the full framebuffer.
- Deliberately use the wrong address and inspect the missing acknowledgment.

## Next Project

Continue with [Project 7: MPU6050 Sensor Acquisition](proj7_sensor.md).
