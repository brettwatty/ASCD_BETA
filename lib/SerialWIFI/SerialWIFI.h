#ifndef SERIAL_WIFI_H
#define SERIAL_WIFI_H

#include <Config.h>

#include <Arduino.h>

class SerialWIFI
{
private:
#if defined(ASCD_MEGA_8X)
    char serialSendString[1024];
#elif (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X))
    char serialSendString[400];
#endif

    bool barcodeScanned[MODULES_COUNT];
    bool insertData[MODULES_COUNT];
    bool restartCycle[MODULES_COUNT];
    bool resetASCD = false;

    // Private Class Functions

public:
    // Public Class Functions
    SerialWIFI();
    void init();
    void sendSerial();
    void readSerial();
    void clearSerialSendString();
    void returnCodes(int codeID);
    void ambientTemperatureSerial(byte ambientTemperature);
    void batteryCheckSerial(byte module);
    void batteryBarcodeSerial(byte module);
    void batteryChargeSerial(byte module, bool chargeRecharge, byte batteryInitialTemp, int batteryInitialVoltage, byte batteryTemp, byte hours, byte minutes, byte seconds, int batteryVoltage, byte batteryHighestTemp);
    void milliOhmsSerial(byte module, int milliOhms, int batteryVoltage);
    void batteryRestSerial(byte module, int milliOhms, byte batteryTemp, byte hours, byte minutes, byte seconds, int batteryVoltage);
    void batteryDischargeSerial(byte module, byte hours, byte minutes, byte seconds, byte batteryInitialTemp, int batteryInitialVoltage, byte batteryTemp, int batteryVoltage, int dischargeAmps, int dischargeMilliamps, byte batteryHighestTemp, int milliOhms);
    void completeSerial(byte module, byte faultCode, int batteryVoltage);
    bool getBarcodeScanned(byte module);
    bool getRestartCycle(byte module);
    void resetRestartCycle(byte module);
    void resetBarcodeScanned(byte module);
    void insertDataFlag(byte module);
    bool getInsertDataFlag(byte module);
    bool getResetASCD();
    void resetInsertDataFlag(byte module);
};

#endif