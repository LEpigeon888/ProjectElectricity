#ifndef MESSAGEEVENT_HPP
#define MESSAGEEVENT_HPP

#include "gameStateStack.hpp"
#include "event.hpp"

class messageEventClass : public eventClass
{
public:
    messageEventClass(std::string newMessage, sf::RectangleShape& newSurface);
    bool action(gamePlayedClass* gamePlayed);
private:
    std::string message;
};

#endif

