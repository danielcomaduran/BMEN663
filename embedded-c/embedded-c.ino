// Import libraries
#include <Arduino.h>

// Pin definitions
const int POT_PIN = A0;    // Potentiometer connected to analog pin A0
const int LED_PIN = 13;    // LED connected to digital pin 13
const int THRESHOLD = 512; // Threshold value (0-1023)

void setup() {
    // Initialize serial communication at 9600 baud
    Serial.begin(9600);
    
    // Configure LED pin as output
    pinMode(LED_PIN, OUTPUT);
    
    // Configure potentiometer pin as input
    pinMode(POT_PIN, INPUT);
}

void loop() {
    // Read the analog value from potentiometer (0-1023)
    int potValue = analogRead(POT_PIN);
    
    // Calculate voltage (0-5V)
    float voltage = potValue * (5.0 / 1023.0);
    
    // Print voltage for serial plotter
    Serial.println(voltage);
    
    // Check if value exceeds threshold
    if (potValue > THRESHOLD) {
        digitalWrite(LED_PIN, HIGH);  // Turn LED on
    } else {
        digitalWrite(LED_PIN, LOW);   // Turn LED off
    }
    
    // Small delay to prevent serial buffer overflow
    static unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 10) {
        previousMillis = currentMillis;
    }
}