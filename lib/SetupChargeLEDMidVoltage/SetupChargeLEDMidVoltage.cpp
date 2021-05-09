#include <SetupChargeLEDMidVoltage.h>

SetupChargeLEDMidVoltage::SetupChargeLEDMidVoltage()
{
}

void SetupChargeLEDMidVoltage::init()
{
    writeOutput.init();
    readInput.init();

    for (byte module = 0; module < MODULES_COUNT; module++)
    {
        writeOutput.chargeMosfetOn(module);
        delay(500);
        readInput.batteryVoltage(module);
        readInput.batteryVoltageDrop(module);
        writeOutput.chargeMosfetOff(module); // Turn off the Charge Mosfet
        delay(500);
        readInput.batteryVoltage(module);
        readInput.batteryVoltageDrop(module);
    }
    delay(2000);
    Serial.begin(BAUD_RATE);
    configEEPROM.init();
    Serial.println();
    Serial.println(F("---------------------------------------------------------------------------------------------------"));
    Serial.println(F("ASCD Setup: Charge LED Mid Voltage Detection"));
    Serial.println(F("---------------------------------------------------------------------------------------------------"));
    for (byte i = 0; i < MODULES_COUNT + 1; i++)
    {
    }
    getChargeMidVoltage();
}

void SetupChargeLEDMidVoltage::getChargeMidVoltage()
{
    for (byte module = 0; module < MODULES_COUNT; module++)
    {
        writeOutput.chargeMosfetOn(module);
        delay(500);
        float chargeLedPinOff = readInput.chargeLedVoltage(module);
        Serial.println();
        Serial.print(F("Module: "));
        Serial.println(module + 1);
        Serial.print(F("Charge LED Off Voltage: "));
        Serial.print(chargeLedPinOff / 1000.0);
        Serial.println(F("V"));
        writeOutput.dischargeMosfetOn(module);
        delay(500);
        float chargeLedPinOn = readInput.chargeLedVoltage(module);
        Serial.print(F("Charge LED ON Voltage: "));
        Serial.print(chargeLedPinOn / 1000.0);
        Serial.println(F("V"));
        chargeLedPinMidVoltageArray[module] = (((chargeLedPinOff + chargeLedPinOn) / 2) + chargeLedPinOff) / 2;
        writeOutput.chargeMosfetOff(module);
        writeOutput.dischargeMosfetOff(module);
        Serial.print(F("Mid Voltage: "));
        Serial.print(chargeLedPinMidVoltageArray[module] / 1000.0);
        Serial.println(F("V"));
        Serial.println(F("---------------------------------------------------------------------------------------------------"));
        delay(2000);
    }
    saveToEEPROM();
}

void SetupChargeLEDMidVoltage::saveToEEPROM()
{
    memcpy(config.chargeLedPinMidVoltage, chargeLedPinMidVoltageArray, sizeof(chargeLedPinMidVoltageArray));
    configEEPROM.setChargeLedPinMidVoltage();

    Serial.println(F("---------------------------------------------------------------------------------------------------"));
    Serial.println(F("Charge LED Mid Voltage values Saved to EEPROM"));
    Serial.println(F("---------------------------------------------------------------------------------------------------"));
}