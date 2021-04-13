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

#ifndef ASCD_LEONARDO_4X
    unsigned long LCDCycleMillis;
    unsigned long buttonCycleMillis;
    byte moduleActiveLCD;
    bool lockActiveLCD;
    byte lockActiveLCDCount;
#endif

#if defined(ONLINE)
    unsigned long serialCycleMillis;
    bool serialCycleReady = false;
#endif

    // Private Class Functions
    Config config;

public:
    // Public Class Functions
    CycleTimer();
    void updateTimer(byte module);
    void clearTimer(byte module);
    bool mainCycle();

#ifndef ASCD_LEONARDO_4X
    bool buttonCycle();
    void LCDCycle();
    void setLCDActiveModule();
    byte getLCDActiveModule();
#endif
#if defined(ONLINE)
    void serialCycle();
    bool getSerialCycleReady();
#endif

    byte getSeconds(byte module);
    byte getMinutes(byte module);
    byte getHours(byte module);
};
#endif