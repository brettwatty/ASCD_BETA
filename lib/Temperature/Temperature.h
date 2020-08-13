#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <Arduino.h>
#include <Variables.h>

class Temperature
{
private:
    byte tempCount[modulesCount + 1];
    byte batteryCurrentTemp[modulesCount + 1];
    byte batteryInitialTemp[modulesCount];
    byte batteryHighestTemp[modulesCount];

    // Private Class Functions

public:
    // Public Class Functions
    Temperature();
    void init();
    void getTemperature(byte module, boolean tempNow);
    byte processTemperature(byte module);
    byte getAmbientTemperature();
    byte getCurrentTemp(byte module);
    byte getInitialTemp(byte module);
    byte getHighestTemp(byte module);
    void setInitialTemp(byte module);
};

#endif