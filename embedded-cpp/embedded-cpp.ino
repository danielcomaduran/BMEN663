#include "potentiometer.h"

int analogPin = A0;     // Analog pin connected to the potentiometer
int ledPin = 13;        // Digital pin connected to the built-in LED
int threshold = 512;    // Threshold value for the potentiometer

Potentiometer pot(A0, 13, 512);

void setup() {
    pot.begin();
}

void loop() {
    pot.update();
    delay(100);
}
