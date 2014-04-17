#ifndef SPAWNENEMYEVENT_HPP
#define SPAWNENEMYEVENT_HPP

#include "gameStateStack.hpp"
#include "character.hpp"
#include "event.hpp"
#include "gamePlayed.hpp"

struct typeSpawnEnemy
{
    int x;
    int y;
    std::string name;
};

class spawnEnemyEventClass : public eventClass
{
public:
    spawnEnemyEventClass(sf::RectangleShape& newSurface, int newPoseX, int newPoseY);
    void addToList(std::string name, int x, int y);
    bool action(gamePlayedClass* gamePlayed);
private:
    bool first;
    std::list<typeSpawnEnemy> listEnemy;
};

#endif


