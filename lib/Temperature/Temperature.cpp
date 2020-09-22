#include <Temperature.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Variables.h>

#define TEMPERATURE_PRECISION 9

#if defined(ASCD_MEGA_8X)
#if defined(MEGA_1X)
#define ONE_WIRE_BUS 2 // Pin 2 Temperature Sensors - ASCD MEGA PCB Version 1.1
#elif defined(MEGA_2X)
#define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors - ASCD MEGA PCB Version 2.0+
#endif
#elif defined(ASCD_NANO_4X)
#define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors - ASCD NANO All Versions
#endif

OneWire oneWire(ONE_WIRE_BUS);       // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

DeviceAddress tempSensorSerial[modulesCount + 1] =
    {{0x28, 0xD5, 0x73, 0x79, 0xA2, 0x00, 0x03, 0x72},
     {0x28, 0x46, 0xF9, 0x79, 0xA2, 0x01, 0x03, 0x28},
     {0x28, 0xB2, 0x23, 0x79, 0xA2, 0x01, 0x03, 0x65},
     {0x28, 0x5F, 0xED, 0x79, 0xA2, 0x01, 0x03, 0x86},
     {0x28, 0xAB, 0xF7, 0x79, 0xA2, 0x00, 0x03, 0x2D}};

Temperature::Temperature()
{
}

void Temperature::init()
{
    sensors.begin(); // Start up the library Dallas Temperature IC Control
}

byte Temperature::processTemperature(byte module)
{
    getTemperature(module, false);
    if (batteryCurrentTemp[module] > batteryHighestTemp[module] && batteryCurrentTemp[module] != 99)
        batteryHighestTemp[module] = batteryCurrentTemp[module]; // Set highest temperature if current value is higher
    if ((batteryCurrentTemp[module] - batteryCurrentTemp[modulesCount]) > tempThreshold && batteryCurrentTemp[module] != 99 && batteryCurrentTemp[module] != 0)
    {
        if ((batteryCurrentTemp[module] - batteryCurrentTemp[modulesCount]) > tempMaxThreshold) // batteryCurrentTemp[modulesCount] is the ambient temp sensor
        {
            //Temp higher than Maximum Threshold
            return 2;
        }
        else
        {
            //Temp higher than Threshold <- Does nothing yet need some flag / warning
            return 1;
        }
    }
    else
    {
        //Temp lower than Threshold
        return 0;
    }
}

void Temperature::getTemperature(byte module, boolean tempNow)
{
    if (tempCount[module] > 16 || batteryCurrentTemp[module] == 0 || batteryCurrentTemp[module] == 99 || tempNow) // Read every 16x cycles or if tempNow = true
    {
        tempCount[module] = 0;
        sensors.requestTemperaturesByAddress(tempSensorSerial[module]);
        float tempC = sensors.getTempC(tempSensorSerial[module]);
        if (tempC > 99 || tempC < 0)
        {
            tempC = 99;
            if (batteryCurrentTemp[module] != 99)
                tempC = batteryCurrentTemp[module];
        }
        batteryCurrentTemp[module] = (int)tempC + temperatureOffset[module];
    }
    else
    {
        tempCount[module]++;
    }
}

byte Temperature::getAmbientTemperature()
{
    getTemperature(modulesCount, false); // modulesCount is the ambient temp sensor array pointer. 0-3 / 0-7 are the modules pointers and 4 or 8 is the 5th or 8th temp sensor
    return batteryCurrentTemp[modulesCount];
}

byte Temperature::getCurrentTemp(byte module)
{
    return batteryCurrentTemp[module];
}

byte Temperature::getInitialTemp(byte module)
{
    return batteryInitialTemp[module];
}

byte Temperature::getHighestTemp(byte module)
{
    return batteryHighestTemp[module];
}

void Temperature::setInitialTemp(byte module)
{
    getTemperature(module, true);
    batteryInitialTemp[module] = batteryCurrentTemp[module];
}

void Temperature::clearHighestTemp(byte module)
{
    batteryHighestTemp[module] = 0;
}