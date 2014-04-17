#include "level.hpp"
#include "basicBloc.hpp"
#include "messageEvent.hpp"
#include "spawnEnemyEvent.hpp"
#include "changeMapEvent.hpp"
#include "bossEnemy.hpp"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <iostream>

levelClass::levelClass()
{
    numberLevel = 0;
    maxLevel = numberFileLevel();
}

void levelClass::setLevel(std::list<eventClass*>& listEvent, std::list<characterClass*>& listEnemy, std::map<std::pair<int, int>, itemClass*>& mapLevel, int& endOfLevel, int& heightLevel, std::string& typeLevel, lightManagerClass& lightManager, int poseXPlayer)
{
    readLevel("level/" + nameCurrentLevel, listEvent, listEnemy, mapLevel, endOfLevel, heightLevel, typeLevel, poseXPlayer, lightManager);
}

bool levelClass::setNextLevel()
{
    if(++numberLevel > maxLevel || goodLevel() == false)
        return true;
    else
        return false;
}

void levelClass::readLevel(std::string nameLevel, std::list<eventClass*>& listEvent, std::list<characterClass*>& listEnemy, std::map<std::pair<int, int>, itemClass*>& mapLevel, int& endOfLevel, int& heightLevel, std::string& typeLevel, int poseXPlayer, lightManagerClass& lightManager)
{
    std::ifstream file(nameLevel.c_str());

    if(file.is_open())
    {
        std::string line;
        std::string typeLine = "END";
        spawnEnemyEventClass* tmpEventSpawn;
        changeMapEventClass* tmpChangeMap;
        while(std::getline(file, line))
        {
            if(line == "END")
            {
                if(typeLine == "SPAWN_ENEMY" || typeLine == "CHANGE_MAP")
                    typeLine = "EVENT";
                else
                    typeLine = "END";
            }
            if(typeLine == "MAP")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseX = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseY = line;
                mapLevel.insert(std::pair<std::pair<int, int>, itemClass*>(std::pair<int, int>(std::atoi(poseX.c_str()), std::atoi(poseY.c_str())), new basicBlocClass(name, std::atoi(poseX.c_str()), std::atoi(poseY.c_str()))));
            }
            else if(typeLine == "ENEMY")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseX = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseY = line;
                if(name == "BOSS")
                    listEnemy.push_back(new bossEnemyClass(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()), name));
                else
                    listEnemy.push_back(new basicEnemyClass(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()), name));
            }
            else if(typeLine == "EVENT")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                if(name == "MESSAGE")
                {
                    std::string poseX = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string poseY = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string width = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string height = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string message = line;
                    while(message.find("\\n") != std::string::npos)
                    {
                        message.replace(message.find("\\n"), 2, "\n");
                    }
                    if(std::atoi(poseX.c_str()) > poseXPlayer)
                    {
                        sf::RectangleShape surface;
                        surface.setPosition(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()));
                        surface.setSize(sf::Vector2f(std::atoi(width.c_str()), std::atoi(height.c_str())));
                        listEvent.push_back(new messageEventClass(message, surface));
                    }
                }
                else if(name == "SPAWN_ENEMY")
                {
                    std::string poseX = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string poseY = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string width = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string height = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string newPoseX = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string newPoseY = line;
                    sf::RectangleShape surface;
                    surface.setPosition(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()));
                    surface.setSize(sf::Vector2f(std::atoi(width.c_str()), std::atoi(height.c_str())));
                    tmpEventSpawn = new spawnEnemyEventClass(surface, std::atoi(newPoseX.c_str()), std::atoi(newPoseY.c_str()));
                    typeLine = "SPAWN_ENEMY";
                    listEvent.push_back(tmpEventSpawn);
                }
                else if(name == "CHANGE_MAP")
                {
                    std::string poseX = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string poseY = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string width = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string height = line;
                    sf::RectangleShape surface;
                    surface.setPosition(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()));
                    surface.setSize(sf::Vector2f(std::atoi(width.c_str()), std::atoi(height.c_str())));
                    tmpChangeMap = new changeMapEventClass(surface);
                    typeLine = "CHANGE_MAP";
                    listEvent.push_back(tmpChangeMap);
                }
            }
            else if(typeLine == "SPAWN_ENEMY")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseX = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseY = line;
                tmpEventSpawn->addToList(name, std::atoi(poseX.c_str()), std::atoi(poseY.c_str()));
            }
            else if(typeLine == "CHANGE_MAP")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseX = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseY = line;
                tmpChangeMap->addToList(name, std::atoi(poseX.c_str()), std::atoi(poseY.c_str()));
            }
            else if(typeLine == "LIGHT_WALL")
            {
                std::string poseXFirst = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseYFirst = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseXSecond = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseYSecond = line;
                lightManager.addWall(sf::Vector2f(atoi(poseXFirst.c_str()), atoi(poseYFirst.c_str())), sf::Vector2f(atoi(poseXSecond.c_str()), atoi(poseYSecond.c_str())));
            }
            else if(typeLine == "HEIGHT")
            {
                heightLevel = std::atoi(line.c_str());
            }
            else if(typeLine == "ENDOFLEVEL")
            {
                endOfLevel = std::atoi(line.c_str());
            }
            else if(typeLine == "TYPELEVEL")
            {
                typeLevel = line.c_str();
            }

            if(line == "MAP")
                typeLine = "MAP";
            else if(line == "ENEMY")
                typeLine = "ENEMY";
            else if(line == "EVENT")
                typeLine = "EVENT";
            else if(line == "LIGHT_WALL")
                typeLine = "LIGHT_WALL";
            else if(line == "HEIGHT")
                typeLine = "HEIGHT";
            else if(line == "ENDOFLEVEL")
                typeLine = "ENDOFLEVEL";
            else if(line == "TYPELEVEL")
                typeLine = "TYPELEVEL";
        }
        file.close();
    }
}

void levelClass::readLevelEdit(std::string nameLevel, std::list<infoEvent>& listEvent, std::list<characterClass*>& listEnemy, std::map<std::pair<int, int>, itemClass*>& mapLevel, int& endOfLevel, int& heightLevel, std::string& typeLevel)
{
    std::ifstream file(nameLevel.c_str());

    if(file.is_open())
    {
        std::string line;
        std::string typeLine = "END";
        while(std::getline(file, line))
        {
            if(line == "END")
            {
                if(typeLine == "SPAWN_ENEMY" || typeLine == "CHANGE_MAP")
                    typeLine = "EVENT";
                else
                    typeLine = "END";
            }
            if(typeLine == "MAP")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseX = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseY = line;
                mapLevel.insert(std::pair<std::pair<int, int>, itemClass*>(std::pair<int, int>(std::atoi(poseX.c_str()), std::atoi(poseY.c_str())), new basicBlocClass(name, std::atoi(poseX.c_str()), std::atoi(poseY.c_str()))));
            }
            else if(typeLine == "ENEMY")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseX = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseY = line;
                if(name == "BOSS")
                    listEnemy.push_back(new bossEnemyClass(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()), name));
                else
                    listEnemy.push_back(new basicEnemyClass(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()), name));
            }
            else if(typeLine == "EVENT")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                if(name == "MESSAGE")
                {
                    std::string poseX = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string poseY = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string width = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string height = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string message = line;
                    while(message.find("\\n") != std::string::npos)
                    {
                        message.replace(message.find("\\n"), 2, "&n");
                    }
                    infoEvent tmp;
                    sf::RectangleShape surface;
                    surface.setPosition(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()));
                    surface.setSize(sf::Vector2f(std::atoi(width.c_str()), std::atoi(height.c_str())));
                    surface.setFillColor(sf::Color::Cyan);
                    tmp.name = "MESSAGE";
                    tmp.surface = surface;
                    tmp.valX = 0;
                    tmp.valY = 0;
                    tmp.action.push_back(message);
                    listEvent.push_back(tmp);
                }
                else if(name == "SPAWN_ENEMY")
                {
                    std::string poseX = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string poseY = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string width = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string height = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string newPoseX = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string newPoseY = line;
                    sf::RectangleShape surface;
                    surface.setPosition(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()));
                    surface.setSize(sf::Vector2f(std::atoi(width.c_str()), std::atoi(height.c_str())));
                    surface.setFillColor(sf::Color::Cyan);
                    infoEvent tmp;
                    tmp.name = "SPAWN_ENEMY";
                    tmp.surface = surface;
                    tmp.valX = std::atoi(newPoseX.c_str());
                    tmp.valY = std::atoi(newPoseY.c_str());
                    typeLine = "SPAWN_ENEMY";
                    listEvent.push_back(tmp);
                }
                else if(name == "CHANGE_MAP")
                {
                    std::string poseX = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string poseY = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string width = line.substr(0, line.find(' '));
                    line.erase(0, line.find(' ') + 1);
                    std::string height = line;
                    sf::RectangleShape surface;
                    surface.setPosition(std::atoi(poseX.c_str()), std::atoi(poseY.c_str()));
                    surface.setSize(sf::Vector2f(std::atoi(width.c_str()), std::atoi(height.c_str())));
                    surface.setFillColor(sf::Color::Cyan);
                    infoEvent tmp;
                    tmp.name = "CHANGE_MAP";
                    tmp.surface = surface;
                    tmp.valX = 0;
                    tmp.valY = 0;
                    typeLine = "CHANGE_MAP";
                    listEvent.push_back(tmp);
                }
            }
            else if(typeLine == "SPAWN_ENEMY")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseX = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseY = line;
                listEvent.back().action.push_back(name + " " + poseX + " " + poseY);
            }
            else if(typeLine == "CHANGE_MAP")
            {
                std::string name = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseX = line.substr(0, line.find(' '));
                line.erase(0, line.find(' ') + 1);
                std::string poseY = line;
                listEvent.back().action.push_back(name + " " + poseX + " " + poseY);
            }
            else if(typeLine == "HEIGHT")
            {
                heightLevel = std::atoi(line.c_str());
            }
            else if(typeLine == "ENDOFLEVEL")
            {
                endOfLevel = std::atoi(line.c_str());
            }
            else if(typeLine == "TYPELEVEL")
            {
                typeLevel = line.c_str();
            }

            if(line == "MAP")
                typeLine = "MAP";
            else if(line == "ENEMY")
                typeLine = "ENEMY";
            else if(line == "EVENT")
                typeLine = "EVENT";
            else if(line == "HEIGHT")
                typeLine = "HEIGHT";
            else if(line == "ENDOFLEVEL")
                typeLine = "ENDOFLEVEL";
            else if(line == "TYPELEVEL")
                typeLine = "TYPELEVEL";
        }
    file.close();
    }
}

int levelClass::numberFileLevel()
{
    int i = 0;
    DIR* directory = NULL;
    struct dirent* file = NULL;
    directory = opendir("level");

    if(directory != NULL)
    {
        while((file = readdir(directory)) != NULL)
        {
            ++i;
        }
    }

    closedir(directory);
    return i - 2;
}

bool levelClass::goodLevel()
{
    std::ostringstream oss;
    oss << numberLevel;
    bool match = true;
    std::ostringstream tmp;

    DIR* directory = NULL;
    struct dirent* file = NULL;
    directory = opendir("level");
    if(directory != NULL)
    {
        while((file = readdir(directory)) != NULL)
        {
            match = true;
            tmp.str("");
            tmp << file->d_name;
            size_t i;
            for(i = 0; i < oss.str().size(); ++i)
            {
                if(tmp.str().size() > i)
                {
                    if(oss.str().at(i) != tmp.str().at(i))
                    {
                        match = false;
                        break;
                    }
                }
                else
                {
                    match = false;
                    break;
                }
            }
            ++i;
            if(tmp.str().size() > i)
            {
                if(tmp.str().at(i) >= '0' && tmp.str().at(i) <= '9')
                {
                    match = false;
                }
            }

            if(match == true)
            {
                break;
            }
        }
    }
    closedir(directory);

    if(match == true)
    {
        nameCurrentLevel = tmp.str();
    }

    return match;
}

int levelClass::getNumberLevel() const
{
    return numberLevel;
}

bool levelClass::setNumberLevel(int val)
{
    numberLevel = val;
    if(numberLevel > maxLevel || goodLevel() == false)
        return true;
    else
        return false;
}
