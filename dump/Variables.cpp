#include "Variables.h"

// ----------------------------------------------------------------------------------------------------------------------------------------------------------

CustomSettings::CustomSettings()
{
  init();
}
void CustomSettings::init()
{
}

bool CustomSettings::getUseReferenceVoltage()
{
  return useReferenceVoltage;
}

float CustomSettings::getReferenceVoltage()
{
  return referenceVoltage;
}

float CustomSettings::getInternalReferenceVoltage()
{
  return internalReferenceVoltage;
}

float CustomSettings::getDefaultBatteryCutOffVoltage()
{
  return defaultBatteryCutOffVoltage;
}

byte CustomSettings::getRestTimeMinutes()
{
  return restTimeMinutes;
}

int CustomSettings::getLowMilliAmps()
{
  return lowMilliAmps;
}

int CustomSettings::getHighMilliOhms()
{
  return highMilliOhms;
}

int CustomSettings::getOffsetMilliOhms()
{
  return offsetMilliOhms;
}

byte CustomSettings::getChargingTimeout()
{
  return chargingTimeout;
}

byte CustomSettings::getTempThreshold()
{
  return tempThreshold;
}

byte CustomSettings::getTempMaxThreshold()
{
  return tempMaxThreshold;
}

float CustomSettings::getBatteryVoltageLeak()
{
  return batteryVoltageLeak;
}

byte CustomSettings::getModulesCount()
{
  return modulesCount;
}

byte CustomSettings::getScreenTime()
{
  return screenTime;
}

int CustomSettings::getDischargeReadInterval()
{
  return dischargeReadInterval;
}

bool CustomSettings::getRechargeCycle()
{
  return rechargeCycle;
}

float CustomSettings::getStorageChargeVoltage()
{
  return storageChargeVoltage;
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------

Modules::Modules()
{
  init();
}
void Modules::init()
{
  // module[0].chargeMosfetPin = 0;
  // module[1].chargeMosfetPin = 2;
  // module[2].chargeMosfetPin = 4;
  // module[3].chargeMosfetPin = 6;
}

/*
byte Modules::getBatteryVoltagePin() {
  return batteryVoltagePin;
}

byte Modules::getBatteryVoltageDropPin() {
  return batteryVoltageDropPin;
}

byte Modules::getChargeLedPin() {
  return chargeLedPin;
}

byte Modules::getChargeMosfetPin() {
  return chargeMosfetPin;
}

byte Modules::getDischargeMosfetPin() {
  return dischargeMosfetPin;
}
*/
