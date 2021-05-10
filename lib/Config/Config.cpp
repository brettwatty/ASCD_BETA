#include <Config.h>

#if (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X) || defined(ASCD_MEGA_8X))
byte Config::defaultValueEEPROM = 192;
// ASCD_NANO_4X, ASCD_MEGA_8X and ASCD_LEONARDO_4X - Config Settings
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
bool Config::useReferenceVoltage = true;     // "true" to use the 5v regulator as the reference voltage or "false" to use the 1.1V internal voltage reference
int Config::referenceVoltage = 4943;         // 5V output of Arduino
int Config::internalReferenceVoltage = 1054; // 1.1V internal voltage reference of Arduino
#endif
int Config::defaultBatteryCutOffVoltage = 2800; // Voltage that the discharge stops
int Config::storageChargeVoltage = 3800;        // Storage charge voltage for recharge cycle. Use 0.00 for no storage charge. Can't be greater than 3.80v
int Config::batteryVoltageLeak = 500;           // On the initial screen "BATTERY CHECK" observe the highest voltage of each module and set this value slightly higher
int Config::lowMilliAmps = 1000;                // This is the value of Milli Amps that is considered low and does not get recharged because it is considered faulty
int Config::highMilliOhms = 500;                // This is the value of Milli Ohms that is considered high and the battery is considered faulty
int Config::offsetMilliOhms = 85;               // Offset calibration for MilliOhms
byte Config::restTimeMinutes = 0;               // The time in Minutes to rest the battery after charge. 0-59 are valid
byte Config::chargingTimeout = 8;               // The timeout in Hours for charging
byte Config::tempThreshold = 5;                 // Warning Threshold in degrees above initial Temperature - Turns of the Fan for Leonardo
byte Config::tempMaxThreshold = 10;             // Maximum Threshold in degrees above initial Temperature - Considered Faulty
bool Config::rechargeCycle = true;              // Run the Recharge Cycle "true" to run and "false" to skip to Completed Cycle
byte Config::screenTime = 4;                    // Time in Seconds (Cycles) per Active Screen
int Config::shuntResistor[MODULES_COUNT] = {3310, 3330, 3300, 3390};
#if defined(ASCD_NANO_4X)
int Config::chargeLedPinMidVoltage[MODULES_COUNT] = {2310, 2420, 2440, 2390}; // Array for each Mid On / Off Voltage of the TP5100 Charge LED Pins
#endif

uint8_t Config::dallasSerials[TEMP_SENSENSORS_COUNT][8] =
    {{0x28, 0x41, 0x43, 0x79, 0x97, 0x05, 0x03, 0x8F},
     {0x28, 0xD5, 0x46, 0x79, 0x97, 0x04, 0x03, 0xF4},
     {0x28, 0xBE, 0x08, 0x79, 0x97, 0x05, 0x03, 0x40},
     {0x28, 0x3F, 0x95, 0x79, 0x97, 0x04, 0x03, 0x02},
     {0x28, 0x05, 0xCE, 0x79, 0x97, 0x04, 0x03, 0xC5}};

#elif defined(ASCD_WIFI_CLIENT)

// ASCD_WIFI_CLIENT - Config Settings
char Config::ssid[33] = ""                          // SSID
char Config::password[33] = "";                     // Password
char Config::server[50] = "submit.vortexit.co.nz";  // Server to connect to send and receive data
char Config::userHash[9] = "";                      // Database Hash - this is unique per user - Get this from Charger / Discharger Menu -> View
int Config::CDUnitID = 0;                           // CDUnitID this is the Units ID - this is unique per user - Get this from Charger / Discharger Menu -> View -> Select your Charger / Discharger

#elif defined(ASCD_WIFI_CLIENT_WEB)

// ASCD_WIFI_CLIENT - Config Settings
char Config::ssid[33] = "";                        // SSID
char Config::password[33] = "";                    // Password
char Config::server[50] = "submit.vortexit.co.nz"; // Server to connect to send and receive data
char Config::userHash[9] = "";                     // Database Hash - this is unique per user - Get this from Charger / Discharger Menu -> View
int Config::CDUnitID = 0;                          // CDUnitID this is the Units ID - this is unique per user - Get this from Charger / Discharger Menu -> View -> Select your Charger / Discharger

#endif

Config::Config()
{
}