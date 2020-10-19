// #include <Config.h>

#include <CycleTimer.h>

CycleTimer::CycleTimer()
{
}

void CycleTimer::updateTimer(byte module)
{
    hours[module] = (millis() - millisCleared[module]) / (3600000L);
    minutes[module] = ((millis() - millisCleared[module]) % (3600000L)) / (60000L);
    seconds[module] = ((millis() - millisCleared[module]) % (3600000L) % (60000L)) / 1000;
}

void CycleTimer::clearTimer(byte module)
{
    millisCleared[module] = millis();
    seconds[module] = 0;
    minutes[module] = 0;
    hours[module] = 0;
}

byte CycleTimer::getSeconds(byte module)
{
    return seconds[module];
}

byte CycleTimer::getMinutes(byte module)
{
    return minutes[module];
}

byte CycleTimer::getHours(byte module)
{
    return hours[module];
}

byte CycleTimer::getLCDActiveModule()
{
    return moduleActiveLCD;
}

bool CycleTimer::getSerialCycleReady()
{
    return serialCycleReady;
}

void CycleTimer::setLCDActiveModule()
{
    if (lockActiveLCD)
    {
        lockActiveLCDCount = 0;
        if (moduleActiveLCD == (MODULES_COUNT - 1))
        {
            moduleActiveLCD = 0;
        }
        else
        {
            moduleActiveLCD++;
        }
    }
    lockActiveLCD = true;
}

void CycleTimer::LCDCycle()
{

    if ((millis() - LCDCycleMillis) >= (config.screenTime * 1000))
    {
        LCDCycleMillis = millis();
        if (lockActiveLCD)
        {
            if ((60 / config.screenTime) >= lockActiveLCDCount)
            {
                lockActiveLCDCount++;
            }
            else
            {
                lockActiveLCDCount = 0;
                lockActiveLCD = false;
            }
        }
        else
        {
            if (moduleActiveLCD == (MODULES_COUNT - 1))
            {
                moduleActiveLCD = 0;
            }
            else
            {
                moduleActiveLCD++;
            }
        }
    }
    // moduleActiveLCD = 3; // override to lock screen for testing
}

bool CycleTimer::buttonCycle()
{
    if ((millis() - buttonCycleMillis) >= 5)
    {
        buttonCycleMillis = millis();
        return true;
    }
    else
    {
        return false;
    }
}

bool CycleTimer::mainCycle()
{
    if ((millis() - mainCycleMillis) >= 1000)
    {
        mainCycleMillis = millis();
        return true;
    }
    else
    {
        return false;
    }
}

#if defined(ONLINE)
void CycleTimer::serialCycle()
{
    if ((millis() - serialCycleMillis) >= 4000)
    {
        serialCycleMillis = millis();
        serialCycleReady = true;
    }
    else
    {
        serialCycleReady = false;
    }
}
#endif
