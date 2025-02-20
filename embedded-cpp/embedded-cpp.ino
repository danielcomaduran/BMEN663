#include <Arduino.h>

class ThresholdSensor {
private:
    const int analogPin;
    const int digitalPin;
    const int threshold;
    int analogValue;
    int digitalValue;

public:
    ThresholdSensor(int aPin, int dPin, int thresh) : 
        analogPin(aPin), 
        digitalPin(dPin), 
        threshold(thresh),
        analogValue(0),
        digitalValue(0) {
        pinMode(digitalPin, OUTPUT);
    }

    void read() {
        analogValue = analogRead(analogPin);
        digitalValue = (analogValue > threshold) ? 1023 : 0;
        digitalWrite(digitalPin, (analogValue > threshold));
    }

    void printValues() {
        Serial.print("analog:");
        Serial.print(analogValue);
        Serial.print(" digital:");
        Serial.println(digitalValue);
    }
};

ThresholdSensor sensor(A0, 2, 512);

void setup() {
    Serial.begin(9600);
}

void waitMillis(unsigned long interval) {
    static unsigned long lastMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - lastMillis >= interval) {
        lastMillis = currentMillis;
    }
}

void loop() {
    sensor.read();
    sensor.printValues();
    waitMillis(10);
}