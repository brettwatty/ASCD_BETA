#include <InitialiseSetup.h>
#include <Variables.h>
#include <OutputLCD.h>
#include <TemperatureControl.h>

CustomSettings settings;
BoardVariables boardVariables;

#define ASCD_NANO_4X
// #define ASCD_MEGA_8X

#ifdef ASCD_MEGA_8X
Modules module[NUMBER_MODULES] =
    {
        {A0, A1, 23, 22, 24},
        {A2, A3, 26, 25, 27},
        {A4, A5, 29, 28, 30},
        {A6, A7, 32, 31, 33},
        {A8, A9, 35, 34, 36},
        {A10, A11, 38, 37, 39},
        {A12, A13, 41, 40, 42},
        {A14, A15, 44, 43, 45}};
#else
Modules module[NUMBER_MODULES]; /*= {{{1, 1, 0, 1}, {1, 1, 1, 1}, {0, 1, 0, 1}, 0, 1}, 
{{1, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 1}, 2, 3}, 
{{1, 1, 1, 0}, {1, 0, 1, 1}, {0, 1, 1, 0}, 4, 5}, 
{{1, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 1, 0}, 6, 7}};
*/

// module[0].chargeMosfetPin = 0;
// module[0].chargeMosfetPin = 2;
// module[0].chargeMosfetPin = 4;
// module[0].chargeMosfetPin = 6;

#endif

initialiseSetup::initialiseSetup()
{
}

void initialiseSetup::init()
{
    //Initialize Serial
    Serial.begin(115200);
    Serial.setTimeout(5);

    outputLCD OutputLCD;
#ifdef ASCD_MEGA_8X
    #define ESP8266 Serial1
    OutputLCD.startup(0);
    for (byte i = 0; i < NumberModules; i++)
    {
        // pinMode(module[i].chargeLedPin, INPUT_PULLUP);
        // pinMode(module[i].chargeMosfetPin, OUTPUT);
        // pinMode(module[i].dischargeMosfetPin, OUTPUT);
        // digitalWrite(module[i].chargeMosfetPin, LOW);
        // digitalWrite(module[i].dischargeMosfetPin, LOW);
    }
    pinMode(boardVariables.BTN, INPUT_PULLUP); // Pin 5 Rotary Encoder Button (BTN)
#else
    // Set pins to output so you can control the shift register
    pinMode(boardVariables.latchPin, OUTPUT);
    pinMode(boardVariables.clockPin, OUTPUT);
    pinMode(boardVariables.dataPin, OUTPUT);
    digitalWrite(boardVariables.latchPin, LOW);

    // MUX Initialization
    pinMode(boardVariables.S0, OUTPUT);
    pinMode(boardVariables.S1, OUTPUT);
    pinMode(boardVariables.S2, OUTPUT);
    pinMode(boardVariables.S3, OUTPUT);
    digitalWrite(boardVariables.S0, LOW);
    digitalWrite(boardVariables.S1, LOW);
    digitalWrite(boardVariables.S2, LOW);
    digitalWrite(boardVariables.S3, LOW);

    // Button
    pinMode(boardVariables.BTN, INPUT);

    // Buzzer
    pinMode(boardVariables.BUZZ, OUTPUT);
    digitalWrite(boardVariables.BUZZ, HIGH);
    delay(50);
    digitalWrite(boardVariables.BUZZ, LOW);

    // FAN
    pinMode(boardVariables.FAN, OUTPUT);
    OutputLCD.startup(0);
    // Set All Digital Outputs on the Shift Register to LOW
    for (byte i = 0; i < settings.getModulesCount(); i++)
    {
        digitalWrite(boardVariables.FAN, HIGH); // Fan On
        // digitalSwitch(module[i].chargeMosfetPin, 1);
        delay(500);
        // digitalSwitch(module[i].chargeMosfetPin, 0);
        delay(500);
        // readMux(module[i].batteryVoltagePin); // Read each batteryVoltagePin to pre pull down voltage to 0.00v
        // digitalSwitch(module[i].dischargeMosfetPin, 1);
        digitalWrite(boardVariables.FAN, LOW); // Fan Off
        delay(500);
        // digitalSwitch(module[i].dischargeMosfetPin, 0);
        delay(500);
    }
    OutputLCD.startup(1);
#endif
    //Initialize Software Serial for communication with the ESP8266
    // ESP8266.begin(38400);
    // ESP8266.setTimeout(5);
    // Create an ESP class
    TemperatureControl temperatureControl;
}
