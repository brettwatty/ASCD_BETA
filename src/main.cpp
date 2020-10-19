
#include <Arduino.h>
#if defined(ASCD_WIFI_CLIENT)
#include <ClientWIFI.h>
ClientWIFI clientWIFI;
#elif defined(SETUP_TEMP_SENSOR_SERIALS)
#include <SetupTempSensorSerials.h>
SetupTempSensorSerials setupTempSensorSerials;
#elif defined(SETUP_CHARGE_LED_MID_VOLTAGE)
#include <SetupChargeLEDMidVoltage.h>
SetupChargeLEDMidVoltage setupChargeLEDMidVoltage;
#elif (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
#include <CycleFunctions.h>
Cycle cycle;
#endif

void setup()
{
#if defined(ASCD_WIFI_CLIENT)
    clientWIFI.init();
#elif defined(SETUP_TEMP_SENSOR_SERIALS)
    setupTempSensorSerials.init();
#elif defined(SETUP_CHARGE_LED_MID_VOLTAGE)
    setupChargeLEDMidVoltage.init();
#elif (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    cycle.init();
#endif
}

void loop()
{
#if defined(ASCD_WIFI_CLIENT)
    clientWIFI.cycleClientWifi();
#elif defined(SETUP_TEMP_SENSOR_SERIALS)
    setupTempSensorSerials.getTempSensorModule();
#elif defined(SETUP_CHARGE_LED_MID_VOLTAGE)

#elif (defined(ASCD_NANO_4X) || defined(ASCD_MEGA_8X))
    cycle.cycleRun();
#endif
}