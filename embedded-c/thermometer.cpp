#include "thermometer.h"
#include <Arduino.h>

void setupTemperatureSensor()
{
    pinMode(TEMP_PIN, INPUT);
}

float readTemperature()
{
    float sumTemp = 0;

    // Take multiple samples and average them
    for (int i = 0; i < TEMP_SAMPLES; i++)
    {
        int sensorValue = analogRead(TEMP_PIN);

        // Calculate resistance ratio
        float thermistorRatio = 1024.0 / sensorValue - 1;

        // Apply Steinhart-Hart equation
        float logThermistorResistance = log(10000.0 * thermistorRatio);
        float tempK = 1.0 / (SH_A + (SH_B + SH_C * logThermistorResistance * logThermistorResistance) * logThermistorResistance);

        // Convert to Celsius
        float tempC = tempK - K_TO_C;

        sumTemp += tempC;
        waitMillis(10);
    }

    return sumTemp / TEMP_SAMPLES;
}

void plotTemperature(float temperature)
{
    // Add variables for plot limits
    Serial.print("Y:" + String(UPPER_TEMP) + ", ");
    Serial.print("-Y:" + String(LOWER_TEMP) + ", ");

    // Print the temperature value
    Serial.print("Temperature_[C]:");
    Serial.println(temperature);
}

void waitMillis(unsigned long interval)
{
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    // Wait until the specified interval has elapsed
    while (currentMillis - previousMillis < interval)
    {
        currentMillis = millis();
    }
}