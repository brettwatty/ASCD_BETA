#include <Variables.h>
#include <ReadInputNano4x.h>
ReadInput::ReadInput()
{
    init();
}

void ReadInput::init()
{
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
}

float ReadInput::batteryVoltage(byte module)
{
    return getInput(batteryVoltagePin[module]);
}

float ReadInput::batteryVoltageDrop(byte module)
{
    return getInput(batteryVoltageDropPin[module]);
}

bool ReadInput::chargeLed(byte module)
{
    return (getInput(chargeLedPin[module]) >= chargeLedPinMidVoltage[module]) ? true : false;
}

float ReadInput::getInput(const bool arrayPins[])
{
    const byte controlPin[] = {S0, S1, S2, S3};

    // Loop through the 4 sig
    for (byte i = 0; i < 4; i++)
    {
        digitalWrite(controlPin[i], arrayPins[i]);
    }
    // Read the value at the SIG pin 10x and convert to voltage
    float batterySampleVoltage = 0.00;
    for (byte i = 0; i < 10; i++)
    {
        if (useReferenceVoltage == true)
        {
            batterySampleVoltage = batterySampleVoltage + (analogRead(SIG) * (referenceVoltage) / 1023.0);
        }
        else
        {
            batterySampleVoltage = batterySampleVoltage + (analogRead(SIG) * (readVcc()));
        }
    }
    return batterySampleVoltage / 10; // Calculate and return the Voltage Reading
}

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
    return ((internalReferenceVoltage * 1024) / result) / 1023.0; // Calculate Vcc (in Volts) = (((Internal Voltage reference 1.1) * 1024) / result) / 1023
}

