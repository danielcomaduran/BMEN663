#include "pulsemeter.h"

// Create pulse sensor object
const int SENSOR_PIN = A1;
const int LED_PIN = 2;
PulseMeter pulseMeter(SENSOR_PIN, LED_PIN);

void setup()
{
    Serial.begin(9600);
    pulseMeter.setup();
}

void loop()
{
    pulseMeter.update();
}
