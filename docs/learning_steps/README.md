# STM32 Blue Pill Learning Path

This folder is a project-based curriculum for the STM32F103C8 using
STM32Cube-generated HAL firmware in `blue_cube_proj` and Wokwi simulation.
Each project builds on the previous one and uses the same CubeIDE project and
ELF output.

## Working Project

- Cube project: `blue_cube_proj/bluepill_demo`
- Application: `blue_cube_proj/bluepill_demo/Core/Src/main.c`
- Build output: `blue_cube_proj/bluepill_demo/Debug/bluepill_demo.elf`
- Wokwi circuit: `sim/wokwi/stm32f103/diagram.json`
- Wokwi configuration: `sim/wokwi/stm32f103/wokwi.toml`
- Physical debugger: DAPLink v2 with pyOCD

## Curriculum

| Project | Topic | Main peripherals | Status |
| --- | --- | --- | --- |
| [1. Blinking LED](proj1_blinking_LED.md) | Baseline build, simulation, and debug | GPIO, USART | Complete baseline |
| [2. Button and debounce](proj2_button_debounce.md) | Reliable digital input | GPIO input | Next |
| [3. Timer interrupt](proj3_timer_interrupt.md) | Nonblocking periodic work | TIM2, NVIC | Planned |
| [4. PWM brightness](proj4_pwm_led.md) | Hardware-generated waveform | TIM3 PWM | Planned |
| [5. ADC and plotter](proj5_adc_plotter.md) | Analog acquisition | ADC1, USART | Planned |
| [6. OLED display](proj6_oled_i2c.md) | I2C device driver | I2C1, SSD1306 | Planned |
| [7. Sensor acquisition](proj7_sensor.md) | Structured sensor data | I2C1, MPU6050 | Planned |
| [8. Final dashboard](proj8_dashboard.md) | Integrated application | GPIO, ADC, I2C, timers, USART | Planned |

Read [Development Workflow](workflow.md) before starting each project.

## Learning Rules

1. Predict behavior before running the code.
2. Add one peripheral or behavior at a time.
3. Build immediately after each meaningful change.
4. Use UART logs for state, VCD traces for timing, and GDB for control flow.
5. Verify in Wokwi before flashing hardware.
6. Keep SWD enabled in CubeMX.
7. Record failures and explanations, not only the final solution.

## Source-Control Checkpoints

Create a commit or tag after each completed project. Suggested tags:

```text
learn/proj1-blink
learn/proj2-button
learn/proj3-timer
learn/proj4-pwm
learn/proj5-adc
learn/proj6-oled
learn/proj7-sensor
learn/proj8-dashboard
```

Do not start the next project until every item in the current completion
checklist passes.
