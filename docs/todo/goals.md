# Goals
Here are our goals for this project

## Goal1
Have a dev env in which we can build C code and Rust code for given boards.

## Goal2
We should be able to simulate C and Rust solutions in Wokwi for supported boards

- ESP32C3 (Seeed studio xiao sense)
- Bluepill (STM32)

## Goal3
We should be able to simulate C and Rust solutions in Renode for supported boards

- Bluepill (STM32)

### Note:
Seems like renode has repl file ready for esp32 solutions which has multi cores. We will not try this board with Renode yet.

## Goal4
When we verify we can simulate all solution for our selected boards we will start using or developing debugging tools like visualizer, port listener, logger etc.