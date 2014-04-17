#include "messageEvent.hpp"
#include "dialogueState.hpp"
#include "gamePlayed.hpp"

messageEventClass::messageEventClass(std::string newMessage, sf::RectangleShape& newSurface)
{
    message = newMessage;
    surface = newSurface;
    type = "MESSAGE";
}

bool messageEventClass::action(gamePlayedClass* gamePlayed)
{
    gamePlayed->getGameStateStack()->add(new dialogueStateClass(message));
    return true;
}
