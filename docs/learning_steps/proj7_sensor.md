# Project 7: MPU6050 Sensor Acquisition

## Goal

Add an MPU6050 to the existing I2C bus, read acceleration and rotation data,
print it through UART, and show selected values on the OLED.

## Concepts

- Multiple devices on one I2C bus
- Register-based device protocols
- Burst reads
- Big-endian signed data
- Raw-to-engineering-unit conversion
- Sensor update rates

## Wokwi Wiring

Add an MPU6050 with:

- VCC to 3.3 V
- GND to GND
- SCL to PB6
- SDA to PB7
- AD0 low for address `0x68`

The OLED at `0x3C` and MPU6050 at `0x68` share SCL and SDA because their
addresses differ.

## Bring-Up Sequence

1. Probe addresses `0x3C` and `0x68` with `HAL_I2C_IsDeviceReady()`.
2. Read register `WHO_AM_I` at `0x75`.
3. Confirm the value is `0x68`.
4. Write `0x00` to `PWR_MGMT_1` at `0x6B` to wake the sensor.
5. Read 14 bytes beginning at `ACCEL_XOUT_H` (`0x3B`).

## Data Conversion

Combine each big-endian signed pair:

```c
int16_t value = (int16_t)((buffer[0] << 8) | buffer[1]);
```

At default ranges:

$$
a_g = \frac{a_{raw}}{16384}
$$

$$
\omega_{deg/s} = \frac{g_{raw}}{131}
$$

Keep raw values as integers initially. Add floating-point formatting only after
transactions and signs are correct.

## Firmware Structure

Create a small sensor module with:

- `mpu6050_init()`
- `mpu6050_read_raw()`
- A struct containing acceleration, temperature, and gyro fields
- Explicit status returns

Schedule sensor reads at 10 or 20 Hz. Do not read continuously in a tight loop.
Update the OLED more slowly if full framebuffer transfers consume too much time.

## Wokwi Verification

1. Confirm both I2C addresses acknowledge.
2. Change simulated MPU6050 motion controls.
3. Confirm raw values change with the expected sign and axis.
4. Inspect shared-bus traffic in the VCD file.
5. Confirm sensor reads and OLED writes use different addresses.

## Debug Exercise

Inspect the 14-byte receive buffer before conversion. Manually calculate one
signed axis and compare it with the program result.

## Completion Checklist

- [ ] `WHO_AM_I` returns `0x68`.
- [ ] Sensor wakes successfully.
- [ ] Burst read returns 14 bytes.
- [ ] Signed values and byte order are correct.
- [ ] UART output updates at a bounded rate.
- [ ] OLED and sensor coexist on I2C1.
- [ ] Errors do not trap the application silently.

## Experiments

- Add a low-pass filter to acceleration.
- Detect orientation from the dominant acceleration axis.
- Measure I2C bus utilization from VCD timestamps.

## Next Project

Continue with [Project 8: Integrated Dashboard](proj8_dashboard.md).
