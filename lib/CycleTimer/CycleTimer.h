#ifndef CYCLE_TIMER_H
#define CYCLE_TIMER_H
#include <Config.h>

#include <Arduino.h>

class CycleTimer
{
private:
    // Timmer HH:MM:SS
    unsigned long millisCleared[MODULES_COUNT];
    byte seconds[MODULES_COUNT];
    byte minutes[MODULES_COUNT];
    byte hours[MODULES_COUNT];

    unsigned long mainCycleMillis;
    unsigned long LCDCycleMillis;
#if defined(ONLINE)
    unsigned long serialCycleMillis;
#endif
    unsigned long buttonCycleMillis;

    byte moduleActiveLCD;
    bool lockActiveLCD;
    byte lockActiveLCDCount;
    bool serialCycleReady = false;

    

    // Private Class Functions
    Config config;

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
    bool getSerialCycleReady();
    byte getSeconds(byte module);
    byte getMinutes(byte module);
    byte getHours(byte module);
};
#endif