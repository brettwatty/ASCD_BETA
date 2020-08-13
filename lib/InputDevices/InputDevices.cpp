#include <InputDevices.h>
#include <Variables.h>
#if defined(ASCD_MEGA_8X)

#elif defined(ASCD_NANO_4X)

#endif

InputDevices::InputDevices()
{
}

void InputDevices::init()
{
    // Button
    pinMode(BTN, BUTTON_INPUT_MODE);

#if defined(ASCD_MEGA_8X)

#endif
}

bool InputDevices::button()
{
    bool buttonState = 0;
    bool buttonReturn = 0;
    buttonState = digitalRead(BTN);
    if (buttonState != lastButtonState)
    {
        if (buttonState == BUTTON_H_L)
        {
            buttonReturn = true;
        }
        else
        {
            buttonReturn = false;
        }
    }
    lastButtonState = buttonState;
    return buttonReturn;
}