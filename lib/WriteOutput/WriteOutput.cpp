// #include <Config.h>
#include <WriteOutput.h>



WriteOutput::WriteOutput()
{
}

void WriteOutput::init()
{
#if (defined(ASCD_MEGA_8X) || defined(ASCD_LEONARDO_4X)) 
    // --------------------------------------------------------------------------------------------------
    // ASCD Mega 8x

    for (byte i = 0; i < MODULES_COUNT; i++)
    {
        pinMode(chargeMosfetPins[i], OUTPUT);
        pinMode(dischargeMosfetPins[i], OUTPUT);
        dischargeMosfetOff(i);
        chargeMosfetOff(i);
    }
#elif defined(ASCD_NANO_4X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Nano 4x

    // Set pins to output so you can control the shift register
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    digitalWrite(latchPin, LOW);

    // FAN
    pinMode(FAN, OUTPUT);
    digitalWrite(FAN, LOW);

    // Set all pins to LOW
    for (byte i = 0; i < MODULES_COUNT; i++)
    {
        chargeMosfetOff(i);
        dischargeMosfetOff(i);
    } 
#endif
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
#if defined(ASCD_MEGA_8X)
    // --------------------------------------------------------------------------------------------------
    digitalWrite(arrayPin, (onOff) ? HIGH : LOW);
#elif defined(ASCD_NANO_4X)
    bitWrite(digitalPinsState, arrayPin, onOff);
    // Set the latchPin LOW
    digitalWrite(latchPin, LOW);
    // Shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, digitalPinsState);
    // Set the latchPin HIGH
    digitalWrite(latchPin, HIGH);
#endif
}

#if defined(ASCD_NANO_4X)
void WriteOutput::fanControl(bool onOff)
{
    digitalWrite(FAN, (onOff) ? HIGH : LOW);
}
#endif
