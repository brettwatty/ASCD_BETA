// #include <Config.h>
#include <ReadInput.h>

ReadInput::ReadInput()
{
#if defined(ASCD_NANO_4X)

#endif
}

void ReadInput::init()
{
#if defined(ASCD_MEGA_8X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Mega 8x
    // Pin Initialization
    for (byte i = 0; i < MODULES_COUNT; i++)
    {
        pinMode(batteryVoltagePin[i], INPUT);     // Analog reading of the Battery positive terminal
        pinMode(batteryVoltageDropPin[i], INPUT); // Analog reading discharge resistor Battery positive terminal
        pinMode(chargeLedPin[i], INPUT_PULLUP);   // Charge LED Digital reading from TP4056
    }
#elif defined(ASCD_NANO_4X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Nano 4x
    // MUX Initialization
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    pinMode(SIG, INPUT); // Analog Mux SIG pin A0

#elif defined(ASCD_LEONARDO_4X)
    for (byte i = 0; i < MODULES_COUNT; i++)
    {
        pinMode(chargeLedPin[i], INPUT_PULLUP);
    }
#endif
}

int ReadInput::batteryVoltage(byte module)
{
    return getInput(batteryVoltagePin[module]);
}

int ReadInput::batteryVoltageDrop(byte module)
{
    return getInput(batteryVoltageDropPin[module]);
}

int ReadInput::chargeLedVoltage(byte module)
{
    return getInput(chargeLedPin[module]);
}

bool ReadInput::chargeLed(byte module)
{
#if defined(ASCD_MEGA_8X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Mega 8x
    return (digitalRead(chargeLedPin[module]) == HIGH) ? true : false;
#elif defined(ASCD_NANO_4X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Nano 4x
    return (getInput(chargeLedPin[module]) >= config.chargeLedPinMidVoltage[module]) ? true : false;
#elif defined(ASCD_LEONARDO_4X)
    // --------------------------------------------------------------------------------------------------
    // ASCD Leonardo 4x
    return true; // temp placement
#endif
}

#if defined(ASCD_MEGA_8X)
int ReadInput::getInput(const byte arrayPin)
{
    // --------------------------------------------------------------------------------------------------
    // ASCD Mega 8x
    // Read the value at the SIG pin 10x and convert to voltage
    unsigned int batterySampleVoltage = 0;
    for (byte i = 0; i < 10; i++)
    {
        if (config.useReferenceVoltage)
        {
            batterySampleVoltage = batterySampleVoltage + (analogRead(arrayPin) * (long)config.referenceVoltage / 1023.0);
        }
        else
        {
            batterySampleVoltage = batterySampleVoltage + (analogRead(arrayPin) * (readVcc()));
        }
    }

    return batterySampleVoltage / 10; // Calculate and return the Voltage Reading
}
#elif defined(ASCD_NANO_4X)
// --------------------------------------------------------------------------------------------------
// ASCD Nano 4x
int ReadInput::getInput(const bool arrayPins[])
{
    unsigned int batterySampleVoltage = 0;
    const byte controlPin[] = {S0, S1, S2, S3};

    // Loop through the 4 sig
    for (byte i = 0; i < 4; i++)
    {
        digitalWrite(controlPin[i], arrayPins[i]);
    }
    // Read the value at the SIG pin 10x and convert to voltage

    for (byte i = 0; i < 10; i++)
    {
        if (config.useReferenceVoltage)
        {
            batterySampleVoltage = batterySampleVoltage + (analogRead(SIG) * (long)config.referenceVoltage / 1023);
        }
        else
        {
            batterySampleVoltage = batterySampleVoltage + (analogRead(SIG) * readVcc() * 1000);
        }
    }
    return batterySampleVoltage / 10; // Calculate and return the Voltage Reading
}
#elif defined(ASCD_LEONARDO_4X)
int ReadInput::getInput(const byte arrayPin)
{
    unsigned int batterySampleVoltage = 42; // temp need ADS function to read volatge
    return batterySampleVoltage / 10; // Calculate and return the Voltage Reading
}
#endif

float ReadInput::readVcc()
{
    long result;
    // Read 1.1V reference against AVcc
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
#else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
#if defined(__AVR_ATmega2560__)
    ADCSRB &= ~_BV(MUX5); // Without this the function always returns -1 on the ATmega2560
#endif
    delay(2);            // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC))
        ;
    result = ADCL;
    result |= ADCH << 8;
    return (((config.internalReferenceVoltage / 1000.0) * 1024) / result) / 1023.0; // Calculate Vcc (in Volts) = (((Internal Voltage reference 1.1) * 1024) / result) / 1023
}