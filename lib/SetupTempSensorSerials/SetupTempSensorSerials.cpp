#include <SetupTempSensorSerials.h>

// #define TEMPERATURE_PRECISION 9
#if defined(ASCD_MEGA_8X)
#if defined(MEGA_1X)
#define ONE_WIRE_BUS 2 // Pin 2 Temperature Sensors - ASCD MEGA PCB Version 1.1
#elif defined(MEGA_2X)
#define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors - ASCD MEGA PCB Version 2.0+
#endif
#elif defined(ASCD_NANO_4X)
#define ONE_WIRE_BUS 4 // Pin 4 Temperature Sensors - ASCD NANO All Versions
#elif defined(ASCD_LEONARDO_4X)
#define ONE_WIRE_BUS 12 // Pin 12 Temperature Sensors - ASCD LEONARDO 4X
#endif

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Array Object to hold device addresses
DeviceAddress tempSensorSerial[TEMP_SENSENSORS_COUNT];

SetupTempSensorSerials::SetupTempSensorSerials()
{
}

void SetupTempSensorSerials::init()
{
    writeOutput.init();
    delay(500);
    for (byte module = 0; module < MODULES_COUNT; module++)
    {
        writeOutput.chargeMosfetOff(module);    // Turn off the Charge Mosfet
        writeOutput.dischargeMosfetOff(module); // Turn off the Discharge Mosfet
    }
    delay(500);
    Serial.begin(BAUD_RATE);
    #if defined(ASCD_LEONARDO_4X)
    while (!Serial)
    {
        // do nothing
    };
    #endif
    configEEPROM.init();
    Serial.println();
    Serial.println(F("---------------------------------------------------------------------------------------------------"));
    Serial.println(F("ASCD Setup: Temperature Sensors Serial Detection"));
    sensors.begin();

    for (byte i = 0; i < TEMP_SENSENSORS_COUNT; i++)
    {
        Serial.print("Config Module: ");
        Serial.print(i);
        Serial.print(" ");
        printTempSensorSerial(config.dallasSerials[i], false, false, false);
        Serial.println();
    }
    run();
}

void SetupTempSensorSerials::run()
{
    getTempSensorCount();
    if (foundTempSensorsCount < TEMP_SENSENSORS_COUNT)
    {
        Serial.println(F("---------------------------------------------------------------------------------------------------"));
        Serial.print(F("ERROR: Did no detect all the Sensors "));
        Serial.print(foundTempSensorsCount);
        Serial.print(F(" found "));
        Serial.print(TEMP_SENSENSORS_COUNT);
        Serial.println(F(" sensors should exist"));
        Serial.println(F("---------------------------------------------------------------------------------------------------"));
        while (1)
            ;
    }
    else
    {
        getTempSensorSerials();
        if (foundTempSensorsCount < TEMP_SENSENSORS_COUNT)
        {
            Serial.print(F("ERROR: Did no detect all the Sensor Serials "));
            Serial.print(foundTempSensorsCount);
            Serial.print(F(" found "));
            Serial.print(TEMP_SENSENSORS_COUNT);
            Serial.println(F(" sensors should exist"));
            Serial.println(F("---------------------------------------------------------------------------------------------------"));
            while (1)
                ;
        }
        else
        {
            getTempSensorAverageTemp();
        }
    }
}

void SetupTempSensorSerials::getTempSensorCount()
{
    foundTempSensorsCount = sensors.getDeviceCount();
    Serial.println(F("---------------------------------------------------------------------------------------------------"));
    Serial.print(F("Searching for sensors... "));
    Serial.print(F("Found "));
    Serial.print(foundTempSensorsCount);
    Serial.println(F(" Sensors"));
}

void SetupTempSensorSerials::getTempSensorSerials()
{
    foundTempSensorsCount = 0;
    Serial.println(F("---------------------------------------------------------------------------------------------------"));
    Serial.println(F("Searching for Temperature Sensor Serials..."));
    Serial.println();
    if (oneWire.search(tempSensorSerial[foundTempSensorsCount]))
    {
        do
        {
            delay(100);
            Serial.print(F("Sensor "));
            Serial.print(foundTempSensorsCount);
            Serial.print(F(" Serial: "));
            printTempSensorSerial(tempSensorSerial[foundTempSensorsCount], false, false, false);
            Serial.println();
            foundTempSensorsCount++;
        } while (oneWire.search(tempSensorSerial[foundTempSensorsCount]));
    }
    Serial.println(F("---------------------------------------------------------------------------------------------------"));
}

void SetupTempSensorSerials::getTempSensorAverageTemp()
{
    Serial.println(F("Getting Average Temperature..."));
    Serial.println();
    sensors.requestTemperatures();
    for (byte i = 0; i < TEMP_SENSENSORS_COUNT; i++)
    {
        sensorTemp = sensors.getTempC(tempSensorSerial[i]);
        Serial.print(F("Sensor "));
        Serial.print(i);
        Serial.print(F(" Temperature: "));
        Serial.println(sensorTemp);
        tempSensorAverageTemp += sensorTemp;
    }
    tempSensorAverageTemp = tempSensorAverageTemp / (TEMP_SENSENSORS_COUNT);
    Serial.println();
    Serial.print(F("Average Temperature: "));
    Serial.println(tempSensorAverageTemp);
    Serial.println();
}

void SetupTempSensorSerials::getTempSensorModule()
{
    if (detectionComplete == false)
    {
        Serial.print(F("-------------------------------------"));
        Serial.print("Heat Up Battery Sensor: ");
        Serial.print(pendingDetection + 1);
        Serial.println(F("-------------------------------------"));
        sensors.requestTemperatures();
        for (byte i = 0; i < TEMP_SENSENSORS_COUNT; i++)
        {
            if (tempSensorSerialCompleted[i] == false)
            {
                if (pendingDetection != ((TEMP_SENSENSORS_COUNT)-1))
                {
                    sensorTemp = sensors.getTempC(tempSensorSerial[i]);
                    Serial.print(F("Sensor "));
                    Serial.print(i);
                    Serial.print(F(" Temperature: "));
                    Serial.println(sensorTemp);
                    if (sensorTemp > (tempSensorAverageTemp + 2.5))
                    {
                        Serial.print(F("Detected Battery: "));
                        Serial.println(pendingDetection + 1);
                        tempSensorSerialCompleted[i] = true;
                        tempSensorSerialOutput[pendingDetection] = i;
                        pendingDetection++; // if not greater than number of devices - last one = ambient
                    }
                }
                else
                {
                    Serial.println();
                    Serial.println();
                    Serial.println();
                    Serial.println();
                    Serial.print(F("---------------------------------"));
                    Serial.print(F("Detected Last Sensor Completed"));
                    Serial.println(F("---------------------------------"));
                    tempSensorSerialCompleted[i] = true;
                    // Got the last one, we are done
                    tempSensorSerialOutput[pendingDetection] = i;
                    detectionComplete = true;
                }
            }
        }
        delay(4000);
    }
    else
    {
        // else show serials
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println(F("---------------------------------------------------------------------------------------------------"));
        for (byte i = 0; i < TEMP_SENSENSORS_COUNT; i++)
        {
            if (i == 0)
            {
                printTempSensorSerial(tempSensorSerial[tempSensorSerialOutput[i]], true, false, true);
            }
            else if (i == (TEMP_SENSENSORS_COUNT - 1))
            {
                printTempSensorSerial(tempSensorSerial[tempSensorSerialOutput[i]], false, true, false);
            }
            else
            {
                printTempSensorSerial(tempSensorSerial[tempSensorSerialOutput[i]], false, false, true);
            }
        }

        // Write Sensor Serials to EEPROM
        for (byte i = 0; i < TEMP_SENSENSORS_COUNT; i++)
        {
            // Copy to config.dallasSerials -> Config.h
            memcpy(config.dallasSerials[i], tempSensorSerial[tempSensorSerialOutput[i]], 8);
        }
        if(configEEPROM.checkEEPROMEmpty()){
            configEEPROM.init();
        }
        configEEPROM.setDallasSerials();

        Serial.println(F("---------------------------------------------------------------------------------------------------"));
        Serial.println(F("Temperature Sensor Serials Saved to EEPROM"));
        Serial.println(F("---------------------------------------------------------------------------------------------------"));
        while (1)
            ;
    }
}

void SetupTempSensorSerials::printTempSensorSerial(DeviceAddress deviceAddress, bool first, bool last, bool comma)
{
    if (first)
    {
        Serial.println(F("uint8_t Config::dallasSerials[TEMP_SENSENSORS_COUNT][8] = "));
        Serial.print(F("{{"));
    }
    else
    {
        Serial.print(F("{"));
    }
    for (byte i = 0; i < 8; i++)
    {
        Serial.print(F("0x"));
        if (deviceAddress[i] < 0x10)
            Serial.print(F("0"));
        Serial.print(deviceAddress[i], HEX);
        if (i < 7)
            Serial.print(F(", "));
    }
    if (last)
    {
        Serial.println(F("}};"));
    }
    else
    {
        if (comma)
        {
            Serial.println(F("},"));
        }
        else
        {
            Serial.print(F("}"));
        }
    }
}