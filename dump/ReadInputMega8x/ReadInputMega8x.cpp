#include <Variables.h>
#include <ReadInputMega8x.h>
ReadInput::ReadInput()
{
  init();
}

void ReadInput::init()
{
  // Pin Initialization
  for (byte i = 0; i < 8; i++)
  {
    pinMode(batteryVoltagePin[i], INPUT);     // Analog reading of the Battery positive terminal
    pinMode(batteryVoltageDropPin[i], INPUT); // Analog reading discharge resistor Battery positive terminal
    pinMode(chargeLedPin[i], INPUT_PULLUP);   // Charge LED Digital reading from TP4056
  }
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
  return (digitalRead(chargeLedPin[module]) == HIGH) ? true : false;
  // if (digitalRead(chargeLedPin[module]) == HIGH)
  // {
  //   return true;
  // }
  // else
  // {
  //   return false;
  // }
}

float ReadInput::getInput(const byte arrayPin)
{
  // Read the value at the SIG pin 10x and convert to voltage
  float batterySampleVoltage = 0.00;
  for (byte i = 0; i < 10; i++)
  {
    if (useReferenceVoltage == true)
    {
      batterySampleVoltage = batterySampleVoltage + (analogRead(arrayPin) * (referenceVoltage) / 1023.0);
    }
    else
    {
      batterySampleVoltage = batterySampleVoltage + (analogRead(arrayPin) * (readVcc()));
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

bool ReadInput::batteryCheck(byte module)
{
  return (batteryVoltage(module) <= batteryVoltageLeak) ? false : true;
  /*
  static byte countVoltDrop;
  module[j].batteryVoltage = readVoltage(module[j].batteryVolatgePin);
  if (module[j].batteryVoltage <= settings.batteryVolatgeLeak)
  {
    return false;
  }
  else
  {
    if (module[j].batteryLastVoltage - module[j].batteryVoltage >= 0.1)
    {
      if (countVoltDrop > 2)
      {
        digitalWrite(module[j].chargeMosfetPin, LOW);  // Turn off TP4056
        digitalWrite(module[j].chargeMosfetPin, HIGH); // Turn on TP4056
        digitalWrite(module[j].chargeMosfetPin, LOW);  // Turn off TP4056
        module[j].batteryVoltage = readVoltage(module[j].batteryVolatgePin);
        countVoltDrop = 0;
      }
      else
      {
        countVoltDrop++;
      }
    }
    module[j].batteryLastVoltage = module[j].batteryVoltage;
    return true;
  }
  */
}

