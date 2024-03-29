
#include <Arduino.h>
#if defined(ASCD_WIFI_CLIENT)
#include <ClientWIFI.h>
ClientWIFI clientWIFI;
#elif defined(ASCD_WIFI_CLIENT_WEB)
#include <ClientWIFI_WEB.h>
ClientWIFI_WEB clientWIFI_WEB;
#elif defined(SETUP_TEMP_SENSOR_SERIALS)
#include <SetupTempSensorSerials.h>
SetupTempSensorSerials setupTempSensorSerials;
#elif defined(SETUP_CHARGE_LED_MID_VOLTAGE)
#include <SetupChargeLEDMidVoltage.h>
SetupChargeLEDMidVoltage setupChargeLEDMidVoltage;
#elif (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X) || defined(ASCD_MEGA_8X))
#include <avr/wdt.h>
#include <CycleFunctions.h>
Cycle cycle;
#endif

void setup()
{
#if defined(ASCD_WIFI_CLIENT)
    clientWIFI.init();
#elif defined(ASCD_WIFI_CLIENT_WEB)
    clientWIFI_WEB.init();
#elif defined(SETUP_TEMP_SENSOR_SERIALS)
    setupTempSensorSerials.init();
#elif defined(SETUP_CHARGE_LED_MID_VOLTAGE)
    setupChargeLEDMidVoltage.init();
#elif (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X) || defined(ASCD_MEGA_8X))
    MCUSR = 0;
    wdt_disable();
    cycle.init();
#endif
}

void loop()
{
#if defined(ASCD_WIFI_CLIENT)
    clientWIFI.cycleClientWifi();
#elif defined(ASCD_WIFI_CLIENT_WEB)
    clientWIFI_WEB.cycleClientWifi();
#elif defined(SETUP_TEMP_SENSOR_SERIALS)
    setupTempSensorSerials.getTempSensorModule();
#elif defined(SETUP_CHARGE_LED_MID_VOLTAGE)

#elif (defined(ASCD_NANO_4X) || defined(ASCD_LEONARDO_4X) || defined(ASCD_MEGA_8X))
    cycle.cycleRun();
#endif
}