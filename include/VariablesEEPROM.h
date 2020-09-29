#ifndef VARIABLES_EEPROM_H
#define VARIABLES_EEPROM_H

#include "Config.h"

#include <Arduino.h>

class VariablesEEPROM
{
private:
    int addressEEPROM = 0;
    // bool testOutput1;
    // float testOutput2;
    // float testOutput3;
    // float testOutput4;
    // float testOutput5;
    // float testOutput6;
    // int testOutput7;
    // int testOutput8;
    // int testOutput9;
    // byte testOutput10;
    // byte testOutput11;
    // byte testOutput12;
    // byte testOutput13;
    // bool testOutput14;

    // Variables variables;
public:
    // Public Class Functions
    VariablesEEPROM();
    void init();
    void writeEEPROMTest();
    void readEEPROMTest();
    void clearEEPROMTest();
};

#endif
