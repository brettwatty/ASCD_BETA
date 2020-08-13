#ifndef CYCLE_FUNCTIONS_H
#define CYCLE_FUNCTIONS_H
#include <Arduino.h>

#include <ReadInput.h>
#include <WriteOutput.h>
#include <OutputLCD.h>
#include <CycleTimer.h>
#include <Buzzer.h>
#include <Temperature.h>
#include <InputDevices.h>
#if defined(ONLINE)
#include <SerialWIFI.h>
#endif

class Cycle
{
private:
    byte cycleState[modulesCount]; // Current Cycle State of ASCD Module
    byte cycleCount[modulesCount]; // Reusable Count Array for Cycles

    float batteryVoltage = 0.00;
    float batteryShuntVoltage = 0.00;
    float dischargeAmps = 0.00;
    float dischargeMilliamps[modulesCount];
    int dischargeMillisTime = 0;
    boolean dischargeCompleted[modulesCount] = false;
    unsigned long dischargeMilliSecondsPrevious[modulesCount];

    int milliOhms[modulesCount];

    float batteryInitialVoltage[modulesCount];

    byte faultCode[modulesCount];

    // Fan Variables
    boolean fanOn = false;

    // Serial Variables
    boolean readSerialResponse = false;
    byte countSerialSend = 0;

    // Private Class Functions
    ReadInput readInput;
    WriteOutput writeOutput;
    OutputLCD outputLCD;
    CycleTimer cycleTimer;
    Buzzer buzzer;
    Temperature temperature;
    InputDevices inputDevices;
#if defined(ONLINE)
    SerialWIFI serialWIFI;
#endif

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