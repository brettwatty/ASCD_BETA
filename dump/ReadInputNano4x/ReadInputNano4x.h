#ifndef READ_INPUT_NANO_4X_H
#define READ_INPUT_NANO_4X_H
#include <Arduino.h>
class ReadInput
{
private:
  // For defining what battery module
  byte module;

  // Array Pins for getInput function
  bool arrayPins[];

  // Mux control pins
  const byte S0 = 12;
  const byte S1 = 11;
  const byte S2 = 10;
  const byte S3 = 9;

  // Mux Pin Mapping
  const bool batteryVoltagePin[4][4] = {{1, 1, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 0}, {1, 0, 1, 0}};
  const bool batteryVoltageDropPin[4][4] = {{1, 1, 1, 1}, {0, 1, 1, 1}, {1, 0, 1, 1}, {0, 0, 1, 1}};
  const bool chargeLedPin[4][4] = {{0, 1, 0, 1}, {0, 0, 0, 1}, {0, 1, 1, 0}, {0, 0, 1, 0}};

  // Mux SIG pin Analog A0
  const byte SIG = 14;

  // Private Class Functions
  void init();
  float getInput(const bool arrayPins[]);
  float readVcc();

public:
  // Public Class Functions
  ReadInput();
  float batteryVoltage(byte module);
  float batteryVoltageDrop(byte module);
  bool chargeLed(byte module);
};
#endif