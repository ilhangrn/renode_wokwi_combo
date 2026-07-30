#![no_std]
#![no_main]

use esp_backtrace as _;
use esp_hal::{
    delay::Delay,
    gpio::{Io, Level, Output},
};
use esp_println::println;

#[esp_hal::entry]
fn main() -> ! {
    let peripherals = esp_hal::init(esp_hal::Config::default());
    let io = Io::new(peripherals.GPIO, peripherals.IO_MUX);
    let mut led = Output::new(io.pins.gpio8, Level::Low);
    let delay = Delay::new();

    println!("Hello from ESP32-C3 Rust Firmware!");

    loop {
        led.toggle();
        println!("Blink Rust loop executed.");
        delay.delay_millis(1000);
    }
}
