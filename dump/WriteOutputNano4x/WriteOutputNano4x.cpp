#include <Variables.h>
#include <WriteOutputNano4x.h>

WriteOutput::WriteOutput()
{
    init();
}

void WriteOutput::init()
{
    // Set pins to output so you can control the shift register
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    digitalWrite(latchPin, LOW);

    // Set all pins to LOW
    for (byte i = 0; i < 4; i++)
    {
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
    byte baseTwo = 1;
    byte eightBitDecimal = 0;
    static bool digitalPinsState[8]; // Boolean Array for all the Shift Register Pin Values (LOW/HIGH - 0/1)
    digitalPinsState[arrayPin] = onOff;
    for (byte i = 0; i < 8; i++)
    {
        if (digitalPinsState[i] == 1)
            eightBitDecimal += baseTwo;
        baseTwo *= 2;
    }
    // Set the latchPin LOW
    digitalWrite(latchPin, LOW);
    // Shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, eightBitDecimal);
    // Set the latchPin HIGH
    digitalWrite(latchPin, HIGH);
}