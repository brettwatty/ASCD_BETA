#include <ConfigEEPROM.h>
#include <EEPROM.h>

ConfigEEPROM::ConfigEEPROM()
{
}

void ConfigEEPROM::init()
{
    // clearEEPROM();
    // clearEEPROMConfig();
    setAddressSize();
    checkEEPROMEmpty();
    Serial.println(F("--------------------------------------------------------"));
    if (emptyEEPROM == false)
    {
        // loadConfigEEPROM(); // EEPROM is not EMPTY -> Load Values into config Struct
        Serial.println(F("Config Loaded from EEPROM"));
    }
    else
    {
        // writeCustomConfigEEPROM();
        Serial.println(F("EEPROM Empty - Using values from Config.h"));
    }
    Serial.println(F("--------------------------------------------------------"));
}

void ConfigEEPROM::checkEEPROMEmpty()
{
    byte countEmptyAddresses = 0;
    byte valueEEPROM;
    for (byte i = 0; i < addressCountEEPROM; i++)
    {
        valueEEPROM = EEPROM.read(i);
        if (valueEEPROM == 255)
        {
            countEmptyAddresses++;
        }
    }
    if (addressCountEEPROM == countEmptyAddresses)
    {
        // EEPROM is EMPTY
        emptyEEPROM = true;
    }
    else
    {
        // EEPROM is NOT EMPTY
        emptyEEPROM = false;
    }
}

bool ConfigEEPROM::getEEPROMEmpty()
{
    return emptyEEPROM;
}

void ConfigEEPROM::setAddressSize()
{
    addressCountEEPROM = 0;
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    addressCountEEPROM += sizeof(config.useReferenceVoltage);
    addressCountEEPROM += sizeof(config.referenceVoltage);
    addressCountEEPROM += sizeof(config.internalReferenceVoltage);
#endif
    addressCountEEPROM += sizeof(config.defaultBatteryCutOffVoltage);
    addressCountEEPROM += sizeof(config.storageChargeVoltage);
    addressCountEEPROM += sizeof(config.batteryVoltageLeak);
    addressCountEEPROM += sizeof(config.lowMilliAmps);
    addressCountEEPROM += sizeof(config.highMilliOhms);
    addressCountEEPROM += sizeof(config.offsetMilliOhms);
    addressCountEEPROM += sizeof(config.restTimeMinutes);
    addressCountEEPROM += sizeof(config.chargingTimeout);
    addressCountEEPROM += sizeof(config.tempThreshold);
    addressCountEEPROM += sizeof(config.tempMaxThreshold);
    addressCountEEPROM += sizeof(config.rechargeCycle);
    addressCountEEPROM += sizeof(config.screenTime);
    addressCountEEPROM += sizeof(config.shuntResistor);
#if defined(ASCD_NANO_4X)
    addressCountEEPROM += sizeof(config.chargeLedPinMidVoltage);
#endif
    addressCountEEPROM += sizeof(config.dallasSerials);
}
void ConfigEEPROM::clearCustomEEPROM()
{
    byte configAddressCountEEPROM = 0;
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    configAddressCountEEPROM += sizeof(config.useReferenceVoltage);
    configAddressCountEEPROM += sizeof(config.referenceVoltage);
    configAddressCountEEPROM += sizeof(config.internalReferenceVoltage);
#endif
    configAddressCountEEPROM += sizeof(config.defaultBatteryCutOffVoltage);
    configAddressCountEEPROM += sizeof(config.storageChargeVoltage);
    configAddressCountEEPROM += sizeof(config.batteryVoltageLeak);
    configAddressCountEEPROM += sizeof(config.lowMilliAmps);
    configAddressCountEEPROM += sizeof(config.highMilliOhms);
    configAddressCountEEPROM += sizeof(config.offsetMilliOhms);
    configAddressCountEEPROM += sizeof(config.restTimeMinutes);
    configAddressCountEEPROM += sizeof(config.chargingTimeout);
    configAddressCountEEPROM += sizeof(config.tempThreshold);
    configAddressCountEEPROM += sizeof(config.tempMaxThreshold);
    configAddressCountEEPROM += sizeof(config.rechargeCycle);
    configAddressCountEEPROM += sizeof(config.screenTime);
    configAddressCountEEPROM += sizeof(config.shuntResistor);

    for (byte i = 0; i < configAddressCountEEPROM; i++)
    {
        EEPROM.update(i, 255);
    }
}

void ConfigEEPROM::writeCustomConfigEEPROM()
{
    addressEEPROM = 0;
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    EEPROM.put(addressEEPROM, config.useReferenceVoltage);
    addressEEPROM += sizeof(config.useReferenceVoltage);

    EEPROM.put(addressEEPROM, config.referenceVoltage);
    addressEEPROM += sizeof(config.referenceVoltage);

    EEPROM.put(addressEEPROM, config.internalReferenceVoltage);
    addressEEPROM += sizeof(config.internalReferenceVoltage);
#endif
    EEPROM.put(addressEEPROM, config.defaultBatteryCutOffVoltage);
    addressEEPROM += sizeof(config.defaultBatteryCutOffVoltage);

    EEPROM.put(addressEEPROM, config.storageChargeVoltage);
    addressEEPROM += sizeof(config.storageChargeVoltage);

    EEPROM.put(addressEEPROM, config.batteryVoltageLeak);
    addressEEPROM += sizeof(config.batteryVoltageLeak);

    EEPROM.put(addressEEPROM, config.lowMilliAmps);
    addressEEPROM += sizeof(config.lowMilliAmps);

    EEPROM.put(addressEEPROM, config.highMilliOhms);
    addressEEPROM += sizeof(config.highMilliOhms);

    EEPROM.put(addressEEPROM, config.offsetMilliOhms);
    addressEEPROM += sizeof(config.offsetMilliOhms);

    EEPROM.put(addressEEPROM, config.restTimeMinutes);
    addressEEPROM += sizeof(config.restTimeMinutes);

    EEPROM.put(addressEEPROM, config.chargingTimeout);
    addressEEPROM += sizeof(config.chargingTimeout);

    EEPROM.put(addressEEPROM, config.tempThreshold);
    addressEEPROM += sizeof(config.tempThreshold);

    EEPROM.put(addressEEPROM, config.tempMaxThreshold);
    addressEEPROM += sizeof(config.tempMaxThreshold);

    EEPROM.put(addressEEPROM, config.rechargeCycle);
    addressEEPROM += sizeof(config.rechargeCycle);

    EEPROM.put(addressEEPROM, config.screenTime);
    addressEEPROM += sizeof(config.screenTime);

    EEPROM.put(addressEEPROM, config.shuntResistor);
    addressEEPROM += sizeof(config.shuntResistor);

    emptyEEPROM = false;
}

void ConfigEEPROM::writeConfigEEPROM()
{
    addressEEPROM = 0;
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    EEPROM.put(addressEEPROM, config.useReferenceVoltage);
    addressEEPROM += sizeof(config.useReferenceVoltage);

    EEPROM.put(addressEEPROM, config.referenceVoltage);
    addressEEPROM += sizeof(config.referenceVoltage);

    EEPROM.put(addressEEPROM, config.internalReferenceVoltage);
    addressEEPROM += sizeof(config.internalReferenceVoltage);
#endif
    EEPROM.put(addressEEPROM, config.defaultBatteryCutOffVoltage);
    addressEEPROM += sizeof(config.defaultBatteryCutOffVoltage);

    EEPROM.put(addressEEPROM, config.storageChargeVoltage);
    addressEEPROM += sizeof(config.storageChargeVoltage);

    EEPROM.put(addressEEPROM, config.batteryVoltageLeak);
    addressEEPROM += sizeof(config.batteryVoltageLeak);

    EEPROM.put(addressEEPROM, config.lowMilliAmps);
    addressEEPROM += sizeof(config.lowMilliAmps);

    EEPROM.put(addressEEPROM, config.highMilliOhms);
    addressEEPROM += sizeof(config.highMilliOhms);

    EEPROM.put(addressEEPROM, config.offsetMilliOhms);
    addressEEPROM += sizeof(config.offsetMilliOhms);

    EEPROM.put(addressEEPROM, config.restTimeMinutes);
    addressEEPROM += sizeof(config.restTimeMinutes);

    EEPROM.put(addressEEPROM, config.chargingTimeout);
    addressEEPROM += sizeof(config.chargingTimeout);

    EEPROM.put(addressEEPROM, config.tempThreshold);
    addressEEPROM += sizeof(config.tempThreshold);

    EEPROM.put(addressEEPROM, config.tempMaxThreshold);
    addressEEPROM += sizeof(config.tempMaxThreshold);

    EEPROM.put(addressEEPROM, config.rechargeCycle);
    addressEEPROM += sizeof(config.rechargeCycle);

    EEPROM.put(addressEEPROM, config.screenTime);
    addressEEPROM += sizeof(config.screenTime);

    EEPROM.put(addressEEPROM, config.shuntResistor);
    addressEEPROM += sizeof(config.shuntResistor);
#if defined(ASCD_NANO_4X)
    EEPROM.put(addressEEPROM, config.chargeLedPinMidVoltage);
    addressEEPROM += sizeof(config.chargeLedPinMidVoltage);
#endif
    EEPROM.put(addressEEPROM, config.dallasSerials);

    emptyEEPROM = false;
}

void ConfigEEPROM::loadConfigEEPROM()
{
#if (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    addressEEPROM = 0;
    EEPROM.get(addressEEPROM, config.useReferenceVoltage);
    addressEEPROM += sizeof(config.useReferenceVoltage);

    EEPROM.get(addressEEPROM, config.referenceVoltage);
    addressEEPROM += sizeof(config.referenceVoltage);

    EEPROM.get(addressEEPROM, config.internalReferenceVoltage);
    addressEEPROM += sizeof(config.internalReferenceVoltage);
#endif
    EEPROM.get(addressEEPROM, config.defaultBatteryCutOffVoltage);
    addressEEPROM += sizeof(config.defaultBatteryCutOffVoltage);

    EEPROM.get(addressEEPROM, config.storageChargeVoltage);
    addressEEPROM += sizeof(config.storageChargeVoltage);

    EEPROM.get(addressEEPROM, config.batteryVoltageLeak);
    addressEEPROM += sizeof(config.batteryVoltageLeak);

    EEPROM.get(addressEEPROM, config.lowMilliAmps);
    addressEEPROM += sizeof(config.lowMilliAmps);

    EEPROM.get(addressEEPROM, config.highMilliOhms);
    addressEEPROM += sizeof(config.highMilliOhms);

    EEPROM.get(addressEEPROM, config.offsetMilliOhms);
    addressEEPROM += sizeof(config.offsetMilliOhms);

    EEPROM.get(addressEEPROM, config.restTimeMinutes);
    addressEEPROM += sizeof(config.restTimeMinutes);

    EEPROM.get(addressEEPROM, config.chargingTimeout);
    addressEEPROM += sizeof(config.chargingTimeout);

    EEPROM.get(addressEEPROM, config.tempThreshold);
    addressEEPROM += sizeof(config.tempThreshold);

    EEPROM.get(addressEEPROM, config.tempMaxThreshold);
    addressEEPROM += sizeof(config.tempMaxThreshold);

    EEPROM.get(addressEEPROM, config.rechargeCycle);
    addressEEPROM += sizeof(config.rechargeCycle);

    EEPROM.get(addressEEPROM, config.screenTime);
    addressEEPROM += sizeof(config.screenTime);

    EEPROM.get(addressEEPROM, config.shuntResistor);
    addressEEPROM += sizeof(config.shuntResistor);
#if defined(ASCD_NANO_4X)
    EEPROM.get(addressEEPROM, config.chargeLedPinMidVoltage);
    addressEEPROM += sizeof(config.chargeLedPinMidVoltage);
#endif
    EEPROM.get(addressEEPROM, config.dallasSerials);
}

void ConfigEEPROM::clearEEPROM()
{
    for (unsigned int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.update(i, 255);
    }
}