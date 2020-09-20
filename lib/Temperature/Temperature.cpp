#include <Temperature.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Variables.h>

#define TEMPERATURE_PRECISION 9
#define ONE_WIRE_BUS 4               // Pin 4 Temperature Sensors
OneWire oneWire(ONE_WIRE_BUS);       // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

DeviceAddress tempSensorSerial[modulesCount + 1] =
    {{0x28, 0xE3, 0x11, 0x79, 0xA2, 0x01, 0x03, 0x7B},
     {0x28, 0x84, 0x35, 0x79, 0xA2, 0x01, 0x03, 0xDA},
     {0x28, 0xCF, 0x41, 0x79, 0xA2, 0x01, 0x03, 0x25},
     {0x28, 0xA4, 0x8A, 0x79, 0xA2, 0x00, 0x03, 0x88},
     {0x28, 0xB9, 0x84, 0x79, 0xA2, 0x00, 0x03, 0x3B}};
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
    if (tempCount[module] > 16 || batteryCurrentTemp[module] == 0 || batteryCurrentTemp[module] == 99 || tempNow) // Read every 16x cycles
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
        batteryCurrentTemp[module] = (int)tempC;
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