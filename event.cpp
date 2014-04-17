#include "event.hpp"

const sf::RectangleShape& eventClass::getSurface()
{
    return surface;
}

const std::string& eventClass::getType()
{
    return type;
}

int eventClass::getPoseX()
{
    return poseX;
}

int eventClass::getPoseY()
{
    return poseY;
}
