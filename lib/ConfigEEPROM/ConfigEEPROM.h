#ifndef VARIABLES_EEPROM_H
#define VARIABLES_EEPROM_H

// #include "Config.h"

#include <Arduino.h>

class ConfigEEPROM
{
private:
    byte addressEEPROM = 0;
 
    // Variables variables;
public:
    // Public Class Functions
    ConfigEEPROM();
    void init();
    void writeConfigEEPROM();
    void readConfigEEPROM();
    void clearEEPROM();
    bool checkEEPROMEmpty();
};

#endif
