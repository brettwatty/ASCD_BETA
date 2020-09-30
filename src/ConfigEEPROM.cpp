#include "Config.h"

#include <ConfigEEPROM.h>
#include <EEPROM.h>

ConfigEEPROM::ConfigEEPROM()
{
}

void ConfigEEPROM::init()
{
    // writeEEPROMTest();
    readEEPROMTest();
}

void ConfigEEPROM::writeEEPROMTest()
{
    // // useReferenceVoltage
    // EEPROM.put(addressEEPROM, variables.useReferenceVoltage);
    // addressEEPROM += sizeof(bool);

    // // referenceVoltage
    // EEPROM.put(addressEEPROM, variables.referenceVoltage);
    // addressEEPROM += sizeof(float);

    // // internalReferenceVoltage
    // EEPROM.put(addressEEPROM, variables.internalReferenceVoltage);
    // addressEEPROM += sizeof(float);

    // // defaultBatteryCutOffVoltage
    // EEPROM.put(addressEEPROM, variables.defaultBatteryCutOffVoltage);
    // addressEEPROM += sizeof(float);

    // // storageChargeVoltage
    // EEPROM.put(addressEEPROM, variables.storageChargeVoltage);
    // addressEEPROM += sizeof(float);

    // // batteryVoltageLeak
    // EEPROM.put(addressEEPROM, variables.batteryVoltageLeak);
    // addressEEPROM += sizeof(float);

    // // lowMilliAmps
    // EEPROM.put(addressEEPROM, variables.lowMilliAmps);
    // addressEEPROM += sizeof(int);

    // // highMilliOhms
    // EEPROM.put(addressEEPROM, variables.highMilliOhms);
    // addressEEPROM += sizeof(int);

    // // offsetMilliOhms
    // EEPROM.put(addressEEPROM, variables.offsetMilliOhms);
    // addressEEPROM += sizeof(int);

    // // restTimeMinutes
    // EEPROM.put(addressEEPROM, variables.restTimeMinutes);
    // addressEEPROM += sizeof(byte);

    // // chargingTimeout
    // EEPROM.put(addressEEPROM, variables.chargingTimeout);
    // addressEEPROM += sizeof(byte);

    // // tempThreshold
    // EEPROM.put(addressEEPROM, variables.tempThreshold);
    // addressEEPROM += sizeof(byte);

    // // tempMaxThreshold
    // EEPROM.put(addressEEPROM, variables.tempMaxThreshold);
    // addressEEPROM += sizeof(byte);

    // // rechargeCycle
    // EEPROM.put(addressEEPROM, variables.rechargeCycle);
    // // addressEEPROM += sizeof(bool);
}

void ConfigEEPROM::readEEPROMTest()
{
    // // useReferenceVoltage
    // EEPROM.get(addressEEPROM, testOutput1);
    // Serial.print("useReferenceVoltage: ");
    // Serial.println(testOutput1);
    // addressEEPROM += sizeof(bool);

    // // referenceVoltage
    // EEPROM.get(addressEEPROM, testOutput2);
    // Serial.print("referenceVoltage: ");
    // Serial.println(testOutput2);
    // addressEEPROM += sizeof(float);

    // // internalReferenceVoltage
    // EEPROM.get(addressEEPROM, testOutput3);
    // Serial.print("internalReferenceVoltage: ");
    // Serial.println(testOutput3);
    // addressEEPROM += sizeof(float);

    // // defaultBatteryCutOffVoltage
    // EEPROM.get(addressEEPROM, testOutput4);
    // Serial.print("defaultBatteryCutOffVoltage: ");
    // Serial.println(testOutput4);
    // addressEEPROM += sizeof(float);

    // // storageChargeVoltage
    // EEPROM.get(addressEEPROM, testOutput5);
    // Serial.print("storageChargeVoltage: ");
    // Serial.println(testOutput5);
    // addressEEPROM += sizeof(float);

    // // batteryVoltageLeak
    // EEPROM.get(addressEEPROM, testOutput6);
    // Serial.print("batteryVoltageLeak: ");
    // Serial.println(testOutput6);
    // addressEEPROM += sizeof(float);

    // // lowMilliAmps
    // EEPROM.get(addressEEPROM, testOutput7);
    // Serial.print("lowMilliAmps: ");
    // Serial.println(testOutput7);
    // addressEEPROM += sizeof(int);

    // // highMilliOhms
    // EEPROM.get(addressEEPROM, testOutput8);
    // Serial.print("highMilliOhms: ");
    // Serial.println(testOutput8);
    // addressEEPROM += sizeof(int);

    // // offsetMilliOhms
    // EEPROM.get(addressEEPROM, testOutput9);
    // Serial.print("offsetMilliOhms: ");
    // Serial.println(testOutput9);
    // addressEEPROM += sizeof(int);

    // // restTimeMinutes
    // EEPROM.get(addressEEPROM, testOutput10);
    // Serial.print("restTimeMinutes: ");
    // Serial.println(testOutput10);
    // addressEEPROM += sizeof(byte);

    // // chargingTimeout
    // EEPROM.get(addressEEPROM, testOutput11);
    // Serial.print("chargingTimeout: ");
    // Serial.println(testOutput11);
    // addressEEPROM += sizeof(byte);

    // // tempThreshold
    // EEPROM.get(addressEEPROM, testOutput12);
    // Serial.print("tempThreshold: ");
    // Serial.println(testOutput12);
    // addressEEPROM += sizeof(byte);

    // // tempMaxThreshold
    // EEPROM.get(addressEEPROM, testOutput13);
    // Serial.print("tempMaxThreshold: ");
    // Serial.println(testOutput13);
    // addressEEPROM += sizeof(byte);

    // // rechargeCycle
    // EEPROM.get(addressEEPROM, testOutput14);
    // Serial.print("rechargeCycle: ");
    // Serial.println(testOutput14);
    // // addressEEPROM += sizeof(bool);
}

void ConfigEEPROM::clearEEPROMTest()
{
}