#ifndef CHANGEEVENT_HPP
#define CHANGEEVENT_HPP

#include "gameStateStack.hpp"
#include "item.hpp"
#include "event.hpp"
#include "gamePlayed.hpp"

struct typeChangeItem
{
    int x;
    int y;
    std::string name;
};

class changeMapEventClass : public eventClass
{
public:
    changeMapEventClass(sf::RectangleShape& newSurface);
    void addToList(std::string name, int x, int y);
    bool action(gamePlayedClass* gamePlayed);
private:
    std::list<typeChangeItem> listItem;
};

#endif
