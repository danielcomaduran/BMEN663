#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <Arduino.h>
#include <math.h>

// Analog pin connected to the thermistor
#define TEMP_PIN A0

// Plot limits in Celsius
#define LOWER_TEMP 0
#define UPPER_TEMP 30

// Constants for thermistor calculations
#define TEMP_SAMPLES 10 // Number of samples for averaging
#define K_TO_C 273.15   // Kelvin to Celsius conversion

// - Steinhart-Hart coefficients
#define SH_A 0.001129148
#define SH_B 0.000234125
#define SH_C 0.0000000876741

/**
 * @brief Initializes the temperature sensor pin as input
 */
void setupTemperatureSensor();

/**
 * @brief Reads the temperature sensor and returns the temperature in Celsius.
 *
 * @return The temperature in Celsius.
 */
float readTemperature();

/**
 * @brief Prints the temperature to the Serial Plotter.
 *
 * @param temperature The temperature in Celsius.
 */
void plotTemperature(float temperature);

/**
 * @brief Waits the specified interval in msec.
 * @param interval The time to wait in msec.
 */
void waitMillis(unsigned long interval);

#endif // THERMOMETER_H
