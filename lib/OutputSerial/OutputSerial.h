#ifndef OUTPUT_SERIAL_H
#define OUTPUT_SERIAL_H

#include <Config.h>

#include <Arduino.h>

class OutputSerial
{
private:
    char serialLine0[50];
    char serialLine1[50];

    // Private Class Functions

public:
    // Public Class Functions
    OutputSerial();
    void init();
    void startup();
    void displaySerialCycle();
    void batteryCheckSerial(byte module, int batteryVoltage);
    void batteryBarcodeSerial(byte module, int batteryVoltage);
    void batteryChargeSerial(byte module, bool chargeRecharge, int batteryVoltage, int batteryInitialVoltage, byte batteryTemp, byte hours, byte minutes, byte seconds);
    void milliOhmsSerial(byte module, int milliOhms);
    void batteryRestSerial(byte module, int batteryVoltage, byte hours, byte minutes, byte seconds);
    void batteryDischargeSerial(byte module, int batteryVoltage, int dischargeAmps, int dischargeMilliamps, byte batteryTemp, byte hours, byte minutes, byte seconds);
    void completeSerial(byte module, byte faultCode, int milliOhms, int dischargeMilliamps, int batteryVoltage);
};

#endif