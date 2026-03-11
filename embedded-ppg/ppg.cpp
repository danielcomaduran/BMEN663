#include "PPG.h"
#include <Arduino.h>

Ppg::Ppg(uint8_t sensor)
  : sensor_pin(sensor), raw_sum(0), raw_index(0),
    baseline(0.0f), ppg_value(512), initialized(false), last_cycle_time(0) {
  memset(raw_buffer, 0, sizeof(raw_buffer));
}

void Ppg::setup() {
  pinMode(sensor_pin, INPUT);
}

bool Ppg::update() {
  uint32_t now = micros();
  if (now - last_cycle_time < cycle_period) return false;
  last_cycle_time = now;

  // Update moving average
  raw_sum -= raw_buffer[raw_index];
  raw_buffer[raw_index] = analogRead(sensor_pin);
  raw_sum += raw_buffer[raw_index];
  raw_index = (raw_index + 1) % buffer_size;
  float avg = (float)raw_sum / buffer_size;

  // On first sample, seed the baseline with the actual sensor value
  // to avoid a large startup transient
  if (!initialized) {
    baseline = avg;
    initialized = true;
  }

  // Slow IIR low-pass filter tracks the DC baseline (~0.1 Hz cutoff)
  baseline = 0.01f * avg + 0.99f * baseline;

  // AC-couple: remove baseline, amplify, and center at 512
  float ac = (avg - baseline) * gain + 512.0f;

  // Clamp to valid ADC range
  if (ac < 0.0f)   ac = 0.0f;
  if (ac > 1023.0f) ac = 1023.0f;
  ppg_value = (uint16_t)ac;

  return true;
}

uint16_t Ppg::get_ppg() {
  return ppg_value;
}
