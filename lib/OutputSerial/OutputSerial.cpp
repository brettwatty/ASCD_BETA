#include <OutputSerial.h>

OutputSerial::OutputSerial()
{
}

void OutputSerial::init()
{
#ifndef SERIAL_BEGIN
#define SERIAL_BEGIN
    Serial.begin(BAUD_RATE);
#endif
}

void OutputSerial::displaySerialCycle()
{
    Serial.println();
    Serial.println(serialLine0);
    Serial.println(serialLine1);
}

void OutputSerial::startup()
{
#if defined(ASCD_MEGA_8X)
    Serial.println(F("ASCD MEGA 8X V2.0.0"));
    Serial.println(F("INITIALIZING TP4056"));
#elif defined(ASCD_NANO_4X)
    Serial.println(F("ASCD NANO V2.0.0"));
    Serial.println(F("Init TP5100....."));
#elif defined(ASCD_LEONARDO_4X)
    Serial.println(F("ASCD LEONARDO V1.0.0 - By Nikola Bencic"));
    Serial.println(F("INITIALIZING TP4056"));
#endif
}

void OutputSerial::batteryCheckSerial(byte module, int batteryVoltage)
{
    sprintf_P(serialLine0, PSTR("%d%-19S"), module + 1, PSTR("-BATTERY CHECK"));
    sprintf_P(serialLine1, PSTR("%-15S%d.%02dV"), PSTR("INSERT BATTERY"), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);

    displaySerialCycle();
}

void OutputSerial::batteryBarcodeSerial(byte module, int batteryVoltage)
{
    sprintf_P(serialLine0, PSTR("%d%-19S"), module + 1, PSTR("-SCAN BARCODE"));
    sprintf_P(serialLine1, PSTR("%-15S%d.%02dV"), PSTR(" "), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);

    displaySerialCycle();
}

void OutputSerial::batteryChargeSerial(byte module, bool chargeRecharge, int batteryVoltage, int batteryInitialVoltage, byte batteryTemp, byte hours, byte minutes, byte seconds)
{
    sprintf_P(serialLine0, PSTR("%d%-11S%02d:%02d:%02d"), module + 1, ((chargeRecharge) ? PSTR("-CHARGING ") : PSTR("-RECHARGE ")), hours, minutes, seconds);
    sprintf_P(serialLine1, PSTR("%d.%02dV %02d%-1S %d.%02dV"), (int)(batteryInitialVoltage / 1000.0), (int)((batteryInitialVoltage / 1000.0) * 100) % 100, batteryTemp, PSTR("C"), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);

    displaySerialCycle();
}

void OutputSerial::milliOhmsSerial(byte module, int milliOhms)
{
    sprintf_P(serialLine0, PSTR("%d%-19S"), module + 1, PSTR("-RESISTANCE"));
    sprintf_P(serialLine1, PSTR("%-14S%04dm%c"), PSTR("MILLIOHMS"), (int)milliOhms, 244);

    displaySerialCycle();
}

void OutputSerial::batteryRestSerial(byte module, int batteryVoltage, byte hours, byte minutes, byte seconds)
{
    sprintf_P(serialLine0, PSTR("%d%-11S%02d:%02d:%02d"), module + 1, PSTR("-RESTING"), hours, minutes, seconds);
    sprintf_P(serialLine1, PSTR("%-15S%d.%02dV"), PSTR(" "), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);

    displaySerialCycle();
}

void OutputSerial::batteryDischargeSerial(byte module, int batteryVoltage, int dischargeAmps, int dischargeMilliamps, byte batteryTemp, byte hours, byte minutes, byte seconds)
{
    sprintf_P(serialLine0, PSTR("%d%-7S %d.%02dA %d.%02dV"), module + 1, PSTR("-DCHG"), (int)(dischargeAmps / 1000.0), (int)((dischargeAmps / 1000.0) * 100) % 100, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
    sprintf_P(serialLine1, PSTR("%02d:%02d:%02d %02d%c %04dmAh"), hours, minutes, seconds, batteryTemp, 223, dischargeMilliamps);

    displaySerialCycle();
}

void OutputSerial::completeSerial(byte module, byte faultCode, int milliOhms, int dischargeMilliamps, int batteryVoltage)
{
    switch (faultCode)
    {
    case 0: // Finished
        sprintf_P(serialLine0, PSTR("%d%-13S %d.%02dV"), module + 1, PSTR("-FINISHED"), (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);
        break;
    case 3: // High Milli Ohms
        sprintf_P(serialLine0, PSTR("%d%-19S"), module + 1, PSTR("-FAULT HIGH OHM"));
        break;
    case 5: // Low Milliamps
        sprintf_P(serialLine0, PSTR("%d%-19S"), module + 1, PSTR("-FAULT LOW mAh"));
        break;
    case 7: // High Temperature
        sprintf_P(serialLine0, PSTR("%d%-19S"), module + 1, PSTR("-FAULT HIGH TMP"));
        break;
    case 9: // Charge Timeout
        sprintf_P(serialLine0, PSTR("%d%-19S"), module + 1, PSTR("-FAULT CHG TIME"));
        break;
    }
    sprintf_P(serialLine1, PSTR("%04dm%c %04dmAh %d.%02dV"), (int)milliOhms, 244, dischargeMilliamps, (int)(batteryVoltage / 1000.0), (int)((batteryVoltage / 1000.0) * 100) % 100);

    displaySerialCycle();
}
