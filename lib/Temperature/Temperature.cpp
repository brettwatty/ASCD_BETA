#include <Temperature.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(ONE_WIRE_BUS);                         // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire);                   // Pass our oneWire reference to Dallas Temperature.
DeviceAddress tempSensorSerial[TEMP_SENSENSORS_COUNT]; // Array Object to hold device addresses

Temperature::Temperature()
{
}

void Temperature::init()
{
    memcpy(tempSensorSerial, config.dallasSerials, sizeof(tempSensorSerial));
    sensors.begin(); // Start up the library Dallas Temperature IC Control
}

byte Temperature::processTemperature(byte module)
{

    getTemperature(module, false);
#if defined(AMBIENT_TEMP_SENSOR)
    if (batteryCurrentTemp[module] > batteryHighestTemp[module] && batteryCurrentTemp[module] != 99)
        batteryHighestTemp[module] = batteryCurrentTemp[module]; // Set highest temperature if current value is higher
    if ((batteryCurrentTemp[module] - batteryCurrentTemp[MODULES_COUNT]) > config.tempThreshold && batteryCurrentTemp[module] != 99 && batteryCurrentTemp[module] != 0)
    {
        if ((batteryCurrentTemp[module] - batteryCurrentTemp[MODULES_COUNT]) > config.tempMaxThreshold) // batteryCurrentTemp[MODULES_COUNT] is the ambient temp sensor
        {
            //Temp higher than Maximum Threshold
            return 2;
        }
        else
        {
            //Temp higher than Threshold 
            return 1;
        }
    }
    else
    {
        //Temp lower than Threshold
        return 0;
    }
#else
    if (batteryCurrentTemp[module] > batteryHighestTemp[module] && batteryCurrentTemp[module] != 99)
        batteryHighestTemp[module] = batteryCurrentTemp[module]; // Set highest temperature if current value is higher

    if ((batteryCurrentTemp[module] - batteryInitialTemp[module]) > config.tempThreshold && batteryCurrentTemp[module] != 99 && batteryCurrentTemp[module] != 0)
    {
        if ((batteryCurrentTemp[module] - batteryInitialTemp[module]) > config.tempMaxThreshold) // No ambient temp sensor. Using Initial Temp for comparison.
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
#endif
}

void Temperature::getTemperature(byte module, bool tempNow)
{
    if (tempCount[module] == 15 || batteryCurrentTemp[module] == 0 || batteryCurrentTemp[module] == 99 || tempNow) // Read every 16x cycles or if tempNow = true
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

#if defined(AMBIENT_TEMP_SENSOR)
byte Temperature::getAmbientTemperature()
{
    getTemperature(MODULES_COUNT, false); // MODULES_COUNT is the ambient temp sensor array pointer. 0-3 / 0-7 are the modules pointers and 4 or 8 is the 5th or 9th temp sensor
    return batteryCurrentTemp[MODULES_COUNT];
}
#endif

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