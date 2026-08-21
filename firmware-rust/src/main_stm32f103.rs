#![no_std]
#![no_main]

mod math;
use math::sum;

use cortex_m_rt::entry;
use panic_halt as _;
use stm32f1xx_hal::{pac, prelude::*};

#[entry]
fn main() -> ! {
    let cp = cortex_m::Peripherals::take().unwrap();
    let dp = pac::Peripherals::take().unwrap();

    let mut flash = dp.FLASH.constrain();
    let rcc = dp.RCC.constrain();
    let clocks = rcc.cfgr.freeze(&mut flash.acr);

    // Configure PC13 as a push-pull output for the on-board LED.
    let mut gpioc = dp.GPIOC.split();
    let mut led = gpioc.pc13.into_push_pull_output(&mut gpioc.crh);

    // Configure USART1 on PA9 (TX) / PA10 (RX) for serial output.
    let mut afio = dp.AFIO.constrain();
    let mut gpioa = dp.GPIOA.split();
    let tx = gpioa.pa9.into_alternate_push_pull(&mut gpioa.crh);
    let rx = gpioa.pa10;
    let serial = stm32f1xx_hal::serial::Serial::new(
        dp.USART1,
        (tx, rx),
        &mut afio.mapr,
        stm32f1xx_hal::serial::Config::default().baudrate(115200.bps()),
        &clocks,
    );
    let (mut tx, _rx) = serial.split();

    let mut delay = cortex_m::delay::Delay::new(cp.SYST, clocks.sysclk().raw());

    use core::fmt::Write;
    write!(tx, "Hello from STM32F103 Rust Firmware!\r\n").unwrap();
    let demo = sum(10, 32);
    write!(tx, "sum(10, 32) = {}\r\n", demo).unwrap();

    loop {
        led.set_high();
        write!(tx, "Blink STM32 loop executed. Pin PC13 state: 1\r\n").unwrap();
        delay.delay_ms(1000);

        led.set_low();
        write!(tx, "Blink STM32 loop executed. Pin PC13 state: 0\r\n").unwrap();
        delay.delay_ms(1000);
    }
}
