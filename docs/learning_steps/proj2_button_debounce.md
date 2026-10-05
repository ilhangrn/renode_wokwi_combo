# Project 2: Button Input and Debouncing

## Goal

Use a pushbutton on PA0 to toggle the PC13 LED exactly once per press. Reject
mechanical bounce without using a long blocking delay.

## Concepts

- GPIO input and internal pull-up
- Active-low signals
- Edge detection
- Debouncing with `HAL_GetTick()`
- Separating raw input from application state

## Wokwi Parts

- Existing Blue Pill and LED
- Pushbutton
- Logic analyzer channels for `BUTTON` and `LED`

Connect one button terminal to PA0 and the other to GND. Configure PA0 with an
internal pull-up, so released reads high and pressed reads low.

## CubeMX Steps

1. Set PA0 to `GPIO_Input`.
2. Select `Pull-up`.
3. Keep PC13 as `GPIO_Output`.
4. Regenerate code.
5. Confirm Serial Wire debug remains enabled.

## Firmware Steps

Maintain four pieces of state:

```c
GPIO_PinState raw_state;
GPIO_PinState stable_state = GPIO_PIN_SET;
GPIO_PinState previous_raw = GPIO_PIN_SET;
uint32_t last_change_ms = 0;
```

In the main loop:

1. Read PA0.
2. When raw state changes, store `HAL_GetTick()`.
3. Accept the new state only after it remains unchanged for 30 ms.
4. Toggle the LED only when stable state changes from released to pressed.
5. Print one UART message per accepted press.

Do not use `HAL_Delay(30)` for debounce. The CPU should remain available for
other work.

## Wokwi Verification

1. Add the button to `diagram.json` with explicit wire routes.
2. Add PA0 to an unused analyzer channel and name it `BUTTON`.
3. Start simulation and click the button repeatedly.
4. Confirm one LED toggle and one log message per press.
5. Inspect `BUTTON` and `LED` in the VCD file.

## Debug Exercise

Set a breakpoint only where a press becomes stable. Inspect raw state, stable
state, and elapsed debounce time.

## Completion Checklist

- [ ] Released input reads high.
- [ ] Pressed input reads low.
- [ ] One press causes one LED toggle.
- [ ] Holding the button does not repeatedly toggle the LED.
- [ ] Main loop remains nonblocking.
- [ ] UART reports accepted presses only.

## Experiments

- Compare debounce intervals of 5, 30, and 100 ms.
- Change the pin to pull-down and reverse the button wiring and logic.
- Count accepted presses and print the count.

## Next Project

Continue with [Project 3: Timer Interrupt](proj3_timer_interrupt.md).
