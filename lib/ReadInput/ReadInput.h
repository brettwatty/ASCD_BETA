#ifndef READ_INPUT__H
#define READ_INPUT__H

#include <Config.h>
#include <ConfigEEPROM.h>
#include <Arduino.h>

#if defined(ASCD_LEONARDO_4X)
#include <Wire.h>
#include <SparkFun_ADS1015_Arduino_Library.h>
#include <Smoothed.h>
#endif

class ReadInput
{
private:
#if defined(ASCD_MEGA_8X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Mega 8x

    // Analog and Digital Pin Mapping
    const byte batteryVoltagePin[MODULES_COUNT] = {A0, A2, A4, A6, A8, A10, A12, A14};
    const byte batteryVoltageDropPin[MODULES_COUNT] = {A1, A3, A5, A7, A9, A11, A13, A15};
    const byte chargeLedPin[MODULES_COUNT] = {23, 26, 29, 32, 35, 38, 41, 44};

    // Private Class Functions
    int getInput(const byte arrayPin);
#elif defined(ASCD_NANO_4X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Nano 4x
    // Array Pins for getInput function

    // Mux control pins
    const byte S0 = 12;
    const byte S1 = 11;
    const byte S2 = 10;
    const byte S3 = 9;

    // Mux Pin Mapping
    const bool batteryVoltagePin[MODULES_COUNT][4] = {{1, 1, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 0}, {1, 0, 1, 0}};
    const bool batteryVoltageDropPin[MODULES_COUNT][4] = {{1, 1, 1, 1}, {0, 1, 1, 1}, {1, 0, 1, 1}, {0, 0, 1, 1}};
    const bool chargeLedPin[MODULES_COUNT][4] = {{0, 1, 0, 1}, {0, 0, 0, 1}, {0, 1, 1, 0}, {0, 0, 1, 0}};

    // Mux SIG pin Analog A0
    const byte SIG = 14;

    // Private Class Functions

    int getInput(const bool arrayPins[]);
#elif defined(ASCD_LEONARDO_4X)

    const uint8_t addressBatt = 0x48;
    const uint8_t addressShunt = 0x49;

    ADS1015 *adsChip[2];

    const byte batteryVoltagePin[MODULES_COUNT] = {3, 2, 0, 1};
    const byte batteryVoltageDropPin[MODULES_COUNT] = {3, 2, 1, 0};
    const byte chargeLedPin[MODULES_COUNT] = {13, 10, 8, 4};

    // Private Class Functions
    int getInput(const byte adcChip, const byte arrayPin);
#endif

    // Private Class Functions

#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    float readVcc();
#endif

    ConfigEEPROM configEEPROM;
    Config config;

public:
    // Public Class Functions
    ReadInput();
    void init();
    int batteryVoltage(byte module);
    int batteryVoltageDrop(byte module);
    bool chargeLed(byte module);
#if (defined(ASCD_NANO_4X) && defined(SETUP_CHARGE_LED_MID_VOLTAGE))
    int chargeLedVoltage(byte module);
#endif
};
#endif