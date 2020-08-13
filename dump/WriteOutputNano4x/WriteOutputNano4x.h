#ifndef WRITE_OUTPUT_NANO_4X_H
#define WRITE_OUTPUT_NANO_4X_H
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

    const byte latchPin = 7; // Latch pin (ST_CP) of 74HC595
    const byte clockPin = 8; // Clock pin (SH_CP) of 74HC595
    const byte dataPin = 6; // Data in (DS) of 74HC595

    // Pin Definitions
    const byte chargeMosfetPins[4] = {0, 2, 4, 6};
    const byte dischargeMosfetPins[4] = {1, 3, 5, 7};

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
