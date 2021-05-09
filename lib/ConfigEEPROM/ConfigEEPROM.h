#ifndef VARIABLES_EEPROM_H
#define VARIABLES_EEPROM_H

#include <Config.h>
#include <Arduino.h>

class ConfigEEPROM
{
private:
    byte tempDefaultValueEEPROM;

    // Private Class Functions
    Config config;

    int getPutEEPROM(byte inputPointer, bool runAll, bool getEEPROM, bool addressSizeEEPROM);
    

public:
    // Public Class Functions
    ConfigEEPROM();
    void init();

    bool checkEEPROMEmpty();

    // #0
    void setDefaultValueEEPROM();
    void getDefaultValueEEPROM();
    // #1
    void setDefaultBatteryCutOffVoltage();
    void getDefaultBatteryCutOffVoltage();
    // #2
    void setStorageChargeVoltage();
    void getStorageChargeVoltage();
    // #3
    void setBatteryVoltageLeak();
    void getBatteryVoltageLeak();
    // #4
    void setLowMilliAmps();
    void getLowMilliAmps();
    // #5
    void setHighMilliOhms();
    void getHighMilliOhms();
    // #6
    void setOffsetMilliOhms();
    void getOffsetMilliOhms();
    // #7
    void setRestTimeMinutes();
    void getRestTimeMinutes();
    // #8
    void setChargingTimeout();
    void getChargingTimeout();
    // #9
    void setTempThreshold();
    void getTempThreshold();
    // #10
    void setTempMaxThreshold();
    void getTempMaxThreshold();
    // #11
    void setRechargeCycle();
    void getRechargeCycle();
    // #12
    void setScreenTime();
    void getScreenTime();
    // #13
    void setShuntResistor();
    void getShuntResistor();
    // #14
    void setDallasSerials();
    void getDallasSerials();

#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    // #15
    void setUseReferenceVoltage();
    void getUseReferenceVoltage();
    // #16
    void setReferenceVoltage();
    void getReferenceVoltage();
    // #17
    void setInternalReferenceVoltage();
    void getInternalReferenceVoltage();
#if defined(ASCD_NANO_4X)
    // #18
    void setChargeLedPinMidVoltage();
    void getChargeLedPinMidVoltage();
#endif
#endif
};
#endif
