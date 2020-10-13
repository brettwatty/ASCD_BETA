#include <Config.h>
#include <ConfigEEPROM.h>
#include <EEPROM.h>

ConfigEEPROM::ConfigEEPROM()
{
}

void ConfigEEPROM::init()
{
}

bool ConfigEEPROM::checkEEPROMEmpty()
{
    byte configSize = sizeof(config);
    byte countEmptyAddresses = 0;
    byte valueEEPROM;
    for (byte i = 0; i < configSize; i++)
    {
        valueEEPROM = EEPROM.read(i);
        if (valueEEPROM == 255)
        {
            countEmptyAddresses++;
        }
        // Serial.print("EEPROM Address: ");
        // Serial.print(i);
        // Serial.print(" Value DEC: ");
        // Serial.println(valueEEPROM);
    }
    if (configSize == countEmptyAddresses)
    {
        // EEPROM is EMPTY
        return true;
    }
    else
    {
        // EEPROM is NOT EMPTY
        return false;
    }
}

void ConfigEEPROM::writeConfigEEPROM()
{
    EEPROM.put(0, config);
}

void ConfigEEPROM::readConfigEEPROM()
{
    EEPROM.get(0, config);
}

void ConfigEEPROM::clearEEPROM()
{
    for (unsigned int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 255);
    }
}