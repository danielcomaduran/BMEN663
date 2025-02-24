#include "thermometer.h"
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    setupTemperatureSensor();
}

void loop()
{
    // Read and plot temperature value
    float temperatureC = readTemperature();
    plotTemperature(temperatureC);

    // Small delay for better readability in the Serial Plotter
    waitMillis(300);
}
