#ifndef WRITE_OUTPUT_MEGA_8X_H
#define WRITE_OUTPUT_MEGA_8X_H
#include <Arduino.h>
class WriteOutput
{
private:
    // For defining what battery module
    byte module;

    // Array Pin for setOutput function
    byte arrayPin;

    // On / Off state for setOutput function
    bool onOff;

    // Pin Definitions
    const byte chargeMosfetPins[8] = {22, 25, 28, 31, 34, 37, 40, 43};
    const byte dischargeMosfetPins[8] = {24, 27, 30, 33, 36, 39, 42, 45};

    // Private Class Functions
    void init();
    void setOutput(const byte arrayPin, bool onOff);

public:
    // Public Class Functions
    WriteOutput();
    void chargeMosfetOn(byte module);
    void chargeMosfetOff(byte module);
    void dischargeMosfetOn(byte module);
    void dischargeMosfetOff(byte module);
};

#endif
