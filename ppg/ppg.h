#ifndef PPG_H
#define PPG_H

#include <Arduino.h>

/**
 * Photoplethysmogram (PPG) sensor class
 * Reads analog signal from a photoresistor and LED circuit.
 * Call update() every loop, then read get_ppg() when update() returns true.
 */
class Ppg {
private:
  const uint8_t sensor_pin;
  static const uint8_t buffer_size = 3;  // Small window to preserve pulse shape
  uint16_t raw_buffer[buffer_size];
  uint32_t raw_sum;
  uint8_t raw_index;
  float baseline;          // Slow IIR tracking DC level
  uint16_t ppg_value;      // Last computed output
  bool initialized;        // True after first sample
  uint32_t last_cycle_time;
  const uint32_t cycle_period = 16667UL;  // 60 Hz in us
  const float gain = 20.0f;

public:
  /**
   * Constructor
   * @param sensor Analog pin connected to the photoresistor
   */
  Ppg(uint8_t sensor);

  /**
   * Initialize the PPG sensor (call once in setup)
   */
  void setup();

  /**
   * Update the PPG reading. Call every loop iteration.
   * @return true if a new sample was taken, false otherwise
   */
  bool update();

  /**
   * Get the last computed PPG value.
   * AC-coupled and amplified, centered at 512.
   * @return PPG value in range 0-1023
   */
  uint16_t get_ppg();
};

#endif
