#include "potentiometer.h"

Potentiometer::Potentiometer(int potPin, int ledPin, int threshold)
    : potPin(potPin), ledPin(ledPin), threshold(threshold), potValue(0), 
      generateSquareWave(false), lastToggleTime(0), squareWaveValue(0) {}

void Potentiometer::begin() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void Potentiometer::update() {
    readPotentiometer();
    checkThresholdAndControlLED();
    if (generateSquareWave) {
        generateSquareWaveSignal();
    }
}

void Potentiometer::readPotentiometer() {
    potValue = analogRead(potPin);
    Serial.print(potValue);
    Serial.print(" ");
    Serial.println(squareWaveValue);
}

void Potentiometer::checkThresholdAndControlLED() {
    if (potValue > threshold) {
        digitalWrite(ledPin, HIGH);
        generateSquareWave = true;
    } else {
        digitalWrite(ledPin, LOW);
        generateSquareWave = false;
        squareWaveValue = 0;
    }
}

void Potentiometer::generateSquareWaveSignal() {
    unsigned long currentTime = millis();
    if (currentTime - lastToggleTime >= 500) { // Adjust the frequency as needed
        squareWaveValue = !squareWaveValue;
        lastToggleTime = currentTime;
    }
}
