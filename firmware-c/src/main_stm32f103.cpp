#include <Arduino.h>
#include "math/sum.h"

#define LED_PIN PC13

void setup()
{
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    Serial.println("Hello from STM32F103 C Firmware!");

    int demo = sum(10, 32);
    Serial.print("sum(10, 32) = ");
    Serial.println(demo);
}

void loop()
{
    digitalWrite(LED_PIN, HIGH);
    Serial.print("Blink STM32 loop executed. Pin ");
    Serial.print(LED_PIN);
    Serial.print(" state: ");
    Serial.println(digitalRead(LED_PIN));
    delay(1000);

    digitalWrite(LED_PIN, LOW);
    Serial.print("Blink STM32 loop executed. Pin ");
    Serial.print(LED_PIN);
    Serial.print(" state: ");
    Serial.println(digitalRead(LED_PIN));
    delay(1000);
}
