#include <Config.h>

#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))

// ASCD_NANO_4X and ASCD_MEGA_8X - Config Settings
bool Config::useReferenceVoltage = true;        // "true" to use the 5v regulator as the reference voltage or "false" to use the 1.1V internal voltage reference
int Config::referenceVoltage = 4980;            // 5V output of Arduino
int Config::internalReferenceVoltage = 1054;    // 1.1V internal voltage reference of Arduino
int Config::defaultBatteryCutOffVoltage = 2800; // Voltage that the discharge stops
int Config::storageChargeVoltage = 3800;        // Storage charge voltage for recharge cycle. Use 0.00 for no storage charge. Can't be greater than 3.80v
int Config::batteryVoltageLeak = 500;           // On the initial screen "BATTERY CHECK" observe the highest voltage of each module and set this value slightly higher
int Config::lowMilliAmps = 1000;                // This is the value of Milli Amps that is considered low and does not get recharged because it is considered faulty
int Config::highMilliOhms = 500;                // This is the value of Milli Ohms that is considered high and the battery is considered faulty
int Config::offsetMilliOhms = 0;                // Offset calibration for MilliOhms
byte Config::restTimeMinutes = 0;               // The time in Minutes to rest the battery after charge. 0-59 are valid
byte Config::chargingTimeout = 8;               // The timeout in Hours for charging
byte Config::tempThreshold = 7;                 // Warning Threshold in degrees above initial Temperature
byte Config::tempMaxThreshold = 10;             // Maximum Threshold in degrees above initial Temperature - Considered Faulty
bool Config::rechargeCycle = true;              // Run the Recharge Cycle "true" to run and "false" to skip to Completed Cycle
byte Config::screenTime = 4;                    // Time in Seconds (Cycles) per Active Screen
int Config::shuntResistor[MODULES_COUNT] = {3330, 3330, 3380, 3370};
int Config::chargeLedPinMidVoltage[MODULES_COUNT] = {2040, 2090, 2150, 2090}; // Array for each Mid On / Off Voltage of the TP5100 Charge LED Pins
uint8_t Config::dallasSerials[MODULES_COUNT + 1][8] =
    {{0x28, 0xE3, 0x11, 0x79, 0xA2, 0x01, 0x03, 0x7B},
     {0x28, 0x84, 0x35, 0x79, 0xA2, 0x01, 0x03, 0xDA},
     {0x28, 0xCF, 0x41, 0x79, 0xA2, 0x01, 0x03, 0x25},
     {0x28, 0xA4, 0x8A, 0x79, 0xA2, 0x00, 0x03, 0x88},
     {0x28, 0xB9, 0x84, 0x79, 0xA2, 0x00, 0x03, 0x3B}};

#elif defined(ASCD_WIFI_CLIENT)

// ASCD_WIFI_CLIENT - Config Settings
char Config::ssid[33] = "FLL-RTR-02";              // SSID
char Config::password[33] = "@passw0rd1";          // Password
char Config::server[50] = "submit.vortexit.co.nz"; // Server to connect to send and receive data
char Config::userHash[9] = "c4ca4238";             // Database Hash - this is unique per user - Get this from Charger / Discharger Menu -> View
int Config::CDUnitID = 264;                        // CDUnitID this is the Units ID - this is unique per user - Get this from Charger / Discharger Menu -> View -> Select your Charger / Discharger


#elif defined(ASCD_WIFI_CLIENT_WEB)

// ASCD_WIFI_CLIENT - Config Settings
char Config::ssid[33] = "Taihoro";              // SSID
char Config::password[33] = "future-orient3d";          // Password
char Config::server[50] = "submit.vortexit.co.nz"; // Server to connect to send and receive data
char Config::userHash[9] = "c4ca4238";             // Database Hash - this is unique per user - Get this from Charger / Discharger Menu -> View
int Config::CDUnitID = 264;                        // CDUnitID this is the Units ID - this is unique per user - Get this from Charger / Discharger Menu -> View -> Select your Charger / Discharger

#endif

Config::Config()
{
}