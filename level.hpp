#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <map>
#include "event.hpp"
#include "basicEnemy.hpp"
#include "item.hpp"
#include "lightManager.hpp"

struct infoEvent
{
    std::string name;
    sf::RectangleShape surface;
    int valX;
    int valY;
    std::list<std::string> action;
};

class levelClass
{
public:
    levelClass();
    void setLevel(std::list<eventClass*>& listEvent, std::list<characterClass*>& listEnemy, std::map<std::pair<int, int>, itemClass*>& mapLevel, int& endOfLevel, int& heightLevel, std::string& typeLevel, lightManagerClass& lightManager, int poseXPlayer = 0);
    bool setNextLevel();
    void readLevel(std::string nameLevel, std::list<eventClass*>& listEvent, std::list<characterClass*>& listEnemy, std::map<std::pair<int, int>, itemClass*>& mapLevel, int& endOfLevel, int& heightLevel, std::string& typeLevel, int poseXPlayer, lightManagerClass& lightManager);
    void readLevelEdit(std::string nameLevel, std::list<infoEvent>& listEvent, std::list<characterClass*>& listEnemy, std::map<std::pair<int, int>, itemClass*>& mapLevel, int& endOfLevel, int& heightLevel, std::string& typeLevel);
    int numberFileLevel();
    bool goodLevel();
    int getNumberLevel() const;
    bool setNumberLevel(int val);
private:
    int numberLevel;
    int maxLevel;
    std::string nameCurrentLevel;
};

#endif
