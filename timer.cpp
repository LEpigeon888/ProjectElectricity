#include "timer.hpp"
#include "global.hpp"

void timerClass::start()
{
    time = 0;
}

void timerClass::update()
{
    time += globalClass::getTimeFrame();
}

double timerClass::getTime()
{
    return time;
}
