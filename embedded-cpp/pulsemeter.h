#ifndef PULSEMETER_H
#define PULSEMETER_H

#include <Arduino.h>

#define SAMPLE_PERIOD 20        // Sample every 20ms
#define BPM_SAMPLE_PERIOD 15000 // Calculate BPM every 15 seconds
#define BUFFER_SIZE 10          // Number of samples to average
#define THRESHOLD_OFFSET 10     // Offset above average for peak detection
#define MIN_BEAT_INTERVAL 500   // Minimum time between beats (ms)

// Add these constants to your header file
#define BUFFER_SIZE 20        // Increased from 10 for better averaging
#define DC_OFFSET 50         // New: DC offset to amplify small changes

class PulseMeter {
private:
    int sensorPin;
    int ledPin;
    int threshold;
    unsigned long lastBeatTime;
    int beatCount;
    int samples[BUFFER_SIZE];

    void calculateAndPrintBPM();

public:
    PulseMeter(int sensor, int led);
    void setup();
    void update();
};

#endif