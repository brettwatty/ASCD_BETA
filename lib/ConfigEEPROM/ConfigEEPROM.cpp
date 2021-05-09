#include <ConfigEEPROM.h>
#include <EEPROM.h>

ConfigEEPROM::ConfigEEPROM()
{
}

void ConfigEEPROM::init()
{
    // EEPROM.write(0, 255); // Writes Address 0 = 255 to notify code that EEPROM is empty - Use to clear EEPROM
    Serial.println(F("--------------------------------------------------------"));
    if (checkEEPROMEmpty() == false)
    {
        Serial.println(F("Config Loaded from EEPROM"));
        getPutEEPROM(0, true, true, false);
    }
    else
    {
        Serial.println(F("EEPROM Empty - Using values from Config.h"));
        getPutEEPROM(0, true, false, false);
    }
    Serial.println(F("--------------------------------------------------------"));
}

bool ConfigEEPROM::checkEEPROMEmpty()
{
    getPutEEPROM(0, false, true, false);
    if (tempDefaultValueEEPROM != config.defaultValueEEPROM) // Get defaultValueEEPROM from EEPROM
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

// Multiple return Function getPutEEPROM
// -------------------------------------
// inputPointer - is a reference for each Config variable e.g. getPutEEPROM(10, false, true, false); - gets addressEEPROM (tempMaxThreshold) copies to config.tempMaxThreshold
// runAll - will execute all inputPointers if TRUE. Set False for single inputPointer
// getEEPROM - if TRUE EEPROM.get is used a.k.a read the EEPROM. If FALSE EEPROM.put is used a.k.a write
// addressSizeEEPROM - if TRUE, Function returns addressEEPROM total size - set inputPointer to 255 e.g. getPutEEPROM(255, false, true, true);

int ConfigEEPROM::getPutEEPROM(byte inputPointer, bool runAll, bool getEEPROM, bool addressSizeEEPROM)
{
    int addressEEPROM = 0;
    if (inputPointer == 0 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#0 "));
            tempDefaultValueEEPROM = EEPROM.read(0);
            // Serial.println(tempDefaultValueEEPROM);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.defaultValueEEPROM);
        }
    }
    addressEEPROM += sizeof(config.defaultValueEEPROM);
    if (inputPointer == 1 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#1 "));
            EEPROM.get(addressEEPROM, config.defaultBatteryCutOffVoltage);
            // Serial.println(config.defaultBatteryCutOffVoltage);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.defaultBatteryCutOffVoltage);
        }
    }
    addressEEPROM += sizeof(config.defaultBatteryCutOffVoltage);
    if (inputPointer == 2 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#2 "));
            EEPROM.get(addressEEPROM, config.storageChargeVoltage);
            // Serial.println(config.storageChargeVoltage);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.storageChargeVoltage);
        }
    }
    addressEEPROM += sizeof(config.storageChargeVoltage);
    if (inputPointer == 3 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#3 "));
            EEPROM.get(addressEEPROM, config.batteryVoltageLeak);
            // Serial.println(config.batteryVoltageLeak);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.batteryVoltageLeak);
        }
    }
    addressEEPROM += sizeof(config.batteryVoltageLeak);
    if (inputPointer == 4 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#4 "));
            EEPROM.get(addressEEPROM, config.lowMilliAmps);
            // Serial.println(config.lowMilliAmps);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.lowMilliAmps);
        }
    }
    addressEEPROM += sizeof(config.lowMilliAmps);
    if (inputPointer == 5 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#5 "));
            EEPROM.get(addressEEPROM, config.highMilliOhms);
            // Serial.println(config.highMilliOhms);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.highMilliOhms);
        }
    }
    addressEEPROM += sizeof(config.highMilliOhms);
    if (inputPointer == 6 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#6 "));
            EEPROM.get(addressEEPROM, config.offsetMilliOhms);
            // Serial.println(config.offsetMilliOhms);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.offsetMilliOhms);
        }
    }
    addressEEPROM += sizeof(config.offsetMilliOhms);
    if (inputPointer == 7 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#7 "));
            EEPROM.get(addressEEPROM, config.restTimeMinutes);
            // Serial.println(config.restTimeMinutes);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.restTimeMinutes);
        }
    }
    addressEEPROM += sizeof(config.restTimeMinutes);
    if (inputPointer == 8 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#8 "));
            EEPROM.get(addressEEPROM, config.chargingTimeout);
            // Serial.println(config.chargingTimeout);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.chargingTimeout);
        }
    }
    addressEEPROM += sizeof(config.chargingTimeout);
    if (inputPointer == 9 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#9 "));
            EEPROM.get(addressEEPROM, config.tempThreshold);
            // Serial.println(config.tempThreshold);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.tempThreshold);
        }
    }
    addressEEPROM += sizeof(config.tempThreshold);
    if (inputPointer == 10 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#10 "));
            EEPROM.get(addressEEPROM, config.tempMaxThreshold);
            // Serial.println(config.tempMaxThreshold);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.tempMaxThreshold);
        }
    }
    addressEEPROM += sizeof(config.tempMaxThreshold);
    if (inputPointer == 11 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#11 "));
            EEPROM.get(addressEEPROM, config.rechargeCycle);
            // Serial.println(config.rechargeCycle);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.rechargeCycle);
        }
    }
    addressEEPROM += sizeof(config.rechargeCycle);
    if (inputPointer == 12 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#12 "));
            EEPROM.get(addressEEPROM, config.screenTime);
            // Serial.println(config.screenTime);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.screenTime);
        }
    }
    addressEEPROM += sizeof(config.screenTime);
    if (inputPointer == 13 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#13 "));
            EEPROM.get(addressEEPROM, config.shuntResistor);
            // Serial.println(config.shuntResistor[0]);
            // Serial.println(config.shuntResistor[1]);
            // Serial.println(config.shuntResistor[2]);
            // Serial.println(config.shuntResistor[3]);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.shuntResistor);
        }
    }
    addressEEPROM += sizeof(config.shuntResistor);
    if (inputPointer == 14 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#14 "));
            EEPROM.get(addressEEPROM, config.dallasSerials);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.dallasSerials);
        }
    }
    addressEEPROM += sizeof(config.dallasSerials);
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    if (inputPointer == 15 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#15 "));
            EEPROM.get(addressEEPROM, config.useReferenceVoltage);
            // Serial.println(config.useReferenceVoltage);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.useReferenceVoltage);
        }
    }
    addressEEPROM += sizeof(config.useReferenceVoltage);
    if (inputPointer == 16 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#16 "));
            EEPROM.get(addressEEPROM, config.referenceVoltage);
            // Serial.println(config.referenceVoltage);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.referenceVoltage);
        }
    }
#if defined(ASCD_NANO_4X)
    addressEEPROM += sizeof(config.referenceVoltage);
    if (inputPointer == 17 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#17 "));
            EEPROM.get(addressEEPROM, config.internalReferenceVoltage);
            // Serial.println(config.internalReferenceVoltage);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.internalReferenceVoltage);
        }
    }
    addressEEPROM += sizeof(config.internalReferenceVoltage);
    if (inputPointer == 18 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#18 "));
            EEPROM.get(addressEEPROM, config.chargeLedPinMidVoltage);
            // Serial.println(config.chargeLedPinMidVoltage[0]);
            // Serial.println(config.chargeLedPinMidVoltage[1]);
            // Serial.println(config.chargeLedPinMidVoltage[2]);
            // Serial.println(config.chargeLedPinMidVoltage[3]);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.chargeLedPinMidVoltage);
        }
    }
    if (addressSizeEEPROM)
    {

        addressEEPROM += sizeof(config.chargeLedPinMidVoltage);
        return addressSizeEEPROM;
    }
#else
    addressEEPROM += sizeof(config.referenceVoltage);
    if (inputPointer == 17 || runAll)
    {
        if (getEEPROM)
        {
            // Serial.print(F("#17 "));
            EEPROM.get(addressEEPROM, config.internalReferenceVoltage);
            // Serial.println(config.internalReferenceVoltage);
        }
        else
        {
            EEPROM.put(addressEEPROM, config.internalReferenceVoltage);
        }
    }
    if (addressSizeEEPROM)
    {
        addressEEPROM += sizeof(config.internalReferenceVoltage);
        return addressSizeEEPROM;
    }
#endif
#else
    if (addressSizeEEPROM)
    {
        return addressSizeEEPROM;
    }
#endif
}

void ConfigEEPROM::setDefaultValueEEPROM()
{
    getPutEEPROM(0, false, false, false);
}

void ConfigEEPROM::getDefaultValueEEPROM()
{
    getPutEEPROM(0, false, true, false);
}

void ConfigEEPROM::setDefaultBatteryCutOffVoltage()
{
    getPutEEPROM(1, false, false, false);
}

void ConfigEEPROM::getDefaultBatteryCutOffVoltage()
{
    getPutEEPROM(1, false, true, false);
}

void ConfigEEPROM::setStorageChargeVoltage()
{
    getPutEEPROM(2, false, false, false);
}

void ConfigEEPROM::getStorageChargeVoltage()
{
    getPutEEPROM(2, false, true, false);
}

void ConfigEEPROM::setBatteryVoltageLeak()
{
    getPutEEPROM(3, false, false, false);
}

void ConfigEEPROM::getBatteryVoltageLeak()
{
    getPutEEPROM(3, false, true, false);
}

void ConfigEEPROM::setLowMilliAmps()
{
    getPutEEPROM(4, false, false, false);
}

void ConfigEEPROM::getLowMilliAmps()
{
    getPutEEPROM(4, false, true, false);
}

void ConfigEEPROM::setHighMilliOhms()
{
    getPutEEPROM(5, false, false, false);
}

void ConfigEEPROM::getHighMilliOhms()
{
    getPutEEPROM(5, false, true, false);
}

void ConfigEEPROM::setOffsetMilliOhms()
{
    getPutEEPROM(6, false, false, false);
}

void ConfigEEPROM::getOffsetMilliOhms()
{
    getPutEEPROM(6, false, true, false);
}

void ConfigEEPROM::setRestTimeMinutes()
{
    getPutEEPROM(7, false, false, false);
}

void ConfigEEPROM::getRestTimeMinutes()
{
    getPutEEPROM(7, false, true, false);
}

void ConfigEEPROM::setChargingTimeout()
{
    getPutEEPROM(8, false, false, false);
}

void ConfigEEPROM::getChargingTimeout()
{
    getPutEEPROM(8, false, true, false);
}

void ConfigEEPROM::setTempThreshold()
{
    getPutEEPROM(9, false, false, false);
}

void ConfigEEPROM::getTempThreshold()
{
    getPutEEPROM(9, false, true, false);
}

void ConfigEEPROM::setTempMaxThreshold()
{
    getPutEEPROM(10, false, false, false);
}

void ConfigEEPROM::getTempMaxThreshold()
{
    getPutEEPROM(10, false, true, false);
}

void ConfigEEPROM::setRechargeCycle()
{
    getPutEEPROM(11, false, false, false);
}

void ConfigEEPROM::getRechargeCycle()
{
    getPutEEPROM(11, false, true, false);
}

void ConfigEEPROM::setScreenTime()
{
    getPutEEPROM(12, false, false, false);
}

void ConfigEEPROM::getScreenTime()
{
    getPutEEPROM(12, false, true, false);
}

void ConfigEEPROM::setShuntResistor()
{
    getPutEEPROM(13, false, false, false);
}

void ConfigEEPROM::getShuntResistor()
{
    getPutEEPROM(13, false, true, false);
}

void ConfigEEPROM::setDallasSerials()
{
    getPutEEPROM(14, false, false, false);
}

void ConfigEEPROM::getDallasSerials()
{
    getPutEEPROM(14, false, true, false);
}

#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))

void ConfigEEPROM::setUseReferenceVoltage()
{
    getPutEEPROM(15, false, false, false);
}

void ConfigEEPROM::getUseReferenceVoltage()
{
    getPutEEPROM(15, false, true, false);
}

void ConfigEEPROM::setReferenceVoltage()
{
    getPutEEPROM(16, false, false, false);
}

void ConfigEEPROM::getReferenceVoltage()
{
    getPutEEPROM(16, false, true, false);
}

void ConfigEEPROM::setInternalReferenceVoltage()
{
    getPutEEPROM(17, false, false, false);
}

void ConfigEEPROM::getInternalReferenceVoltage()
{
    getPutEEPROM(17, false, true, false);
}

#if defined(ASCD_NANO_4X)

void ConfigEEPROM::setChargeLedPinMidVoltage()
{
    getPutEEPROM(18, false, false, false);
}

void ConfigEEPROM::getChargeLedPinMidVoltage()
{
    getPutEEPROM(18, false, true, false);
}
#endif
#endif