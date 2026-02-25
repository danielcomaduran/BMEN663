// PPG.ino
#include "PPG.h"

Ppg ppg(A1);  // Sensor pin (LED connected directly to 5V)

const uint8_t print_every = 3;  // Print every Nth sample → 60Hz / 6 = 10Hz display
uint8_t sample_count = 0;

void setup() {
  Serial.begin(115200);
  ppg.setup();
}

void loop() {
  if (ppg.update()) {
    sample_count++;
    if (sample_count >= print_every) {
      sample_count = 0;
      Serial.print("max:600, min:400, baseline:512, ppg:");
      Serial.println(ppg.get_ppg());
    }
  }
}
