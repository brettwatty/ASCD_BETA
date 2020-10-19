#ifndef VARIABLES_EEPROM_H
#define VARIABLES_EEPROM_H

#include <Config.h>
#include <Arduino.h>

class ConfigEEPROM
{
private:
    bool emptyEEPROM;
    byte addressEEPROM = 0;
    byte addressCountEEPROM = 0;

    // Private Class Functions
    Config config;

public:
    // Public Class Functions
    ConfigEEPROM();
    void init();
    void writeConfigEEPROM();
    void loadConfigEEPROM();
    void clearEEPROM();
    void checkEEPROMEmpty();
    bool getEEPROMEmpty();
    void setAddressSize();
};
#endif
