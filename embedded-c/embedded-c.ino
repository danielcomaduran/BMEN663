#include "potentiometer.h"
#include <Arduino.h>

int threshold = 512; // ADC threshold value for potentiometer

void setup() 
{
    Serial.begin(9600);
    setupPins();
}

void loop() 
{
    // Read and print potentiometer value
    int potValue = readPotentiometer();
    Serial.println(potValue);

    // Turn on LED if potentiometer value passes threshold
    checkThresholdAndControlLED(potValue, threshold);

    // Small delay for better readability in the Serial Plotter
    waitMillis(100);
}
