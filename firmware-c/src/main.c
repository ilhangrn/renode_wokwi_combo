#include <Arduino.h>

// Most ESP32 dev boards have a built-in LED on GPIO 2
#define BLINK_LED 2

void setup()
{
    // Set the pin as an output
    pinMode(BLINK_LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("ESP32 C Booted Successfully!");
}

void loop()
{
    // Turn the LED on
    digitalWrite(BLINK_LED, HIGH);
    Serial.println("LED ON");
    delay(1000);

    // Turn the LED off
    digitalWrite(BLINK_LED, LOW);
    Serial.println("LED OFF");
    delay(1000);
}
