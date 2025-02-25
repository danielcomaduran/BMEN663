#ifndef PULSEMETER_H
#define PULSEMETER_H

#include <Arduino.h>

// Time constants
#define SAMPLE_PERIOD 20        // Sample period [msec]
#define MIN_BEAT_INTERVAL 500   // Minimum time between beats [sec]

// Signal processing constants
#define BUFFER_SIZE 20         // Number of samples for moving average
#define THRESHOLD_OFFSET 10    // Offset above average for peak detection
#define DC_OFFSET 50          // DC offset to amplify small changes

class PulseMeter {
private:
    int sensorPin;                    // Analog pin connected to the pulse sensor
    int ledPin;                       // Digital pin connected to the indicator LED
    int threshold = 512;              // Threshold value for peak detection
    unsigned long lastBeatTime = 0;   // Time of the last heartbeat
    int beatCount = 0;                // Number of beats detected
    int samples[BUFFER_SIZE];         // Array to store raw sensor values

    /**
     * @brief Prints the average value, threshold, and peak status.
     * 
     * This method is used for debugging purposes to print the current
     * average value, threshold, and peak status to the Serial Monitor.
     * 
     * @param avgValue The current average value
     * @param threshold The current threshold value
     * @param isPeak True if a peak is detected, false otherwise
     */
    void printValues(int avgValue, int threshold, bool isPeak);

public:
    /**
     * @brief Constructs a new Pulse Meter object.
     * 
     * @param sensor The analog pin connected to the pulse sensor
     * @param led The digital pin connected to the indicator LED
     */
    PulseMeter(int sensor, int led);

    /**
     * @brief Initializes the pulse sensor and LED pins.
     * 
     * This method should be called in the setup() function of the main program.
     * It configures the sensor pin as input and the LED pin as output.
     */
    void setup();

    /**
     * @brief Updates the pulse measurements and detects beats.
     * 
     * This method should be called in the main loop. It reads the sensor,
     * processes the signal using a moving average filter, detects beats,
     * and updates the BPM calculation when appropriate.
     */
    void update();
};

#endif