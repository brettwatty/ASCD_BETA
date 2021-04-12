#include <OutputSerial.h>

OutputSerial::OutputSerial()
{
}

void OutputSerial::init()
{
#ifndef SERIAL_BEGIN
#define SERIAL_BEGIN
    Serial.begin(115200);
#endif
}

void OutputSerial::startup()
{
#if defined(ASCD_MEGA_8X)
    sprintf_P(lcdLine0, PSTR("%-20S"), PSTR("ASCD MEGA 8X V2.0.0"));
    sprintf_P(lcdLine1, PSTR("%-20S"), PSTR("INITIALIZING TP4056"));
#elif defined(ASCD_NANO_4X)
    sprintf_P(lcdLine0, PSTR("%-16S"), PSTR("ASCD NANO V2.0.0"));
    sprintf_P(lcdLine1, PSTR("%-16S"), PSTR("Init TP5100....."));
#elif defined(ASCD_LEONARDO_4X)

#endif
    displaySerialCycle();
}