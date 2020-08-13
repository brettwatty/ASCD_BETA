#include <Variables.h>
#include <WriteOutputMega8x.h>

WriteOutput::WriteOutput()
{
    init();
}

void WriteOutput::init()
{
    for (byte i = 0; i < 8; i++)
    {
        pinMode(chargeMosfetPins[module], OUTPUT);
        pinMode(dischargeMosfetPins[module], OUTPUT);
        chargeMosfetOff(i);
        dischargeMosfetOff(i);
    }
}

void WriteOutput::chargeMosfetOn(byte module)
{
     setOutput(chargeMosfetPins[module], true);
}

void WriteOutput::chargeMosfetOff(byte module)
{
     setOutput(chargeMosfetPins[module], false);
}

void WriteOutput::dischargeMosfetOn(byte module)
{
     setOutput(dischargeMosfetPins[module], true);
}

void WriteOutput::dischargeMosfetOff(byte module)
{
     setOutput(dischargeMosfetPins[module], false);
}

void WriteOutput::setOutput(const byte arrayPin, bool onOff)
{
    if (onOff == true)
    {
        digitalWrite(arrayPin, HIGH);
    }
    else
    {
        digitalWrite(arrayPin, LOW);
    }
}
