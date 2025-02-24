#include "thermometer.h"
#include <Arduino.h>

void setup() 
{
    Serial.begin(9600);
    setupTemperature();
}

void loop() 
{
    // Read and plot temperature value
    float temperature = readTemperature();
    plotTemperature(temperature);

    // Small delay for better readability in the Serial Plotter
    waitMillis(100);
}
