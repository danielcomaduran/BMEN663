#include "thermometer.h"

void setupTemperature() {
    Serial.begin(9600);
}

float readTemperature() {
    float sumTemp = 0;
    
    // Take multiple samples and average them
    for(int i = 0; i < TEMP_SAMPLES; i++) {
        int sensorValue = analogRead(TEMP_PIN);
        
        // Convert ADC value to resistance
        float voltage = sensorValue / 1024.0;
        float resistance = REFERENCE_RESISTOR * (1.0 / voltage - 1.0);
        
        // Use Steinhart-Hart equation to convert to temperature
        float steinhart = log(resistance / THERMISTOR_R0);
        steinhart /= THERMISTOR_B;
        steinhart += 1.0 / THERMISTOR_T0;
        float tempC = (1.0 / steinhart) - 273.15;
        
        sumTemp += tempC;
        delay(2);
    }
    
    return sumTemp / TEMP_SAMPLES;
}

void plotTemperature(float temperature) {
    Serial.println(temperature);
}

void waitMillis(unsigned long interval) {
    delay(interval);
}
