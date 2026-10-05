# Project 3: Timer Interrupt and Nonblocking Scheduling

## Goal

Replace `HAL_Delay()` blinking with a TIM2 periodic interrupt. Keep UART
formatting and transmission in the main loop rather than inside the interrupt.

## Concepts

- Hardware timers
- Prescaler and auto-reload values
- NVIC interrupts
- `volatile` shared state
- Interrupt service routine design
- Deferred work in the main loop

## Timer Calculation

With an 8 MHz timer clock, choose:

- Prescaler: 7999
- Auto-reload: 99

The update frequency is:

$$
f = \frac{8,000,000}{(7999 + 1)(99 + 1)} = 10\text{ Hz}
$$

Ten timer events therefore equal one second.

## CubeMX Steps

1. Enable TIM2 with its internal clock.
2. Set prescaler to 7999.
3. Set counter period to 99.
4. Enable the TIM2 global interrupt in NVIC.
5. Regenerate code.

## Firmware Steps

Create shared state:

```c
volatile uint32_t timer_ticks = 0;
volatile bool one_second_due = false;
```

In `HAL_TIM_PeriodElapsedCallback()`:

1. Check that `htim->Instance == TIM2`.
2. Increment `timer_ticks`.
3. Every ten ticks, set `one_second_due = true`.
4. Do not call `snprintf()`, blocking UART, or `HAL_Delay()` in the callback.

Start the timer after peripheral initialization:

```c
HAL_TIM_Base_Start_IT(&htim2);
```

In the main loop, consume and clear `one_second_due`, then toggle the LED and
print the message.

## Wokwi Verification

1. Capture PC13 as `LED`.
2. Run for at least five seconds.
3. Stop simulation and open the VCD file.
4. Measure time between LED edges.
5. Confirm the main loop can still process button input from Project 2.

## Debug Exercise

Set a breakpoint in the main-loop event handler, not the interrupt. Add
`timer_ticks` and `one_second_due` to Watch.

## Completion Checklist

- [ ] TIM2 interrupt runs at 10 Hz.
- [ ] LED toggles once per second.
- [ ] No `HAL_Delay()` remains in the main loop.
- [ ] Interrupt callback performs bounded, nonblocking work.
- [ ] Button input remains responsive.
- [ ] VCD timing matches the calculation.

## Experiments

- Produce 2 Hz and 5 Hz LED rates by changing only software division.
- Change timer period and verify the frequency mathematically and in VCD.
- Count missed events if the main loop is deliberately slowed.

## Next Project

Continue with [Project 4: PWM LED Brightness](proj4_pwm_led.md).
