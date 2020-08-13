#ifndef OUTPUT_LCD_H
#define OUTPUT_LCD_H
#include <Arduino.h>
#include <Variables.h>

class OutputLCD
{
private:
#if defined(ASCD_MEGA_8X)
    char lcdLine0[20];
    char lcdLine1[20];
    char lcdLine2[20];
    char lcdLine3[20];
#elif defined(ASCD_NANO_4X)
    char lcdLine0[16];
    char lcdLine1[16];
#endif

    // Private Class Functions

public:
    // Public Class Functions
    OutputLCD();
    void init();
    void startup();
    void displayLCDCycle();
    void batteryCheckLCD(byte module, float batteryVoltage);
    void batteryBarcodeLCD(byte module, float batteryVoltage);
    void batteryChargeLCD(byte module, bool chargeRecharge, float batteryVoltage, float batteryInitialVoltage, byte batteryTemp, byte hours, byte minutes, byte seconds);
    void milliOhmsLCD(byte module, int milliOhms);
    void batteryRestLCD(byte module, float batteryVoltage, byte hours, byte minutes, byte seconds);
    void batteryDischargeLCD(byte module, float batteryVoltage, float dischargeAmps, float dischargeMilliamps, byte batteryTemp, byte hours, byte minutes, byte seconds);
    void completeLCD(byte module, byte faultCode, int milliOhms, float dischargeMilliamps, float batteryVoltage);
};

#endif