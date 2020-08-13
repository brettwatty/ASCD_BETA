#include <TemperatureControl.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TempSensorSerials.h>

TemperatureControl::TemperatureControl()
{
    init();
}

void TemperatureControl::init()
{
    #if defined(ASCD_MEGA_8X)
        //#define ONE_WIRE_BUS 2 // Pin 2 Temperature Sensors - PCB Version 1.1
        #define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors - PCB Version 2.+
    #elif defined(ASCD_NANO_4X)
        #define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors
    #endif
    OneWire oneWire(ONE_WIRE_BUS);       // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
    DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
    sensors.begin();                     // Move to new OOP class
}