# Notes

## To edit diagram
- Open it in another vscode, not in this container. Wokwi will stop you.

## compiling main.rs
- root@bc4dfb6a5199:/workspaces/demo_renode/firmware-rust# cargo build --release

### Result
   Compiling firmware-rust v0.1.0 (/workspaces/demo_renode/firmware-rust)
    Finished `release` profile [optimized] target(s) in 0.34s
warning: the following packages contain code that will be rejected by a future version of Rust: proc-macro-error2 v2.0.1
note: to see what the problems were, use the option `--future-incompat-report`, or run `cargo report future-incompatibilities --id 1`
root@bc4dfb6a5199:/workspaces/demo_renode/firmware-rust# cargo build --release
   Compiling firmware-rust v0.1.0 (/workspaces/demo_renode/firmware-rust)
    Finished `release` profile [optimized] target(s) in 0.37s
warning: the following packages contain code that will be rejected by a future version of Rust: proc-macro-error2 v2.0.1
note: to see what the problems were, use the option `--future-incompat-report`, or run `cargo report future-incompatibilities --id 1`

## compiling main.c
root@bc4dfb6a5199:/workspaces/demo_renode/firmware-c# pio run

### Result
Processing esp32-c3-devkitm-1 (platform: espressif32; board: esp32-c3-devkitm-1; framework: arduino)
-----------------------------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/esp32-c3-devkitm-1.html
PLATFORM: Espressif 32 (7.0.1) > Espressif ESP32-C3-DevKitM-1
HARDWARE: ESP32C3 160MHz, 320KB RAM, 4MB Flash
DEBUG: Current (cmsis-dap) External (cmsis-dap, esp-bridge, esp-builtin, esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
PACKAGES: 
 - framework-arduinoespressif32 @ 3.20017.241212+sha.dcc1105b 
 - tool-esptoolpy @ 2.41100.0 (4.11.0) 
 - toolchain-riscv32-esp @ 8.4.0+2021r2-patch5
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 33 compatible libraries
Scanning dependencies...
No dependencies
Building in release mode
Retrieving maximum program size .pio/build/esp32-c3-devkitm-1/firmware.elf
Checking size .pio/build/esp32-c3-devkitm-1/firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [          ]   4.3% (used 13988 bytes from 327680 bytes)
Flash: [==        ]  19.9% (used 260878 bytes from 1310720 bytes)
==================================== [SUCCESS] Took 1.08 seconds ====================================
