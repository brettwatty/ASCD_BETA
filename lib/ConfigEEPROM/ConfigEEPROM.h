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
    void writeCustomConfigEEPROM();
    void loadConfigEEPROM();
    void clearEEPROM(); // Clears all EEPROM
    void clearCustomEEPROM(); // Clears all manual Config Variables 
    void checkEEPROMEmpty();
    bool getEEPROMEmpty();
    void setAddressSize();
};
#endif
