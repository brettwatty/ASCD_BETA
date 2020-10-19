#ifndef CYCLE_FUNCTIONS_H
#define CYCLE_FUNCTIONS_H

#include <Config.h>

#include <Arduino.h>
#include <ReadInput.h>
#include <WriteOutput.h>
#include <OutputLCD.h>
#include <CycleTimer.h>
#include <Buzzer.h>
#include <Temperature.h>
#include <InputDevices.h>
#include <SerialWIFI.h>
#include <ConfigEEPROM.h>


class Cycle
{
private:
    byte cycleState[MODULES_COUNT]; // Current Cycle State of ASCD Module
    byte cycleCount[MODULES_COUNT]; // Reusable Count Array for Cycles

    int batteryVoltage = 0;
    int batteryShuntVoltage = 0;
    int dischargeAmps = 0;
    float dischargeMilliamps[MODULES_COUNT];
    int dischargeMillisTime = 0;
    bool dischargeCompleted[MODULES_COUNT];
    unsigned long dischargeMilliSecondsPrevious[MODULES_COUNT];

    int milliOhms[MODULES_COUNT];

    float batteryInitialVoltage[MODULES_COUNT];

    byte faultCode[MODULES_COUNT];

#if defined(ASCD_NANO_4X)
    // Fan Variables
    bool fanOn = false;
#endif
#if defined(ONLINE)
    // Serial Variables
    bool readSerialResponse = false;
    byte countSerialSend = 0;
#endif

    // Private Class Functions
    Config config;
    ReadInput readInput;
    WriteOutput writeOutput;
    OutputLCD outputLCD;
    CycleTimer cycleTimer;
    Buzzer buzzer;
    Temperature temperature;
    InputDevices inputDevices;
    SerialWIFI serialWIFI;
    ConfigEEPROM configEEPROM;

    

    void mainCycle();
    void nextCycle(byte module);
    void processFault(byte module);
    void batteryCheck(byte module);
    void batteryBarcode(byte module);
    void batteryCharge(byte module, bool chargeRecharge);
    void milliOhmsCycle(byte module);
    void dischargeCycle(byte module);
    void restCycle(byte module);
    void completeCycle(byte module);

public:
    // Public Class Functions
    Cycle();
    void init();
    void cycleRun();
};
#endif