#include "changeMapEvent.hpp"
#include "basicBloc.hpp"

changeMapEventClass::changeMapEventClass(sf::RectangleShape& newSurface)
{
    surface = newSurface;
    type = "CHANGE_MAP";
}

void changeMapEventClass::addToList(std::string name, int x, int y)
{
    typeChangeItem tempItem;
    tempItem.x = x;
    tempItem.y = y;
    tempItem.name = name;
    listItem.push_back(tempItem);
}

bool changeMapEventClass::action(gamePlayedClass* gamePlayed)
{
    while(!listItem.empty())
    {
        if(gamePlayed->getMapLevel().find(std::pair<int, int>(listItem.front().x, listItem.front().y)) != gamePlayed->getMapLevel().end())
        {
            delete gamePlayed->getMapLevel().find(std::pair<int, int>(listItem.front().x, listItem.front().y))->second;
            gamePlayed->getMapLevel().erase(std::pair<int, int>(listItem.front().x, listItem.front().y));
        }
        if(listItem.front().name != "ERASE")
        {
        gamePlayed->getMapLevel().insert(std::pair<std::pair<int, int>, itemClass*>(std::pair<int, int>(listItem.front().x, listItem.front().y), new basicBlocClass(listItem.front().name, listItem.front().x, listItem.front().y)));
        }
        listItem.pop_front();
    }
    return true;
}

