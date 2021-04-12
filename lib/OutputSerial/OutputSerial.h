#ifndef OUTPUT_SERIAL_H
#define OUTPUT_SERIAL_H

#include <Config.h>

#include <Arduino.h>

class OutputSerial
{
private:
// #if defined(ASCD_MEGA_8X)
//     char lcdLine0[21];
//     char lcdLine1[21];
//     char lcdLine2[21];
//     char lcdLine3[21];
// #elif defined(ASCD_NANO_4X)
//     char lcdLine0[16];
//     char lcdLine1[16];
// #endif

    // Private Class Functions

public:
    // Public Class Functions
    OutputSerial();
    void init();
    void startup();
    // void displayLCDCycle();
    // void batteryCheckLCD(byte module, int batteryVoltage);
    // void batteryBarcodeLCD(byte module, int batteryVoltage);
    // void batteryChargeLCD(byte module, bool chargeRecharge, int batteryVoltage, int batteryInitialVoltage, byte batteryTemp, byte hours, byte minutes, byte seconds);
    // void milliOhmsLCD(byte module, int milliOhms);
    // void batteryRestLCD(byte module, int batteryVoltage, byte hours, byte minutes, byte seconds);
    // void batteryDischargeLCD(byte module, int batteryVoltage, int dischargeAmps, int dischargeMilliamps, byte batteryTemp, byte hours, byte minutes, byte seconds);
    // void completeLCD(byte module, byte faultCode, int milliOhms, int dischargeMilliamps, int batteryVoltage);
};

#endif