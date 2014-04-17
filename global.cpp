#include "global.hpp"

sf::Clock globalClass::timer;
sf::Font globalClass::font;
double globalClass::timeFrame = 0.015625;
bool globalClass::smoothLighting = true;

sf::Clock& globalClass::getTimer()
{
    return timer;
}

double& globalClass::getTimeFrame()
{
    return timeFrame;
}

sf::Font& globalClass::getFont()
{
    return font;
}

bool& globalClass::getSmoothLighting()
{
    return smoothLighting;
}
