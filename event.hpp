#ifndef EVENT_HPP
#define EVENT_HPP

#include "gameStateStack.hpp"

class gamePlayedClass;

class eventClass
{
public:
    virtual ~eventClass() {};
    const sf::RectangleShape& getSurface();
    int getPoseX();
    int getPoseY();
    const std::string& getType();
    virtual bool action(gamePlayedClass* gamePlayed) = 0;
protected:
    sf::RectangleShape surface;
    int poseY;
    int poseX;
    std::string type;
};

#endif
