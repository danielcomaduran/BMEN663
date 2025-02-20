#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

/**
 * @brief Potentiometer class to handle reading from a potentiometer,
 * controlling an LED, and generating a square wave signal.
 */
class Potentiometer 
{
public:
    /**
     * @brief Constructor for the Potentiometer class.
     * @param potPin Analog pin connected to the potentiometer.
     * @param ledPin Digital pin connected to the built-in LED.
     * @param threshold Threshold value for turning on the LED and generating a square wave.
     */
    Potentiometer(int potPin, int ledPin, int threshold);

    /**
     * @brief Initializes the serial communication and configures the LED pin as an output.
     *
     * This function should be called in the setup() function of the main program.
     * It initializes the serial communication at 9600 baud rate and sets the LED pin
     * as an output to allow control of the built-in LED.
     */
    void begin();

    /**
     * @brief Updates the potentiometer value, controls the LED, and generates a square wave signal.
     *
     * This function should be called in the loop() function of the main program.
     * It reads the potentiometer value, checks the threshold, and generates a square wave signal
     * if the potentiometer value exceeds the threshold.
     */
    void update();

private:
    int potPin;             ///< Analog pin connected to the potentiometer
    int ledPin;             ///< Digital pin connected to the built-in LED
    int threshold;          ///< Threshold value for turning on the LED and generating a square wave
    int potValue;           ///< Variable to store the potentiometer value
    bool generateSquareWave;///< Flag to indicate whether to generate a square wave
    unsigned long lastToggleTime; ///< Last time the square wave toggled
    int squareWaveValue;    ///< Current value of the square wave

    /**
     * @brief Reads the potentiometer value from the analog pin.
     *
     * This function reads the analog value from the potentiometer connected to the
     * analog pin (potPin) and stores the value in potValue. It also prints the
     * potentiometer value and square wave value to the Serial Plotter.
     */
    void readPotentiometer();

    /**
     * @brief Checks the potentiometer value against the threshold and controls the LED.
     *
     * This function checks if the potentiometer value exceeds the defined threshold.
     * If the value exceeds the threshold, the built-in LED (ledPin) is turned on and
     * the square wave generation is enabled. Otherwise, the LED is turned off and
     * the square wave generation is disabled.
     */
    void checkThresholdAndControlLED();

    /**
     * @brief Generates a square wave signal.
     *
     * This function toggles the square wave value at a fixed frequency, creating a square
     * wave signal. The square wave value is printed to the Serial Plotter along with the
     * potentiometer value.
     */
    void generateSquareWaveSignal();
};

#endif // POTENTIOMETER_H
