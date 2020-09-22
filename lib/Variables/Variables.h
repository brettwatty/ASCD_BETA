#ifndef VARIABLES_H
#define VARIABLES_H
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
const float shuntResistor[modulesCount] = {3.46, 3.45, 3.44, 3.45, 3.41, 3.42, 3.41, 3.39};
// Add baud rate for Serials - If Online
#elif defined(ASCD_NANO_4X)
// ASCD Nano 4x Settings
const byte modulesCount = 4; // Number of Modules
const float shuntResistor[modulesCount] = {3.28, 3.37, 3.31, 3.4};
const float chargeLedPinMidVoltage[modulesCount] = {2.08, 2.1, 2.06, 2.08}; // Array for each Mid On / Off Voltage of the TP5100 Charge LED Pins
// const byte pwmFanMinStart = 115;
// Add baud rate for Serials - If Online
#endif
// All ASCD Settings
const bool useReferenceVoltage = true;        // "true" to use the 5v regulator as the reference voltage or "false" to use the 1.1V internal voltage reference
const float referenceVoltage = 4.963;           // 5V output of Arduino
const float internalReferenceVoltage = 1.077;  // 1.1V internal voltage reference of Arduino
const float defaultBatteryCutOffVoltage = 2.8; // Voltage that the discharge stops
const byte restTimeMinutes = 1;                // The time in Minutes to rest the battery after charge. 0-59 are valid
const int lowMilliAmps = 1000;                 // This is the value of Milli Amps that is considered low and does not get recharged because it is considered faulty
const int highMilliOhms = 500;                 // This is the value of Milli Ohms that is considered high and the battery is considered faulty
const int offsetMilliOhms = 0;                 // Offset calibration for MilliOhms
const byte chargingTimeout = 8;                // The timeout in Hours for charging
const byte tempThreshold = 7;                  // Warning Threshold in degrees above initial Temperature
const byte tempMaxThreshold = 10;              // Maximum Threshold in degrees above initial Temperature - Considered Faulty
const float batteryVoltageLeak = 0.5;         // On the initial screen "BATTERY CHECK" observe the highest voltage of each module and set this value slightly higher
const byte screenTime = 4;                     // Time in Seconds (Cycles) per Active Screen
const bool rechargeCycle = true;               // Run the Recharge Cycle "true" to run and "false" to skip to Completed Cycle
const float storageChargeVoltage = 3.80;       // Storage charge voltage for recharge cycle. Use 0.00 for no storage charge. Can't be greater than 3.80v
#endif