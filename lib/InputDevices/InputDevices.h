#ifndef INPUT_DEVICES_H
#define INPUT_DEVICES_H

#include <Config.h>

#include <Arduino.h>

class InputDevices
{
private:
    bool lastButtonState = 0;
#if defined(ASCD_MEGA_8X)

// #define CLK 3 // Rotary Encoder PIN A CLK    - PCB Version 1.1
// #define DT 4  // Rotary Encoder PIN B DT     - PCB Version 1.1
#define CLK 6 // Rotary Encoder PIN A CLK       - PCB Version 2.+
#define DT 7  // Rotary Encoder PIN B DT        - PCB Version 2.+

#define BUTTON_H_L LOW
#define BUTTON_INPUT_MODE INPUT_PULLUP
    // Button pin - Pin 5 Rotary Encoder Button (BTN)
    const byte BTN = 5;
#elif defined(ASCD_NANO_4X)
#define BUTTON_H_L HIGH
#define BUTTON_INPUT_MODE INPUT
    // Button pin Analog A1
    const byte BTN = 15;
// #elif defined(ASCD_LEONARDO_4X)

// #endif
    // Private Class Functions

public:
    // Public Class Functions
    InputDevices();
    void init();
    bool button();
};

#endif