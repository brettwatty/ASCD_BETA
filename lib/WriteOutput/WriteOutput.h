#ifndef WRITE_OUTPUT_H
#define WRITE_OUTPUT_H

#include <Config.h>

#include <Arduino.h>

class WriteOutput
{
private:
#if defined(ASCD_MEGA_8X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Mega 8x
    // Pin Definitions
    const byte chargeMosfetPins[MODULES_COUNT] = {22, 25, 28, 31, 34, 37, 40, 43};
    const byte dischargeMosfetPins[MODULES_COUNT] = {24, 27, 30, 33, 36, 39, 42, 45};

#elif defined(ASCD_NANO_4X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Nano 4x
    const byte latchPin = 7; // Latch pin (ST_CP) of 74HC595
    const byte clockPin = 8; // Clock pin (SH_CP) of 74HC595
    const byte dataPin = 6;  // Data in (DS) of 74HC595

    // Pin Definitions
    const byte chargeMosfetPins[MODULES_COUNT] = {0, 2, 4, 6};
    const byte dischargeMosfetPins[MODULES_COUNT] = {1, 3, 5, 7};

    // Fan pin 5 PWM Digital
    const byte FAN = 5; // Leonardo Nano 4x PCB Version 1.11+ only

    byte digitalPinsState = 0b00000000;
#elif defined(ASCD_LEONARDO_4X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Leonardo 4x
    // Pin Definitions
    // ********* Need to add LED pins
    const byte chargeMosfetPins[MODULES_COUNT] = {14, 5, 9, 6};
    const byte dischargeMosfetPins[MODULES_COUNT] = {19, 18, 17, 16};

    // Fan pin 15 Digital
    const byte FAN = 15; // A1
#endif
    // Private Class Functions
    void setOutput(const byte arrayPin, bool onOff);

public:
    // Public Class Functions
    WriteOutput();
    void init();
    void chargeMosfetOn(byte module);
    void chargeMosfetOff(byte module);
    void dischargeMosfetOn(byte module);
    void dischargeMosfetOff(byte module);
#if (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X))
    void fanControl(bool onOff);
#endif
};

#endif
