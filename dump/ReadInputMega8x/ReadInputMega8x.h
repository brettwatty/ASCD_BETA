#ifndef READ_INPUT_MEGA_8X_H
#define READ_INPUT_MEGA_8X_H
#include <Arduino.h>
class ReadInput
{
private:
    // For defining what battery module
    byte module;

    // Array Pin for getInput function
    byte arrayPin;

    // Analog and Digital Pin Mapping
    const byte batteryVoltagePin[8] = {A0, A2, A4, A6, A8, A10, A12, A14};
    const byte batteryVoltageDropPin[8] = {A1, A3, A5, A7, A9, A11, A13, A15};
    const byte chargeLedPin[8] = {23, 26, 29, 32, 35, 38, 41, 44};

    // Private Class Functions
    void init();
    float getInput(const byte arrayPin);
    float readVcc();

public:
    // Public Class Functions
    ReadInput();
    float batteryVoltage(byte module);
    float batteryVoltageDrop(byte module);
    bool chargeLed(byte module);
    bool batteryCheck(byte module);
};
#endif