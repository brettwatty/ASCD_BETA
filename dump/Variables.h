#ifndef VARIABLES_H
#define VARIABLES_H
#include <Arduino.h>
#ifdef ASCD_MEGA_8X
    #define NUMBER_MODULES 8
#else
    #define NUMBER_MODULES 4
#endif
// ----------------------------------------------------------------------------------------------------------------------------------------------------------

class CustomSettings
{
private:
#ifdef ASCD_MEGA_8X
    // ASCD Mega 8x Settings
    const float shuntResistor[NUMBER_MODULES] = {3.3, 3.3, 3.3, 3.3, 3.3, 3.3, 3.3, 3.3};
#else
    // ASCD Nano 4x Settings
    const float shuntResistor[NUMBER_MODULES] = {3.3, 3.3, 3.3, 3.3};
    const float chargeLedPinMidVoltage[NUMBER_MODULES] = {2.04, 1.99, 2.08, 2.02}; // Array for each Mid On / Off Voltage of the TP5100 Charge LED Pins
    const byte pwmFanMinStart = 115;                                              // Minimum PWM value when the Fan will start spinning
#endif
    const byte modulesCount = NUMBER_MODULES;      // Number of Modules
    const bool useReferenceVoltage = true;         // "true" to use the 5v regulator as the reference voltage or "false" to use the 1.1V internal voltage reference
    const float referenceVoltage = 5.00;           // 5V output of Arduino
    const float internalReferenceVoltage = 1.1;    // 1.1V internal voltage reference of Arduino
    const float defaultBatteryCutOffVoltage = 2.8; // Voltage that the discharge stops
    const byte restTimeMinutes = 1;                // The time in Minutes to rest the battery after charge. 0-59 are valid
    const int lowMilliAmps = 1000;                 // This is the value of Milli Amps that is considered low and does not get recharged because it is considered faulty
    const int highMilliOhms = 500;                 // This is the value of Milli Ohms that is considered high and the battery is considered faulty
    const int offsetMilliOhms = 0;                 // Offset calibration for MilliOhms
    const byte chargingTimeout = 8;                // The timeout in Hours for charging
    const byte tempThreshold = 7;                  // Warning Threshold in degrees above initial Temperature
    const byte tempMaxThreshold = 10;              // Maximum Threshold in degrees above initial Temperature - Considered Faulty
    const float batteryVoltageLeak = 2.00;         // On the initial screen "BATTERY CHECK" observe the highest voltage of each module and set this value slightly higher
    const byte screenTime = 4;                     // Time in Seconds (Cycles) per Active Screen
    const int dischargeReadInterval = 5000;        // Time intervals between Discharge readings. Adjust for mAh +/-
    const bool rechargeCycle = true;               // Run the Recharge Cycle "true" to run and "false" to skip to Completed Cycle
    const float storageChargeVoltage = 3.80;       // Storage charge voltage for recharge cycle. Use 0.00 for no storage charge

public:
    CustomSettings();
    void init();

    bool getUseReferenceVoltage();
    float getReferenceVoltage();
    float getInternalReferenceVoltage();
    float getDefaultBatteryCutOffVoltage();
    byte getRestTimeMinutes();
    int getLowMilliAmps();
    int getHighMilliOhms();
    int getOffsetMilliOhms();
    byte getChargingTimeout();
    byte getTempThreshold();
    byte getTempMaxThreshold();
    float getBatteryVoltageLeak();
    byte getModulesCount();
    byte getScreenTime();
    int getDischargeReadInterval();
    bool getRechargeCycle();
    float getStorageChargeVoltage();
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
struct PinDefinitions
{
    #ifdef ASCD_MEGA_8X
        // Pin Definitions Mega
        const uint8_t batteryVoltagePin;
        const uint8_t batteryVoltageDropPin;
        const uint8_t chargeLedPin;
        const uint8_t chargeMosfetPin;
        const uint8_t dischargeMosfetPin;
    #else
        // Pin Definitions Nano
         bool batteryVoltagePin[4];
         bool batteryVoltageDropPin[4];
         bool chargeLedPin[4];
         byte chargeMosfetPin;
         byte dischargeMosfetPin;
    #endif
};


PinDefinitions pins[4] =
	{
		{{1, 1, 0, 1}, {1, 1, 1, 1}, {0, 1, 0, 1}, 0, 1},
		{{1, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 1}, 2, 3},
		{{1, 1, 1, 0}, {1, 0, 1, 1}, {0, 1, 1, 0}, 4, 5},
		{{1, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 1, 0}, 6, 7}};


class Modules
{

private:
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

public:
    Modules();
    void init();

    // byte getBatteryVoltagePin();
    // byte getBatteryVoltageDropPin();
    // byte getChargeLedPin();
    // byte getChargeMosfetPin();
    // byte getDischargeMosfetPin();

};


// ----------------------------------------------------------------------------------------------------------------------------------------------------------

class BoardVariables
{
private:
public:
    int ambientTemperature = 0;
    boolean buttonPressed = false;

    // Serial
    boolean readSerialResponse = false;
    char serialSendString[2048];
    byte countSerialSend = 0;

    // Cycle
    byte cycleStateLast = 0;

#ifdef ASCD_MEGA_8X

    // Rotary Encoder
    byte rotaryOverride = 0;
    boolean rotaryOverrideLock = 0;

    // Button
    const byte BTN = 5; // Button pin Digital 5

#else

    // ASCD Nano 4x Variables

    const byte latchPin = 7; // Latch pin (ST_CP) of 74HC595
    const byte clockPin = 8; // Clock pin (SH_CP) of 74HC595
    const byte dataPin = 6;  // Data in (DS) of 74HC595

    // Mux control pins
    const byte S0 = 12;
    const byte S1 = 11;
    const byte S2 = 10;
    const byte S3 = 9;

    const byte SIG = 14; // Mux in SIG pin Analog A0

    const byte BTN = 15; // Button pin Analog A1

    // Buzzer pin
    //const byte BUZZ = 5; // PCB Version 1.1
    const byte BUZZ = 16; // PCB Version 1.11

    // Fan pin 5 PWM Digital
    const byte FAN = 5; // PCB Version 1.11+ only

#endif

    // Button All
    boolean buttonState = 0;
    boolean lastButtonState = 0;
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------------
#endif