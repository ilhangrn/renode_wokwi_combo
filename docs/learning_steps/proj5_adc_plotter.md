# Project 5: ADC and Serial Plotter

## Goal

Read a potentiometer with ADC1 channel 1 on PA1. Print samples for Wokwi's
Serial Plotter and map the reading to PWM LED brightness.

## Concepts

- Analog-to-digital conversion
- ADC resolution and reference voltage
- Sampling rate
- Integer scaling
- Analog visualization through sampled data

## Hardware and Wokwi Changes

Add a potentiometer:

- VCC to 3.3 V
- GND to GND
- Signal/wiper to PA1

A logic analyzer cannot display analog voltage. Use the Serial Plotter to graph
ADC samples. Keep digital PWM capture on the analyzer.

## CubeMX Steps

1. Enable ADC1 input channel 1 on PA1.
2. Use 12-bit resolution and software triggering.
3. Select a moderate sample time.
4. Disable continuous mode for explicit scheduled samples.
5. Regenerate code.

## Firmware Steps

Calibrate once after ADC initialization:

```c
HAL_ADCEx_Calibration_Start(&hadc1);
```

Every 100 ms:

1. Start ADC conversion.
2. Poll with a finite timeout.
3. Read the 12-bit value.
4. Stop conversion.
5. Convert to millivolts.
6. Update PWM duty.
7. Print one numeric sample line.

Conversions:

$$
V_{mV} = \frac{ADC \times 3300}{4095}
$$

$$
PWM = \frac{ADC \times 999}{4095}
$$

Use 32-bit intermediate values to avoid overflow and truncation errors.

For a single plot, print only the ADC value:

```c
snprintf(message, sizeof(message), "%lu\r\n", adc_value);
```

Set `serialMonitor.display` to `plotter` while graphing. Return it to `terminal`
when reading normal logs.

## Wokwi Verification

1. Start simulation in plotter mode.
2. Move the potentiometer slowly from minimum to maximum.
3. Confirm values span approximately 0 to 4095.
4. Confirm PWM brightness follows the reading.
5. Check that samples arrive at 10 Hz.

Wokwi currently provides basic ADC1 conversion for the Blue Pill; ADC2 is not
implemented.

## Debug Exercise

Watch the raw ADC value, millivolts, and PWM compare value. Test near 0, 2048,
and 4095.

## Completion Checklist

- [ ] ADC calibration succeeds.
- [ ] Minimum and maximum readings cover most of the 12-bit range.
- [ ] Plotter shows a stable 10 Hz signal.
- [ ] PWM mapping uses 32-bit arithmetic.
- [ ] Every poll operation has a finite timeout.
- [ ] Analog behavior is verified on physical hardware when available.

## Experiments

- Add a moving average over 8 or 16 samples.
- Compare raw and filtered readings.
- Add high and low thresholds with hysteresis.

## Next Project

Continue with [Project 6: SSD1306 OLED over I2C](proj6_oled_i2c.md).
