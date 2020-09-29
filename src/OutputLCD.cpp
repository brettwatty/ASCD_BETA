#include "Config.h"

#include <OutputLCD.h>
#include <LiquidCrystal_I2C.h>

#if defined(ASCD_MEGA_8X)
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display
#elif defined(ASCD_NANO_4X)
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif

OutputLCD::OutputLCD()
{
}

void OutputLCD::init()
{
    lcd.init();
    lcd.clear();
    lcd.backlight(); // Turn on backlight
}

void OutputLCD::displayLCDCycle()
{
#if defined(ASCD_MEGA_8X)
    lcd.setCursor(0, 0);
    lcd.print(lcdLine0);
    lcd.setCursor(0, 1);
    lcd.print(lcdLine1);
    lcd.setCursor(0, 2);
    lcd.print(lcdLine2);
    lcd.setCursor(0, 3);
    lcd.print(lcdLine3);
#elif defined(ASCD_NANO_4X)
    lcd.setCursor(0, 0);
    lcd.print(lcdLine0);
    lcd.setCursor(0, 1);
    lcd.print(lcdLine1);
#endif
}

void OutputLCD::startup()
{
#if defined(ASCD_MEGA_8X)
    sprintf_P(lcdLine0, PSTR("%-20S"), PSTR("ASCD MEGA 8X V2.0.0"));
    sprintf_P(lcdLine1, PSTR("%-20S"), PSTR("INITIALIZING TP4056"));
#elif defined(ASCD_NANO_4X)
    sprintf_P(lcdLine0, PSTR("%-16S"), PSTR("ASCD NANO V2.0.0"));
    sprintf_P(lcdLine1, PSTR("%-16S"), PSTR("Init TP5100....."));
#endif
    displayLCDCycle();
}

void OutputLCD::batteryCheckLCD(byte module, int batteryVoltage)
{
#if defined(ASCD_MEGA_8X)
    sprintf_P(lcdLine0, PSTR("%d%-19S"), module + 1, PSTR("-BATTERY CHECK"));
    sprintf_P(lcdLine1, PSTR("%-15S%d.%02dV"), PSTR("INSERT BATTERY"), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
    sprintf_P(lcdLine2, PSTR("%-20S"), PSTR(" "));
    sprintf_P(lcdLine3, PSTR("%-20S"), PSTR(" "));
#elif defined(ASCD_NANO_4X)
    sprintf_P(lcdLine0, PSTR("%d%-15S"), module + 1, PSTR("-BATTERY CHECK"));
    sprintf_P(lcdLine1, PSTR("%-11S%d.%02dV"), PSTR("INSERT BAT"), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
#endif
    displayLCDCycle();
}

void OutputLCD::batteryBarcodeLCD(byte module, int batteryVoltage)
{
#if defined(ASCD_MEGA_8X)
    sprintf_P(lcdLine0, PSTR("%d%-19S"), module + 1, PSTR("-SCAN BARCODE"));
    sprintf_P(lcdLine1, PSTR("%-15S%d.%02dV"), PSTR(" "), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
#elif defined(ASCD_NANO_4X)
    sprintf_P(lcdLine0, PSTR("%d%-15S"), module + 1, PSTR("-SCAN BARCODE"));
    sprintf_P(lcdLine1, PSTR("%-11S%d.%02dV"), PSTR(" "), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
#endif
    displayLCDCycle();
}

void OutputLCD::batteryChargeLCD(byte module, bool chargeRecharge, int batteryVoltage, int batteryInitialVoltage, byte batteryTemp, byte hours, byte minutes, byte seconds)
{
#if defined(ASCD_MEGA_8X)
    sprintf_P(lcdLine0, PSTR("%d%-11S%02d:%02d:%02d"), module + 1, ((chargeRecharge) ? PSTR("-CHARGING ") : PSTR("-RECHARGE ")), hours, minutes, seconds);
    sprintf_P(lcdLine1, PSTR("%d.%02dV   %02d%cC   %d.%02dV"), (int)(batteryInitialVoltage / 1000.0), (int)((batteryInitialVoltage / 1000.0) * 100) % 100, batteryTemp, 223, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
#elif defined(ASCD_NANO_4X)
    sprintf_P(lcdLine0, PSTR("%d%-7S%02d:%02d:%02d"), module + 1, ((chargeRecharge) ? PSTR("-CHRG ") : PSTR("-RCHG ")), hours, minutes, seconds);
    sprintf_P(lcdLine1, PSTR("%d.%02dV  %02d%c %d.%02dV"), (int)(batteryInitialVoltage / 1000.0), (int)((batteryInitialVoltage / 1000.0) * 100) % 100, batteryTemp, 223, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
#endif
    displayLCDCycle();
}

void OutputLCD::milliOhmsLCD(byte module, int milliOhms)
{
#if defined(ASCD_MEGA_8X)
    sprintf_P(lcdLine0, PSTR("%d%-19S"), module + 1, PSTR("-RESISTANCE"));
    sprintf_P(lcdLine1, PSTR("%-14S%04dm%c"), PSTR("MILLIOHMS"), (int)milliOhms, 244);
#elif defined(ASCD_NANO_4X)
    sprintf_P(lcdLine0, PSTR("%d%-15S"), module + 1, PSTR("-RESISTANCE"));
    sprintf_P(lcdLine1, PSTR("%-10S%04dm%c"), PSTR("MILLIOHMS"), (int)milliOhms, 244);
#endif
    displayLCDCycle();
}

void OutputLCD::batteryRestLCD(byte module, int batteryVoltage, byte hours, byte minutes, byte seconds)
{
#if defined(ASCD_MEGA_8X)
    sprintf_P(lcdLine0, PSTR("%d%-11S%02d:%02d:%02d"), module + 1, PSTR("-RESTING"), hours, minutes, seconds);
    sprintf_P(lcdLine1, PSTR("%-15S%d.%02dV"), PSTR(" "), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
#elif defined(ASCD_NANO_4X)
    sprintf_P(lcdLine0, PSTR("%d%-7S%02d:%02d:%02d"), module + 1, PSTR("-REST"), hours, minutes, seconds);
    sprintf_P(lcdLine1, PSTR("%-11S%d.%02dV"), PSTR(" "), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
#endif
    displayLCDCycle();
}

void OutputLCD::batteryDischargeLCD(byte module, int batteryVoltage, int dischargeAmps, int dischargeMilliamps, byte batteryTemp, byte hours, byte minutes, byte seconds)
{
#if defined(ASCD_MEGA_8X)
    sprintf_P(lcdLine0, PSTR("%d%-7S %d.%02dA %d.%02dV"), module + 1, PSTR("-DCHG"), (int)(dischargeAmps / 1000.0), (int)((dischargeAmps / 1000.0) * 100) % 100, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
    sprintf_P(lcdLine1, PSTR("%02d:%02d:%02d %02d%c %04dmAh"), hours, minutes, seconds, batteryTemp, 223, dischargeMilliamps));
#elif defined(ASCD_NANO_4X)
    sprintf_P(lcdLine0, PSTR("%d%-4S%d.%02dA %d.%02dV"), module + 1, PSTR("-DC"), (int)(dischargeAmps / 1000.0), (int)((dischargeAmps / 1000.0) * 100) % 100, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
    sprintf_P(lcdLine1, PSTR("%02d:%02d:%02d %04dmAh"), hours, minutes, seconds, dischargeMilliamps);
#endif
    displayLCDCycle();
}

void OutputLCD::completeLCD(byte module, byte faultCode, int milliOhms, int dischargeMilliamps, int batteryVoltage)
{
#if defined(ASCD_MEGA_8X)
    switch (faultCode)
    {
    case 0: // Finished
        sprintf_P(lcdLine0, PSTR("%d%-13S %d.%02dV"), module + 1, PSTR("-FINISHED"), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
        break;
    case 3: // High Milli Ohms
        sprintf_P(lcdLine0, PSTR("%d%-19S"), module + 1, PSTR("-FAULT HIGH OHM"));
        break;
    case 5: // Low Milliamps
        sprintf_P(lcdLine0, PSTR("%d%-19S"), module + 1, PSTR("-FAULT LOW mAh"));
        break;
    case 7: // High Temperature
        sprintf_P(lcdLine0, PSTR("%d%-19S"), module + 1, PSTR("-FAULT HIGH TMP"));
        break;
    case 9: // Charge Timeout
        sprintf_P(lcdLine0, PSTR("%d%-19S"), module + 1, PSTR("-FAULT CHG TIME"));
        break;
    }
    sprintf_P(lcdLine1, PSTR("%04dm%c %04dmAh %d.%02dV"), (int)milliOhms, 244, dischargeMilliamps, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
#elif defined(ASCD_NANO_4X)
    switch (faultCode)
    {
    case 0: // Finished
        sprintf_P(lcdLine0, PSTR("%d%-9S %d.%02dV"), module + 1, PSTR("-FINISHED"), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
        break;
    case 3: // High Milli Ohms
        sprintf_P(lcdLine0, PSTR("%d%-15S"), module + 1, PSTR("-FAULT HIGH OHM"));
        break;
    case 5: // Low Milliamps
        sprintf_P(lcdLine0, PSTR("%d%-15S"), module + 1, PSTR("-FAULT LOW mAh"));
        break;
    case 7: // High Temperature
        sprintf_P(lcdLine0, PSTR("%d%-15S"), module + 1, PSTR("-FAULT HIGH TMP"));
        break;
    case 9: // Charge Timeout
        sprintf_P(lcdLine0, PSTR("%d%-15S"), module + 1, PSTR("-FAULT CHG TIME"));
        break;
    }
    sprintf_P(lcdLine1, PSTR("%04dm%c   %04dmAh"), (int)milliOhms, 244, dischargeMilliamps);
#endif
    displayLCDCycle();
}
