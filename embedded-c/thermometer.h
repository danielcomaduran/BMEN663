#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <Arduino.h>
#include <math.h>

// Analog pin connected to the thermistor
#define TEMP_PIN A0

// Constants for thermistor calculations
#define TEMP_SAMPLES 10        // Number of samples for averaging
#define REFERENCE_RESISTOR 10000.0  // 10k reference resistor
#define THERMISTOR_B 3950.0    // B value of the thermistor
#define THERMISTOR_T0 298.15   // 25°C in Kelvin
#define THERMISTOR_R0 10000.0  // Resistance at 25°C

/**
 * @brief Initializes the serial communication.
 *
 * This function should be called in the setup() function of the main program.
 * It initializes the serial communication at 9600 baud rate.
 */
void setupTemperature();

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
