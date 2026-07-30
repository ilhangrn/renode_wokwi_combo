#![no_std]
#![no_main]

use esp_backtrace as _;
use esp_hal::{
    delay::Delay,
    gpio::{Level, Output},
};
use esp_println::println;

#[esp_hal::main]
fn main() -> ! {
    // 1. New simplified initialization
    let peripherals = esp_hal::init(esp_hal::Config::default());
    
    // 2. Access the pin directly from `peripherals` instead of `Io::new`
    let mut led = Output::new(peripherals.GPIO8, Level::Low);
    
    // 3. Delay no longer requires passing frozen clocks
    let delay = Delay::new();

    println!("Hello from ESP32-C3 Rust Firmware! \r\n");

    loop {
        led.toggle();
        // delay.delay_millis(500);
        let reading = led.is_set_high();
        println!("Blink Rust loop executed. Pin 8 state: {}\r\n", reading);
        delay.delay_millis(1000);
    }
}