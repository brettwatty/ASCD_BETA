#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#if defined(ASCD_MEGA_8X)
#define MODULES_COUNT 8 // Number of Modules
#define TEMP_SENSENSORS_COUNT 9
#define AMBIENT_TEMP_SENSOR
#if defined(MEGA_1X)
#define ONE_WIRE_BUS 2 // Pin 2 Temperature Sensors - ASCD MEGA PCB Version 1.1
#elif defined(MEGA_2X)
#define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors - ASCD MEGA PCB Version 2.0+
#endif
#elif defined(ASCD_NANO_4X)
#define MODULES_COUNT 4 // Number of Modules
#define TEMP_SENSENSORS_COUNT 5
#define AMBIENT_TEMP_SENSOR
#define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors - ASCD NANO All Versions
#elif defined(ASCD_LEONARDO_4X)
#define MODULES_COUNT 4 // Number of Modules
#define TEMP_SENSENSORS_COUNT 4
#define ONE_WIRE_BUS 12 // Pin 12 Temperature Sensors - ASCD LEONARDO 4X
#endif

class Config
{
private:
public:
    // Public Class Functions
    Config();
    // Public Variables
#if (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X) || defined(ASCD_MEGA_8X))

// ASCD_NANO_4X, ASCD_LEONARDO_4X and ASCD_MEGA_8X - Config Settings
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    static bool useReferenceVoltage;
    static int referenceVoltage;
    static int internalReferenceVoltage;
#endif
    static int defaultBatteryCutOffVoltage;
    static int storageChargeVoltage;
    static int batteryVoltageLeak;
    static int lowMilliAmps;
    static int highMilliOhms;
    static int offsetMilliOhms;
    static byte restTimeMinutes;
    static byte chargingTimeout;
    static byte tempThreshold;
    static byte tempMaxThreshold;
    static bool rechargeCycle;
    static byte screenTime;
    static int shuntResistor[MODULES_COUNT];
#if defined(ASCD_NANO_4X)
    static int chargeLedPinMidVoltage[MODULES_COUNT];
#endif
    static uint8_t dallasSerials[TEMP_SENSENSORS_COUNT][8];

#elif defined(ASCD_WIFI_CLIENT)

    // ASCD_WIFI_CLIENT - Config Settings
    static char ssid[33];
    static char password[33];
    static char server[50];
    static char userHash[9];
    static int CDUnitID;

#elif defined(ASCD_WIFI_CLIENT_WEB)

    // ASCD_WIFI_CLIENT - Config Settings
    static char ssid[33];
    static char password[33];
    static char server[50];
    static char userHash[9];
    static int CDUnitID;

#endif
};

#endif
