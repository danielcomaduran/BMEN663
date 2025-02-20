#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

// Analog pin connected to the potentiometer
#define POT_PIN A0

// Digital pin connected to the built-in LED
#define LED_PIN 13

/**
 * @brief Initializes the serial communication and configures the LED pin as an output.
 *
 * This function should be called in the setup() function of the main program.
 * It initializes the serial communication at 9600 baud rate and sets the LED pin
 * as an output to allow control of the built-in LED.
 */
void setupPins();

/**
 * @brief Reads the potentiometer value from the analog pin.
 *
 * @return The analog value read from the potentiometer (range: 0 to 1023).
 *
 * This function reads the analog value from the potentiometer connected to the
 * analog pin (POT_PIN) and returns the value. The value can be used to determine
 * the position of the potentiometer.
 */
int readPotentiometer();

/**
 * @brief Checks the potentiometer value against the threshold and controls the LED.
 *
 * @param potValue The analog value read from the potentiometer.
 *
 * This function prints the potentiometer value to the Serial Plotter for visualization.
 * It then checks if the potentiometer value exceeds the defined threshold (THRESHOLD).
 * If the value exceeds the threshold, the built-in LED (LED_PIN) is turned on. Otherwise,
 * the LED is turned off.
 */
void checkThresholdAndControlLED(int potValue, int threshold);

/**
 * @brief Waits the specified interval in msec.
 * @param interval The time to waig in msec.
 */
void waitMillis(unsigned long interval);

#endif // POTENTIOMETER_H
