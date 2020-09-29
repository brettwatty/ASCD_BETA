#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "Config.h"

#include <Arduino.h>

class Temperature
{
private:
    byte tempCount[modulesCount + 1];
    byte batteryCurrentTemp[modulesCount + 1];
    byte batteryInitialTemp[modulesCount];
    byte batteryHighestTemp[modulesCount];
#if defined(ASCD_MEGA_8X)
    const int8_t temperatureOffset[modulesCount + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Offset for Temperature sensors in + / - 1 e.g. 5: for readings 5 degrees celsius under. -2 equals for readings 2 degrees celsius over
#elif defined(ASCD_NANO_4X)
    const int8_t temperatureOffset[modulesCount + 1] = {0, 0, 0, 0, 0}; // Offset for Temperature sensors in + / - 1 e.g. 5: for readings 5 degrees celsius under. -2 equals for readings 2 degrees celsius over
#endif
    // Private Class Functions
    // Variables

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
    void clearHighestTemp(byte module);
};
// extern configuration config;
#endif