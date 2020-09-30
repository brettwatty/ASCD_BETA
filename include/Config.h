#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// #define ASCD_MEGA_8X
#define ASCD_NANO_4X

// #define OFFLINE
#define ONLINE

#define SERIAL_PIN_SS // SS: Software Serial
// #define SERIAL_PINS_HS  // HS: Hardware Serial

#if defined(ASCD_MEGA_8X)
// ASCD Mega 8x Settings

#define MEGA_1X // ASCD MEGA PCB Version 1.1
// #define MEGA_2X // ASCD MEGA PCB Version 2.0+

const byte modulesCount = 8; // Number of Modules
// const float shuntResistor[modulesCount] = {3.46, 3.45, 3.44, 3.45, 3.41, 3.42, 3.41, 3.39};
// Add baud rate for Serials - If Online
#elif defined(ASCD_NANO_4X)
// ASCD Nano 4x Settings
const byte modulesCount = 4; // Number of Modules
// const float shuntResistor[modulesCount] = {3.37, 3.35, 3.38, 3.3};
// const float chargeLedPinMidVoltage[modulesCount] = {2.11, 2.07, 2.12, 2.33}; // Array for each Mid On / Off Voltage of the TP5100 Charge LED Pins
// Add baud rate for Serials - If Online
#endif

struct configuration
{
    bool useReferenceVoltage = true;        // "true" to use the 5v regulator as the reference voltage or "false" to use the 1.1V internal voltage reference
    int referenceVoltage = 4957;            // 5V output of Arduino
    int internalReferenceVoltage = 1054;    // 1.1V internal voltage reference of Arduino
    int defaultBatteryCutOffVoltage = 2800; // Voltage that the discharge stops
    int storageChargeVoltage = 3800;        // Storage charge voltage for recharge cycle. Use 0.00 for no storage charge. Can't be greater than 3.80v
    int batteryVoltageLeak = 500;           // On the initial screen "BATTERY CHECK" observe the highest voltage of each module and set this value slightly higher
    int lowMilliAmps = 1000;                // This is the value of Milli Amps that is considered low and does not get recharged because it is considered faulty
    int highMilliOhms = 500;                // This is the value of Milli Ohms that is considered high and the battery is considered faulty
    int offsetMilliOhms = 0;                // Offset calibration for MilliOhms
    byte restTimeMinutes = 0;               // The time in Minutes to rest the battery after charge. 0-59 are valid
    byte chargingTimeout = 8;               // The timeout in Hours for charging
    byte tempThreshold = 7;                 // Warning Threshold in degrees above initial Temperature
    byte tempMaxThreshold = 10;             // Maximum Threshold in degrees above initial Temperature - Considered Faulty
    bool rechargeCycle = true;              // Run the Recharge Cycle "true" to run and "false" to skip to Completed Cycle
    byte screenTime = 4;                    // Time in Seconds (Cycles) per Active Screen

    int shuntResistor[modulesCount] = {3370, 3350, 3380, 3300};
    int chargeLedPinMidVoltage[modulesCount] = {2110, 2070, 2120, 2330}; // Array for each Mid On / Off Voltage of the TP5100 Charge LED Pins
    uint8_t dallasSerials[modulesCount + 1][8] =
    {{0x28, 0x3C, 0x47, 0x79, 0x97, 0x05, 0x03, 0x42},
     {0x28, 0x87, 0xA1, 0x79, 0xA2, 0x00, 0x03, 0xEF},
     {0x28, 0xE9, 0x87, 0x79, 0xA2, 0x00, 0x03, 0x5B},
     {0x28, 0xB4, 0x4B, 0x79, 0xA2, 0x00, 0x03, 0x3C},
     {0x28, 0x06, 0x18, 0x79, 0xA2, 0x01, 0x03, 0x4A}};
};





static configuration config;

#endif