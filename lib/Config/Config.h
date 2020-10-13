#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#if defined(ASCD_WIFI_CLIENT)
// WIFI Client Settings

const char ssid[] = "Taihoro";                 // SSID
const char password[] = "Mahi-Tahi$";          // Password
const char server[] = "submit.vortexit.co.nz"; // Server to connect to send and receive data
const char userHash[] = "c4ca4238";            // Database Hash - this is unique per user - Get this from Charger / Discharger Menu -> View
const int CDUnitID = 264;                      // CDUnitID this is the Units ID - this is unique per user - Get this from Charger / Discharger Menu -> View -> Select your Charger / Discharger

#else
// ASCD Settings

#if defined(ASCD_MEGA_8X)
// ASCD Mega 8x Settings

const byte modulesCount = 8; // Number of Modules
// Add baud rate for Serials - If Online

#elif defined(ASCD_NANO_4X)
// ASCD Nano 4x Settings

const byte modulesCount = 4; // Number of Modules
                             // Add baud rate for Serials - If Online

#endif

struct configuration
{
    bool useReferenceVoltage = true;        // "true" to use the 5v regulator as the reference voltage or "false" to use the 1.1V internal voltage reference
    int referenceVoltage = 4980;            // 5V output of Arduino
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

    int shuntResistor[modulesCount] = {3330, 3330, 3380, 3370};
    int chargeLedPinMidVoltage[modulesCount] = {2040, 2090, 2150, 2090}; // Array for each Mid On / Off Voltage of the TP5100 Charge LED Pins
    uint8_t dallasSerials[modulesCount + 1][8] =
        {{0x28, 0xE3, 0x11, 0x79, 0xA2, 0x01, 0x03, 0x7B},
         {0x28, 0x84, 0x35, 0x79, 0xA2, 0x01, 0x03, 0xDA},
         {0x28, 0xCF, 0x41, 0x79, 0xA2, 0x01, 0x03, 0x25},
         {0x28, 0xA4, 0x8A, 0x79, 0xA2, 0x00, 0x03, 0x88},
         {0x28, 0xB9, 0x84, 0x79, 0xA2, 0x00, 0x03, 0x3B}};
};

static configuration config;

#endif

#endif