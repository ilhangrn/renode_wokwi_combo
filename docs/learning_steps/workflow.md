# Development Workflow

Use this loop for every learning project.

## 1. Define the Behavior

Write down:

- Inputs
- Outputs
- Update rate
- Expected UART messages
- Signals to capture with the logic analyzer
- One failure condition to test

## 2. Save a Checkpoint

Start from a working project. Commit or copy important generated configuration
before changing CubeMX settings. Do not mix two new peripherals in one step.

## 3. Configure STM32CubeMX

1. Open `bluepill_demo.ioc`.
2. Enable only the peripheral required by the lesson.
3. Assign pins and check for conflicts.
4. Keep **System Core > SYS > Debug** set to **Serial Wire**.
5. Confirm clock assumptions. This project currently uses the reset-default
   8 MHz HSI clock.
6. Generate code.

Place application code inside `USER CODE BEGIN/END` sections so regeneration
does not erase it.

## 4. Update the Wokwi Circuit

1. Add the matching virtual component.
2. Use the same pin names selected in CubeMX.
3. Give every wire an explicit orthogonal route.
4. Connect relevant digital signals to logic-analyzer channels.
5. Keep UART TX/RX connected to the serial monitor.

## 5. Build

```sh
make -C blue_cube_proj/bluepill_demo/Debug all
```

Fix compiler errors before opening Wokwi. Wokwi loads the existing ELF; it does
not build source code.

## 6. Simulate

1. Start Wokwi using `sim/wokwi/stm32f103/wokwi.toml`.
2. Exercise every input.
3. Compare behavior with the written prediction.
4. Read UART logs.
5. Stop simulation to finalize `wokwi-stm32-signals.vcd`.

## 7. Inspect Signals

Open the VCD file in Surfer, PulseView, or GTKWave. Check:

- Edge timing
- Period and frequency
- Pulse width or PWM duty cycle
- UART activity
- I2C clock and data activity

The Wokwi analyzer itself shows activity and sample count. Waveforms are viewed
from the VCD file.

## 8. Debug

Use breakpoints sparingly. Inspect:

- Peripheral handle initialization
- State variables
- Interrupt callbacks
- Error-handler entry

Avoid breakpoints inside timing-critical interrupts unless the lesson requires
it; stopping the CPU changes timing.

## 9. Test Hardware

1. Connect DAPLink SWDIO, SWCLK, GND, VTref, and nRESET.
2. Build the same ELF used by Wokwi.
3. Launch **Debug Blue Pill (DAPLink / pyOCD)**.
4. Compare physical behavior with simulation.

## 10. Record Results

For each project, record:

```text
Prediction:
Observed in Wokwi:
Observed on hardware:
Difference:
Root cause:
What I learned:
```

## Definition of Done

A project is complete only when:

- Build succeeds.
- Expected Wokwi behavior is visible.
- UART output is understandable and bounded.
- Relevant VCD signals match expected timing.
- Hardware behavior is checked when components are available.
- The lesson checklist is complete.
