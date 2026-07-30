#include <Arduino.h>

#define LED_PIN 8

void setup()
{
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Hello from ESP32-C3 C Firmware!");
}

void loop()
{
    digitalWrite(LED_PIN, HIGH);
    Serial.printf("Blink C loop executed. Pin %d state: %d\r\n", LED_PIN, digitalRead(LED_PIN));
    delay(1000);

    digitalWrite(LED_PIN, LOW);
    Serial.printf("Blink C loop executed. Pin %d state: %d\r\n", LED_PIN, digitalRead(LED_PIN));
    delay(1000);
}