// #include "Config.h"

#include <Arduino.h>
#include <CycleFunctions.h>



Cycle cycle;

void setup()
{
    cycle.init();
}

void loop()
{
    cycle.cycleRun();
}