#include "pulsemeter.h"
#include <Arduino.h>

void PulseMeter::setup()
{
    pinMode(sensorPin, INPUT);

    // Turn on LED and keep it on
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
}

PulseMeter::PulseMeter(int sensor, int led)
{
    sensorPin = sensor;
    ledPin = led;
    threshold = threshold;

    // Initialize arrays for running average
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        samples[i] = 0;
    }
}

void PulseMeter::update()
{
    static unsigned long lastSampleTime = 0;
    static unsigned long lastThresholdUpdate = 0;
    unsigned long currentTime = millis();

    static bool isPeak = false;
    static int sampleIndex = 0;
    static int lastRawValue = 0;
    static int avgValue = 512;

    if (currentTime - lastSampleTime >= SAMPLE_PERIOD)
    {
        lastSampleTime = currentTime;

        // Read raw value
        int rawValue = analogRead(sensorPin);
        
        // Store raw value in buffer
        samples[sampleIndex] = rawValue;
        sampleIndex = (sampleIndex + 1) % BUFFER_SIZE;

        // Update threshold less frequently (every 1000ms)
        if (currentTime - lastThresholdUpdate >= 1000) {
            lastThresholdUpdate = currentTime;
            long sum = 0;
            int max_value = 0;
            for (int i = 0; i < BUFFER_SIZE; i++) {
                sum += samples[i];
                max_value = max(max_value, samples[i]);
            }

            avgValue = sum / BUFFER_SIZE;  // Update static avgValue
            threshold = avgValue + ((max_value - avgValue) * 0.6);
        }

        // Print debug values
        printValues(avgValue, threshold, isPeak);

        // Check for a new heartbeat
        bool validInterval = (currentTime - lastBeatTime) > MIN_BEAT_INTERVAL;
        if (rawValue > threshold && !isPeak && validInterval)
        {
            isPeak = true;
            lastBeatTime = currentTime;
        }
        else if (rawValue <= threshold && isPeak)
        {
            isPeak = false;
        }
    }
}

void PulseMeter::printValues(int avgValue, int threshold, bool isPeak)
{
    Serial.print("Max:1024, Min:0, ");
    Serial.print(", Avg:");
    Serial.print(avgValue);
    Serial.print(", Threshold:");
    Serial.print(threshold);
    Serial.print(", Peak:");
    Serial.println(isPeak ? "900" : "100");
}