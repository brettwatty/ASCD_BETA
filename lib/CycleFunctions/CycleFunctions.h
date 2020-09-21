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
#include <SerialWIFI.h>

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
    boolean dischargeCompleted[modulesCount];
    unsigned long dischargeMilliSecondsPrevious[modulesCount];

    int milliOhms[modulesCount];

    float batteryInitialVoltage[modulesCount];

    byte faultCode[modulesCount];

#if defined(ASCD_NANO_4X)
    // Fan Variables
    boolean fanOn = false;
#endif
#if defined(ONLINE)
    // Serial Variables
    boolean readSerialResponse = false;
    byte countSerialSend = 0;
#endif

    // Private Class Functions
    ReadInput readInput;
    WriteOutput writeOutput;
    OutputLCD outputLCD;
    CycleTimer cycleTimer;
    Buzzer buzzer;
    Temperature temperature;
    InputDevices inputDevices;
    SerialWIFI serialWIFI;

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