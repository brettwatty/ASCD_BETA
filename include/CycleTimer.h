#ifndef CYCLE_TIMER_H
#define CYCLE_TIMER_H
#include "Config.h"

#include <Arduino.h>

class CycleTimer
{
private:
    // Timmer HH:MM:SS
    unsigned long millisCleared[modulesCount];
    byte seconds[modulesCount];
    byte minutes[modulesCount];
    byte hours[modulesCount];

    unsigned long mainCycleMillis;
    unsigned long LCDCycleMillis;
#if defined(ONLINE)
    unsigned long serialCycleMillis;
#endif
    unsigned long buttonCycleMillis;

    byte moduleActiveLCD;
    boolean lockActiveLCD;
    byte lockActiveLCDCount;
    boolean serialCycleReady = false;

    

    // Private Class Functions

public:
    // Public Class Functions
    CycleTimer();
    void updateTimer(byte module);
    void clearTimer(byte module);
    bool buttonCycle();
    bool mainCycle();
    void LCDCycle();
#if defined(ONLINE)
    void serialCycle();
#endif
    void setLCDActiveModule();
    byte getLCDActiveModule();
    boolean getSerialCycleReady();
    byte getSeconds(byte module);
    byte getMinutes(byte module);
    byte getHours(byte module);
};
// extern configuration config;
#endif