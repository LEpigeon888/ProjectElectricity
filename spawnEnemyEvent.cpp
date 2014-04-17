#include "spawnEnemyEvent.hpp"
#include "basicEnemy.hpp"
#include "bossEnemy.hpp"

spawnEnemyEventClass::spawnEnemyEventClass(sf::RectangleShape& newSurface, int newPoseX, int newPoseY)
{
    surface = newSurface;
    poseX = newPoseX;
    poseY = newPoseY;
    first = false;
    type = "SPAWN_ENEMY";
}

void spawnEnemyEventClass::addToList(std::string name, int x, int y)
{
    typeSpawnEnemy tempEnemy;
    tempEnemy.x = x;
    tempEnemy.y = y;
    tempEnemy.name = name;
    listEnemy.push_back(tempEnemy);
}

bool spawnEnemyEventClass::action(gamePlayedClass* gamePlayed)
{
    if(!first)
    {
        surface.setPosition(0, 0);
        surface.setSize(sf::Vector2f(gamePlayed->getCamera().getCenter().x + 320, gamePlayed->getCamera().getCenter().y + 240));
        first = true;
    }
    if(listEnemy.empty())
        return true;
    if(gamePlayed->getCamera().getCenter().x == poseX && gamePlayed->getCamera().getCenter().y == poseY)
    {
        while(!listEnemy.empty())
        {
            if(listEnemy.front().name == "WAIT")
            {
                listEnemy.pop_front();
                return false;
            }
            if(listEnemy.front().name == "BOSS")
            {
                gamePlayed->getListActiveEnemy().push_front(new bossEnemyClass(listEnemy.front().x, listEnemy.front().y, listEnemy.front().name));
                listEnemy.pop_front();
                continue;
            }
            gamePlayed->getListActiveEnemy().push_back(new basicEnemyClass(listEnemy.front().x, listEnemy.front().y, listEnemy.front().name));
            listEnemy.pop_front();
        }
    }
    return false;
}
