#ifndef SETUP_CHARGE_LED_MID_VOLTAGE_H
#define SETUP_CHARGE_LED_MID_VOLTAGE_H

#include <Config.h>
#include <Arduino.h>
#include <WriteOutput.h>
#include <ReadInput.h>
#include <ConfigEEPROM.h>

class SetupChargeLEDMidVoltage
{
private:
    int chargeLedPinMidVoltageArray[4];

    // External Classes
    Config config;
    WriteOutput writeOutput;
    ConfigEEPROM configEEPROM;
    ReadInput readInput;

    // Private Class Functions
    void getChargeMidVoltage();
    void saveToEEPROM();
    
public:
    // Public Class Functions
    SetupChargeLEDMidVoltage();
    void init();
};
#endif