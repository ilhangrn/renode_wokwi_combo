#![no_std]
#![no_main]

use esp_backtrace as _;
use esp_hal::{
    delay::Delay,
    gpio::{Io, Level, Output},
    prelude::*,
};
use esp_println::println;

#[entry]
fn main() -> ! {
    // Initialize peripheral clocks and control structures
    let peripherals = esp_hal::init(esp_hal::Config::default());
    
    // Initialize the IO system and configure GPIO 2 as a digital output
    let io = Io::new(peripherals.GPIO, peripherals.IO_MUX);
    let mut led = Output::new(io.pins.gpio2, Level::Low);

    // Get a delay driver instance
    let delay = Delay::new();

    println!("ESP32 Rust Booted Successfully!");

    loop {
        led.toggle();
        if led.is_set_high() {
            println!("LED ON");
        } else {
            println!("LED OFF");
        }
        delay.delay_millis(1000);
    }
}
