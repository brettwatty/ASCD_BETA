#ifndef BUZZER_H
#define BUZZER_H
#include <Arduino.h>
#include <Variables.h>

class Buzzer
{
private:
    // Buzzer pin Analog A2
    //const byte BUZZ = 5; // PCB Version 1.1
    const byte BUZZ = 16; // PCB Version 1.11

public:
    // Public Class Functions
    Buzzer();
    void init();
    void buzzerStart();
    void buzzerFinished();
    void buzzerKeyPress();
};

#endif