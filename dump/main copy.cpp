// Setup - What Version Model you have, online or offline etc...
#define ASCD MEGA_8X // ASCD_MEGA_8X or ASCD_NANO_4X
// #define ASCD_NANO_4X // ASCD_MEGA_8X or ASCD_NANO_4X
#define ASCD_MODE_ONLINE  // ASCD_MODE_ONLINE or ASCD_MODE_OFFLINE

// Definitions
#define TEMPERATURE_PRECISION 9

// External Library
#include <Arduino.h>
#include <Wire.h> // Comes with Arduino IDE
// #include <OneWire.h>
// #include <DallasTemperature.h>
// #include <TempSensorSerials.h> // May need to move this later !!!!!!!!!!!!

// Tester Specific Library, Classes and Definitions
#ifdef ASCD_MEGA_8X
    // #define NUMBER_MODULES 8
    // Need rotary encoder library here
    // #define CLK 3 // Rotary Encoder PIN A CLK    - PCB Version 1.1
    // #define DT 4  // Rotary Encoder PIN B DT     - PCB Version 1.1
    #define CLK 6 // Rotary Encoder PIN A CLK       - PCB Version 2.+
    #define DT 7  // Rotary Encoder PIN B DT        - PCB Version 2.+
    //#define ONE_WIRE_BUS 2 // Pin 2 Temperature Sensors - PCB Version 1.1
    #define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors - PCB Version 2.+ 
    // encoder_begin(CLK, DT);     // Start the decoder encoder Pin A (CLK) = 3 encoder Pin B (DT) = 4 for Version 1.1 | Pin 7 (CLK) and Pin 6 (DT) for Version 2.+
#else
    // #define NUMBER_MODULES 4
    #define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors
    #ifdef ASCD_MODE_ONLINE 
        #include <SoftwareSerial.h>
        SoftwareSerial ESP8266(3, 2); // RX , TX
    #endif
#endif

// Class Initialisation
// OneWire oneWire(ONE_WIRE_BUS);       // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
// DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

// ASCD Program Includes
#include <InitialiseSetup.h>

initialiseSetup initialiseASCD;

void setup()
{
    initialiseASCD.init();
    //   Serial.begin(115200); //Initialize Serial
}

void loop()
{
    // delay(2000);
    // Serial.print("Charging Time Out: ");
    // Serial.println(settings.chargingTimeout);
}
