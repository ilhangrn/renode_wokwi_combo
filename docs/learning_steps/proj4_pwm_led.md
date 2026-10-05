# Project 4: PWM LED Brightness

## Goal

Drive an external LED from TIM3 channel 1 on PA6. Fade brightness using hardware
PWM while the CPU continues handling button, timer, and UART work.

## Concepts

- Timer output compare and PWM
- Frequency and duty cycle
- GPIO alternate functions
- Updating a capture/compare register
- Measuring pulse width in VCD

## Hardware and Wokwi Changes

Add a second LED for PWM:

- PA6 to a 220 ohm resistor
- Resistor to LED anode
- LED cathode to GND

Keep PC13 as the one-second status LED. Connect PA6 to an analyzer channel named
`PWM_LED`.

## PWM Calculation

For an 8 MHz TIM3 clock, use:

- Prescaler: 7
- Auto-reload/period: 999

$$
f_{PWM} = \frac{8,000,000}{(7 + 1)(999 + 1)} = 1000\text{ Hz}
$$

The compare value controls duty cycle from 0 to 999.

## CubeMX Steps

1. Enable TIM3 channel 1 as `PWM Generation CH1`.
2. Confirm PA6 is assigned to TIM3_CH1.
3. Set prescaler to 7 and counter period to 999.
4. Set initial pulse to 0.
5. Regenerate code.

## Firmware Steps

Start PWM after initialization:

```c
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
```

Maintain a duty value and direction. Update brightness from the main-loop
scheduler every 5 to 10 ms:

```c
__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty);
```

Do not toggle PA6 manually after assigning it to the timer alternate function.

## Wokwi Verification

1. Confirm the PWM LED fades smoothly.
2. Capture PA6 with the logic analyzer.
3. Measure a period of approximately 1 ms.
4. Pause at low, medium, and high brightness and compare pulse width.
5. Confirm PC13 and button behavior continue independently.

## Debug Exercise

Watch `duty` and the TIM3 capture/compare register. Confirm 25%, 50%, and 75%
duty values are approximately 250, 500, and 750.

## Completion Checklist

- [ ] PA6 is configured as TIM3_CH1.
- [ ] PWM frequency is approximately 1 kHz.
- [ ] Duty cycle ramps without blocking delays.
- [ ] VCD pulse widths match register values.
- [ ] Existing button and one-second tasks remain responsive.
- [ ] Physical LED uses a current-limiting resistor.

## Experiments

- Compare 100 Hz, 1 kHz, and 10 kHz PWM.
- Apply a nonlinear brightness table and compare perceived smoothness.
- Use the button to pause or reverse the fade.

## Next Project

Continue with [Project 5: ADC and Serial Plotter](proj5_adc_plotter.md).
