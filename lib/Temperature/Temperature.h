#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Config.h>

#include <Arduino.h>

class Temperature
{
private:
    byte tempCount[MODULES_COUNT + 1];
    byte batteryCurrentTemp[MODULES_COUNT + 1];
    byte batteryInitialTemp[MODULES_COUNT];
    byte batteryHighestTemp[MODULES_COUNT];
#if defined(ASCD_MEGA_8X)
    const int8_t temperatureOffset[MODULES_COUNT + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Offset for Temperature sensors in + / - 1 e.g. 5: for readings 5 degrees celsius under. -2 equals for readings 2 degrees celsius over
#elif defined(ASCD_NANO_4X)
    const int8_t temperatureOffset[MODULES_COUNT + 1] = {0, 0, 0, 0, 0}; // Offset for Temperature sensors in + / - 1 e.g. 5: for readings 5 degrees celsius under. -2 equals for readings 2 degrees celsius over
#elif defined(ASCD_LEONARDO_4X)
const int8_t temperatureOffset[MODULES_COUNT] = {0, 0, 0, 0}; // Offset for Temperature sensors in + / - 1 e.g. 5: for readings 5 degrees celsius under. -2 equals for readings 2 degrees celsius over
#endif
    // Private Class Functions
    Config config;
    // Variables

public:
    // Public Class Functions
    Temperature();
    void init();
    void getTemperature(byte module, bool tempNow);
    byte processTemperature(byte module);
    byte getAmbientTemperature();
    byte getCurrentTemp(byte module);
    byte getInitialTemp(byte module);
    byte getHighestTemp(byte module);
    void setInitialTemp(byte module);
    void clearHighestTemp(byte module);
};
#endif