#ifndef SETUP_TEMP_SENSOR_SERIALS_H
#define SETUP_TEMP_SENSOR_SERIALS_H

#include <Config.h>
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WriteOutput.h>
#include <ConfigEEPROM.h>

class SetupTempSensorSerials
{
private:
    byte foundTempSensorsCount;
    float sensorTemp;
    float tempSensorAverageTemp;
    bool tempSensorSerialCompleted[TEMP_SENSENSORS_COUNT];
    byte tempSensorSerialOutput[TEMP_SENSENSORS_COUNT];
    bool detectionComplete = false;
    byte pendingDetection = 0;

    // External Classes
    Config config;
    WriteOutput writeOutput;
    ConfigEEPROM configEEPROM;

    // Private Class Functions
    void run();
    void getTempSensorCount();
    void getTempSensorSerials();
    void getTempSensorAverageTemp();
    void printTempSensorSerial(DeviceAddress deviceAddress, bool first, bool last, bool comma);

public:
    // Public Class Functions
    SetupTempSensorSerials();
    void init();
    void getTempSensorModule();
};

#endif