#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#if defined(ASCD_MEGA_8X)
#define MODULES_COUNT 8 // Number of Modules
// Add baud rate for Serials - If Online
#elif defined(ASCD_NANO_4X)
#define MODULES_COUNT 4 // Number of Modules
// Add baud rate for Serials - If Online
#endif

class Config
{
private:
public:
    // Public Class Functions
    Config();
    // Public Variables
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))

    // ASCD_NANO_4X and ASCD_MEGA_8X - Config Settings
    static bool useReferenceVoltage;
    static int referenceVoltage;
    static int internalReferenceVoltage;
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
    static int chargeLedPinMidVoltage[MODULES_COUNT];
    static uint8_t dallasSerials[MODULES_COUNT + 1][8];

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
