#include "potentiometer.h"
#include <Arduino.h>

void setupPins() 
{
    // Configure the LED pin as an output
    pinMode(LED_PIN, OUTPUT);
}

int readPotentiometer() 
{
    // Read the potentiometer value
    return analogRead(POT_PIN);
}

void checkThresholdAndControlLED(int potValue, int threshold)
{
    // Check if the potentiometer value exceeds the threshold
    if (potValue > threshold) {
        // Turn on the LED
        digitalWrite(LED_PIN, HIGH);
    } else {
        // Turn off the LED
        digitalWrite(LED_PIN, LOW);
    }
}

void waitMillis(unsigned long interval) {
  // Start timers
  unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Wait for the time to pass
  while (currentMillis - previousMillis < interval) {
    currentMillis = millis();
  }
  previousMillis = currentMillis;
}
