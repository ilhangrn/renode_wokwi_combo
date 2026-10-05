# Project 8: Integrated Sensor Dashboard

## Goal

Combine the previous lessons into a responsive application with a button,
potentiometer, PWM LED, MPU6050, OLED, UART logs, timer-driven scheduling, and
fault reporting.

## Application Behavior

- Read the button with debounce.
- Sample the potentiometer at 10 Hz.
- Read the MPU6050 at 20 Hz.
- Update PWM brightness from the potentiometer.
- Refresh the OLED at 5 Hz.
- Print a compact status line at 1 Hz.
- Use the button to switch OLED pages.
- Blink PC13 with a distinct pattern when a peripheral fails.

## Concepts

- Cooperative scheduling
- State machines
- Peripheral ownership
- Data freshness
- Error propagation and recovery
- Integration testing

## Suggested Architecture

Use a small application state structure:

```c
typedef struct
{
  uint32_t adc_raw;
  int16_t accel_x;
  int16_t accel_y;
  int16_t accel_z;
  uint8_t display_page;
  bool sensor_ok;
  bool display_ok;
} AppState;
```

Use TIM2 or `HAL_GetTick()` to create due flags for each rate. Peripheral drivers
update state; presentation code reads state. Avoid global formatting buffers in
interrupts.

## Implementation Steps

1. Start from the completed Project 7 checkpoint.
2. List every pin and verify no CubeMX conflict.
3. Create independent task functions:
   - `button_task()`
   - `adc_task()`
   - `sensor_task()`
   - `display_task()`
   - `uart_task()`
4. Give each task a fixed update period.
5. Ensure interrupt callbacks only set counters or flags.
6. Add explicit timeout and status handling to ADC, I2C, and UART operations.
7. Define degraded behavior when the sensor or display is absent.
8. Add one UART startup summary listing clocks, addresses, and update rates.

## Wokwi Test Matrix

| Test | Expected result |
| --- | --- |
| Move potentiometer | PWM and ADC value follow smoothly |
| Press button once | Display page advances once |
| Change MPU6050 controls | Sensor values update within 100 ms |
| Run for one minute | No lockup or unbounded logging |
| Wrong sensor address | Error status appears; other tasks continue |
| Stop simulation | VCD contains LED, PWM, UART, and I2C activity |

## Timing Review

Use the VCD capture to answer:

- Is PWM frequency stable while I2C transfers occur?
- How often are OLED transfers sent?
- Does UART traffic overlap sensor reads safely?
- Does button handling remain responsive during display updates?

## Hardware Verification

Test incrementally:

1. Blue Pill and DAPLink only.
2. Add button and LEDs.
3. Add potentiometer.
4. Add OLED and run an I2C address scan.
5. Add MPU6050.
6. Compare physical and Wokwi logs.

Check voltage levels and use a common ground before powering external modules.

## Completion Checklist

- [ ] No long blocking delays in normal operation.
- [ ] Each task runs at its intended rate.
- [ ] Button input is debounced.
- [ ] ADC controls PWM predictably.
- [ ] OLED and MPU6050 share I2C correctly.
- [ ] UART output remains readable and rate-limited.
- [ ] Peripheral failures are visible and nonfatal where possible.
- [ ] VCD traces support the timing claims.
- [ ] Physical hardware matches core simulated behavior.
- [ ] Final observations are recorded in project notes.

## Further Projects

After this dashboard, choose a direction:

- SPI microSD data logger
- FreeRTOS tasks and queues
- Low-power sleep and wake-up
- UART command shell
- Bootloader and firmware update flow
- Host-side tests for protocol and filtering code
- Renode automated regression tests
