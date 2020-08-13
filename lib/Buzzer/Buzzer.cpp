#include <Buzzer.h>
Buzzer::Buzzer()
{
}

void Buzzer::init()
{
    // buzzerStart();
}

void Buzzer::buzzerStart()
{
    for (int i = 500; i < 3000; i += 300)
    {
        tone(BUZZ, i, 75);
        delay(100);
    }
}

void Buzzer::buzzerFinished()
{
    for (int i = 500; i < 3000; i += 300)
    {
        tone(BUZZ, i, 30);
        delay(50);
    }
}

void Buzzer::buzzerKeyPress()
{
    tone(BUZZ, 2000, 50);
}



