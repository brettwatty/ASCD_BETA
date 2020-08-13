#include <Arduino.h>


typedef struct
{
  // Pin Definitions
  const uint8_t batteryVolatgePin;
  const uint8_t batteryVolatgeDropPin;
  const uint8_t chargeLedPin;
  const uint8_t chargeMosfetPin;
  const uint8_t dischargeMosfetPin;

  // Timmer
  unsigned long longMilliSecondsCleared;
  byte seconds;
  byte minutes;
  byte hours;

  // Module Cycle
  byte cycleCount;
  bool batteryBarcode;
  bool insertData;
  byte cycleState;
  byte batteryFaultCode;

  // Voltage Readings
  float batteryInitialVoltage;
  float batteryVoltage;
  float batteryLastVoltage;

  // Temp Readings an Variables
  byte batteryInitialTemp;
  byte batteryHighestTemp;
  byte batteryCurrentTemp;
  byte tempCount;

  // Milli Ohms
  float tempMilliOhmsValue;
  float milliOhmsValue;

  // Discharge Battery
  int intMilliSecondsCount;
  unsigned long longMilliSecondsPreviousCount;
  unsigned long longMilliSecondsPrevious;
  unsigned long longMilliSecondsPassed;
  float dischargeMilliamps;
  float dischargeVoltage;
  float dischargeAmps;
  bool dischargeCompleted;
  int dischargeMinutes;
  bool pendingDischargeRecord;
} Modules;

Modules module[8] =
    {
        {A0, A1, 23, 22, 24},
        {A2, A3, 26, 25, 27},
        {A4, A5, 29, 28, 30},
        {A6, A7, 32, 31, 33},
        {A8, A9, 35, 34, 36},
        {A10, A11, 38, 37, 39},
        {A12, A13, 41, 40, 42},
        {A14, A15, 44, 43, 45}};

typedef struct
{
  const float shuntResistor[8] = {3.3, 3.3, 3.3, 3.3, 3.3, 3.3, 3.3, 3.3};
  const bool useReferenceVoltage = true;         // "true" to use the 5v regulator as the refenence voltage or "false" to use the 1.1V internal voltage reference
  const float referenceVoltage = 5.00;           // 5V output of Arduino
  const float internalReferenceVoltage = 1.1;    // 1.1V internal voltage reference of Arduino
  const float defaultBatteryCutOffVoltage = 2.8; // Voltage that the discharge stops
  const byte restTimeMinutes = 1;                // The time in Minutes to rest the battery after charge. 0-59 are valid
  const int lowMilliamps = 1000;                 // This is the value of Milli Amps that is considered low and does not get recharged because it is considered faulty
  const int highMilliOhms = 500;                 // This is the value of Milli Ohms that is considered high and the battery is considered faulty
  const int offsetMilliOhms = 0;                 // Offset calibration for MilliOhms
  const byte chargingTimeout = 8;                // The timeout in Hours for charging
  const byte tempThreshold = 7;                  // Warning Threshold in degrees above initial Temperature
  const byte tempMaxThreshold = 10;              // Maximum Threshold in degrees above initial Temperature - Considered Faulty
  const float batteryVolatgeLeak = 2.00;         // On the initial screen "BATTERY CHECK" observe the highest voltage of each module and set this value slightly higher
  const byte modules = 8;                        // Number of Modules
  const byte screenTime = 4;                     // Time in Seconds (Cycles) per Active Screen
  const int dischargeReadInterval = 5000;        // Time intervals between Discharge readings. Adjust for mAh +/-
  const bool rechargeCycle = true;               // Run the Recharge Cycle "true" to run and "false" to skip to Completed Cycle
} CustomSettings;

CustomSettings settings;



int ambientTemperature = 0;
boolean buttonPressed = false;
boolean readSerialResponse = false;
char serialSendString[2048];
byte countSerialSend = 0;

// Cycle Variables

byte cycleStateLast = 0;
byte rotaryOverride = 0;
boolean rotaryOverrideLock = 0;
boolean buttonState = 0;
boolean lastButtonState = 0;