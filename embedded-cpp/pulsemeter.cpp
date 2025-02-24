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
    : sensorPin(sensor), ledPin(led), threshold(512), lastBeatTime(0), beatCount(0)
{
    // Initialize arrays for running average
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        samples[i] = 0;
    }
}

void PulseMeter::update()
{
    static unsigned long lastSampleTime = 0;
    static bool isPeak = false;
    static int sampleIndex = 0;
    static int lastThresholdUpdate = 0;
    static int lastRawValue = 0;
    static int avgValue = 512;
    unsigned long currentTime = millis();

    if (currentTime - lastSampleTime >= SAMPLE_PERIOD)
    {
        lastSampleTime = currentTime;

        // Read raw value
        int rawValue = analogRead(sensorPin);
        
        // Store raw value instead of difference
        samples[sampleIndex] = rawValue;
        sampleIndex = (sampleIndex + 1) % BUFFER_SIZE;

        // Update threshold less frequently (every 1000ms)
        if (currentTime - lastThresholdUpdate >= 1000) {
            long sum = 0;
            int max_value = 0;
            for (int i = 0; i < BUFFER_SIZE; i++) {
                sum += samples[i];
                max_value = max(max_value, samples[i]);
            }
            
            // ...existing threshold calculation code...
            avgValue = sum / BUFFER_SIZE;  // Update static avgValue
            threshold = avgValue + ((max_value - avgValue) * 0.6);
        }

        // Print debug values
        Serial.print("Max:1024 , Min:0, ");
        Serial.print("raw:");
        Serial.print(rawValue);
        Serial.print(",avg:");
        Serial.print(avgValue);
        Serial.print(",thr:");
        Serial.print(threshold);
        Serial.print(",pk:");
        Serial.println(isPeak ? "900":"100");

        // Detect peaks
        if (rawValue > threshold && !isPeak &&
            (currentTime - lastBeatTime) > MIN_BEAT_INTERVAL)
        {
            isPeak = true;
            beatCount++;
            lastBeatTime = currentTime;
        }
        else if (rawValue <= threshold && isPeak)
        {
            isPeak = false;
        }

        if (currentTime - lastBeatTime >= BPM_SAMPLE_PERIOD)
        {
            calculateAndPrintBPM();
            beatCount = 0;
            lastBeatTime = currentTime;
        }
    }
}

void PulseMeter::calculateAndPrintBPM()
{
    // Calculate BPM based on beat count over the sample period
    float beatsPerMinute = (float)beatCount * (60000.0f / BPM_SAMPLE_PERIOD);

    // Print BPM value
    Serial.print("BPM: ");
    Serial.println(beatsPerMinute);
}