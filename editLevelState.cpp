#include "editLevelState.hpp"
#include "basicBloc.hpp"
#include "sprite.hpp"
#include "mainMenuState.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

editLevelStateClass::~editLevelStateClass()
{
    window->setKeyRepeatEnabled(false);
}

void editLevelStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
    window->setView(window->getDefaultView());
    font.loadFromFile("cour.ttf");
    heightLevel = 480;
    endOfLevel = 640;
    camera.setSize(640, 480);
    camera.setCenter(320, heightLevel - 240);
    border.setPosition(0, 0);
    border.setSize(sf::Vector2f(640, 40));
    border.setFillColor(sf::Color::Black);
    backgroundText.setSize(sf::Vector2f(640, 40));
    backgroundText.setPosition(0, 220);
    backgroundText.setFillColor(sf::Color::White);
    backgroundText.setOutlineThickness(5.f);
    backgroundText.setOutlineColor(sf::Color::Black);
    numberItem = 0;
    tool = 0;
    maxInTool = 10;
    firstClick = true;
    item.setTexture(spriteClass::getImage("skinItem"));
    item.setPosition(10, 10);
    setItemTexture();
    window->setKeyRepeatEnabled(true);
    textEntered = false;
    typeTextEntered = "NONE";
    spritePlayer.setTexture(spriteClass::getImage("player"));
    spritePlayer.setTextureRect(sf::IntRect(82, 81, 40, 80));
    spritePlayer.setPosition(50.f, heightLevel - 80.f);
}

void editLevelStateClass::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if((event.type == sf::Event::Closed))
        {
            window->close();
            break;
        }
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            deleteLevel();
            parent->set(new mainMenuStateClass);
            return;
        }
        if(textEntered == false)
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Add)
                {
                    if(++numberItem > maxInTool)
                    {
                        numberItem = 0;
                    }
                    setItemTexture();
                }
                else if(event.key.code == sf::Keyboard::Subtract)
                {
                    if(--numberItem < 0)
                    {
                        numberItem = maxInTool;
                    }
                    setItemTexture();
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    camera.move(0, -10);
                    if(camera.getCenter().y - 200 < 0)
                        camera.setCenter(camera.getCenter().x, 200);
                }
                else if(event.key.code == sf::Keyboard::Down)
                {
                    camera.move(0, 10);
                    if(camera.getCenter().y + 240 > heightLevel)
                        camera.setCenter(camera.getCenter().x, heightLevel - 240);
                }
                else if(event.key.code == sf::Keyboard::Left)
                {
                    camera.move(-10, 0);
                    if(camera.getCenter().x - 320 < 0)
                        camera.setCenter(320, camera.getCenter().y);
                }
                else if(event.key.code == sf::Keyboard::Right)
                {
                    camera.move(10, 0);
                    if(camera.getCenter().x + 320 > endOfLevel)
                        camera.setCenter(endOfLevel - 320, camera.getCenter().y);
                }
                else if(event.key.code == sf::Keyboard::Num1 && tool < 50)
                {
                    tool = 0;
                    maxInTool = 10;
                    numberItem = 0;
                    setItemTexture();
                }
                else if(event.key.code == sf::Keyboard::Num2 && tool < 50)
                {
                    tool = 1;
                    maxInTool = 5;
                    numberItem = 0;
                    setItemTexture();
                }
                else if(event.key.code == sf::Keyboard::Num3 && tool < 50)
                {
                    tool = 2;
                    maxInTool = 2;
                    numberItem = 0;
                    setItemTexture();
                }
                else if(event.key.code == sf::Keyboard::Num4 && tool < 50)
                {
                    tool = 3;
                    maxInTool = 0;
                    numberItem = 0;
                    setItemTexture();
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed && (event.mouseButton.button == sf::Mouse::Left))
            {
                if(tool == 2)
                {
                    if(numberItem == 0)
                    {
                        if(firstClick)
                        {
                                while(!tmpInfoEvent.action.empty())
                                {
                                    tmpInfoEvent.action.pop_back();
                                }
                                tmpInfoEvent.valX = 0;
                                tmpInfoEvent.valY = 0;
                                tmpInfoEvent.surface.setPosition(sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320, sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240);
                                tmpInfoEvent.surface.setFillColor(sf::Color::Cyan);
                                tmpInfoEvent.name = nameOfItem;
                                firstClick = false;
                        }
                        else
                        {
                            int tmpWidth = sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320 - tmpInfoEvent.surface.getPosition().x;
                            if(tmpWidth < 5)
                            {
                                tmpWidth = 5;
                            }
                            int tmpHeight = sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240 - tmpInfoEvent.surface.getPosition().y;
                            if(tmpHeight < 5)
                            {
                                tmpHeight = 5;
                            }
                            tmpInfoEvent.surface.setSize(sf::Vector2f(tmpWidth, tmpHeight));
                            std::list<infoEvent>::iterator j;
                            for(j = listEvent.begin(); j != listEvent.end(); ++j)
                            {
                                if(j->surface.getPosition().x > tmpInfoEvent.surface.getPosition().x)
                                {
                                    poseCurrentEvent = listEvent.insert(j, tmpInfoEvent);
                                    break;
                                }
                            }
                            if(j == listEvent.end())
                            {
                                poseCurrentEvent = listEvent.insert(j, tmpInfoEvent);
                            }
                            typeTextEntered = "MESSAGE";
                            textEntered = true;
                            stringTextEntered.erase(0);
                            firstClick = true;
                        }
                    }
                    else if(numberItem == 1)
                    {
                        if(firstClick)
                        {
                            while(!tmpInfoEvent.action.empty())
                            {
                                tmpInfoEvent.action.pop_back();
                            }
                            tmpInfoEvent.valX = 0;
                            tmpInfoEvent.valY = 0;
                            tmpInfoEvent.surface.setPosition(sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320, sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240);
                            tmpInfoEvent.surface.setFillColor(sf::Color::Cyan);
                            tmpInfoEvent.name = "CHANGE_MAP";
                            firstClick = false;
                        }
                        else
                        {
                            int tmpWidth = sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320 - tmpInfoEvent.surface.getPosition().x;
                            if(tmpWidth < 5)
                            {
                                tmpWidth = 5;
                            }
                            int tmpHeight = sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240 - tmpInfoEvent.surface.getPosition().y;
                            if(tmpHeight < 5)
                            {
                                tmpHeight = 5;
                            }
                            tmpInfoEvent.surface.setSize(sf::Vector2f(tmpWidth, tmpHeight));
                            tool = 99;
                            maxInTool = 11;
                            numberItem = 0;
                            setItemTexture();
                            firstClick = true;
                        }
                    }
                    else if(numberItem == 2)
                    {
                        if(firstClick)
                        {
                            while(!tmpInfoEvent.action.empty())
                            {
                                tmpInfoEvent.action.pop_back();
                            }
                            tmpInfoEvent.valX = 0;
                            tmpInfoEvent.valY = 0;
                            tmpInfoEvent.surface.setPosition(sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320, sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240);
                            tmpInfoEvent.surface.setFillColor(sf::Color::Cyan);
                            tmpInfoEvent.name = "SPAWN_ENEMY";
                            firstClick = false;
                        }
                        else
                        {
                            int tmpWidth = sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320 - tmpInfoEvent.surface.getPosition().x;
                            if(tmpWidth < 5)
                            {
                                tmpWidth = 5;
                            }
                            int tmpHeight = sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240 - tmpInfoEvent.surface.getPosition().y;
                            if(tmpHeight < 5)
                            {
                                tmpHeight = 5;
                            }
                            tmpInfoEvent.surface.setSize(sf::Vector2f(tmpWidth, tmpHeight));
                            tmpInfoEvent.valX = camera.getCenter().x;
                            tmpInfoEvent.valY = camera.getCenter().y;
                            if(tmpInfoEvent.valY < 240)
                            {
                                tmpInfoEvent.valY = 240;
                            }
                            tool = 98;
                            maxInTool = 7;
                            numberItem = 0;
                            setItemTexture();
                            firstClick = true;
                        }
                    }
                }
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(*window).x > 0 && sf::Mouse::getPosition(*window).x < 640 && sf::Mouse::getPosition(*window).y > 0 && sf::Mouse::getPosition(*window).y < 480)
            {
                if(sf::Mouse::getPosition(*window).y > 40)
                {
                    if(tool == 0)
                    {
                        int poseX = (sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320) / 20;
                        int poseY = (sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240) / 20;
                        std::map<std::pair<int, int>, itemClass*>::iterator i;
                        if((i = mapLevel.find(std::pair<int, int>(poseX, poseY))) != mapLevel.end())
                        {
                            delete i->second;
                            mapLevel.erase(i);
                        }
                        mapLevel[std::pair<int, int>(poseX, poseY)] = new basicBlocClass(nameOfItem, poseX, poseY);
                    }
                    else if(tool == 1)
                    {
                        if(!listEnemy.empty())
                        {
                            std::list<characterClass*>::iterator j;
                            for(j = listEnemy.begin(); j != listEnemy.end(); )
                            {
                                if((*j)->getSpriteDraw().getPosition().x > (item.getPosition().x + camera.getCenter().x - 320))
                                {
                                    listEnemy.insert(j, new basicEnemyClass((item.getPosition().x + camera.getCenter().x - 320), (item.getPosition().y + camera.getCenter().y - 240), nameOfItem));
                                    break;
                                }
                                else if((*j)->getSpriteDraw().getPosition().x == item.getPosition().x && (*j)->getSpriteDraw().getPosition().y == item.getPosition().y)
                                {
                                    delete (*j);
                                    listEnemy.erase(j++);
                                    continue;
                                }
                                ++j;
                            }
                            if(j == listEnemy.end())
                            {
                                listEnemy.insert(j, new basicEnemyClass((item.getPosition().x + camera.getCenter().x - 320), (item.getPosition().y + camera.getCenter().y - 240), nameOfItem));
                            }
                        }
                        else
                        {
                            listEnemy.push_back(new basicEnemyClass((item.getPosition().x + camera.getCenter().x - 320), (item.getPosition().y + camera.getCenter().y - 240), nameOfItem));
                        }
                    }
                    else if(tool == 3)
                    {
                        if(numberItem == 0)
                        {
                            for(std::list<infoEvent>::iterator j = listEvent.begin(); j != listEvent.end(); ++j)
                            {
                                if(j->surface.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320, sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240))
                                {
                                    typeTextEntered = "EDIT MESSAGE";
                                    textEntered = true;
                                    stringTextEntered = j->action.back();
                                    poseCurrentEvent = j;
                                    break;
                                }
                            }
                        }
                    }
                    else if(tool == 99)
                    {
                        int poseX = (sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320) / 20;
                        int poseY = (sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240) / 20;
                        std::string tmpStr;
                        std::string tmpPoseX;
                        std::string tmpPoseY;
                        for(std::list<std::string>::iterator i = tmpInfoEvent.action.begin(); i != tmpInfoEvent.action.end(); ++i)
                        {
                            tmpStr = *i;
                            tmpStr.erase(0, tmpStr.find(' ') + 1);
                            tmpPoseX = tmpStr.substr(0, tmpStr.find(' '));
                            tmpStr.erase(0, tmpStr.find(' ') + 1);
                            tmpPoseY = tmpStr;
                            if(poseX == atoi(tmpPoseX.c_str()) && poseY == atoi(tmpPoseY.c_str()))
                            {
                                tmpInfoEvent.action.erase(i);
                                break;
                            }
                        }
                        std::ostringstream tmpOssX;
                        tmpOssX << poseX;
                        std::ostringstream tmpOssY;
                        tmpOssY << poseY;
                        std::string newBlock = nameOfItem + " " + tmpOssX.str() + " " + tmpOssY.str();
                        tmpInfoEvent.action.push_back(newBlock);
                    }
                    else if(tool == 98)
                    {
                        int poseX = (item.getPosition().x + camera.getCenter().x - 320);
                        int poseY = (item.getPosition().y + camera.getCenter().y - 240);
                        std::string tmpStr;
                        std::string name;
                        std::string tmpPoseX;
                        std::string tmpPoseY;
                        for(std::list<std::string>::reverse_iterator i = tmpInfoEvent.action.rbegin(); i != tmpInfoEvent.action.rend(); ++i)
                        {
                            tmpStr = *i;
                            name = tmpStr.substr(0, tmpStr.find(' '));
                            tmpStr.erase(0, tmpStr.find(' ') + 1);
                            tmpPoseX = tmpStr.substr(0, tmpStr.find(' '));
                            tmpStr.erase(0, tmpStr.find(' ') + 1);
                            tmpPoseY = tmpStr;
                            if(name == "WAIT")
                            {
                                break;
                            }
                            if(poseX == atoi(tmpPoseX.c_str()) && poseY == atoi(tmpPoseY.c_str()))
                            {
                                tmpInfoEvent.action.erase(--(i.base()));
                                break;
                            }
                        }
                        std::ostringstream tmpOssX;
                        tmpOssX << poseX;
                        std::ostringstream tmpOssY;
                        tmpOssY << poseY;
                        std::string newBlock = nameOfItem + " " + tmpOssX.str() + " " + tmpOssY.str();
                        tmpInfoEvent.action.push_back(newBlock);
                    }
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && sf::Mouse::getPosition(*window).x > 0 && sf::Mouse::getPosition(*window).x < 640 && sf::Mouse::getPosition(*window).y > 0 && sf::Mouse::getPosition(*window).y < 480)
            {
                if(sf::Mouse::getPosition(*window).y > 40)
                {
                    if(tool == 0)
                    {
                        int poseX = (sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320) / 20;
                        int poseY = (sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240) / 20;
                        std::map<std::pair<int, int>, itemClass*>::iterator i;
                        if((i = mapLevel.find(std::pair<int, int>(poseX, poseY))) != mapLevel.end())
                        {
                            delete i->second;
                            mapLevel.erase(i);
                        }
                    }
                    else if(tool == 1)
                    {
                        for(std::list<characterClass*>::iterator j = listEnemy.begin(); j != listEnemy.end(); ++j)
                        {
                            if((*j)->getSpriteDraw().getGlobalBounds().contains((sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320), (sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240)))
                            {
                                delete (*j);
                                listEnemy.erase(j);
                                break;
                            }
                        }
                    }
                    else if(tool == 2)
                    {
                        for(std::list<infoEvent>::iterator j = listEvent.begin(); j != listEvent.end(); ++j)
                        {
                            if(j->surface.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320, sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240))
                            {
                                listEvent.erase(j);
                                break;
                            }
                        }
                    }
                    else if(tool == 99)
                    {
                        int poseX = (sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320) / 20;
                        int poseY = (sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240) / 20;
                        std::string tmpStr;
                        std::string tmpPoseX;
                        std::string tmpPoseY;
                        for(std::list<std::string>::iterator i = tmpInfoEvent.action.begin(); i != tmpInfoEvent.action.end(); ++i)
                        {
                            tmpStr = *i;
                            tmpStr.erase(0, tmpStr.find(' ') + 1);
                            tmpPoseX = tmpStr.substr(0, tmpStr.find(' '));
                            tmpStr.erase(0, tmpStr.find(' ') + 1);
                            tmpPoseY = tmpStr;
                            if(poseX == atoi(tmpPoseX.c_str()) && poseY == atoi(tmpPoseY.c_str()))
                            {
                                tmpInfoEvent.action.erase(i);
                                break;
                            }
                        }
                    }
                    else if(tool == 98)
                    {
                        int poseX = (item.getPosition().x + camera.getCenter().x - 320);
                        int poseY = (item.getPosition().y + camera.getCenter().y - 240);
                        std::string tmpStr;
                        std::string name;
                        std::string tmpPoseX;
                        std::string tmpPoseY;
                        for(std::list<std::string>::reverse_iterator i = tmpInfoEvent.action.rbegin(); i != tmpInfoEvent.action.rend(); ++i)
                        {
                            tmpStr = *i;
                            name = tmpStr.substr(0, tmpStr.find(' '));
                            tmpStr.erase(0, tmpStr.find(' ') + 1);
                            tmpPoseX = tmpStr.substr(0, tmpStr.find(' '));
                            tmpStr.erase(0, tmpStr.find(' ') + 1);
                            tmpPoseY = tmpStr;
                            if(name == "WAIT")
                            {
                                break;
                            }
                            if(poseX == atoi(tmpPoseX.c_str()) && poseY == atoi(tmpPoseY.c_str()))
                            {
                                tmpInfoEvent.action.erase(--(i.base()));
                                break;
                            }
                        }
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    textEntered = true;
                    typeTextEntered = "SAVE";
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                {
                    stringTextEntered.erase(0);
                    textEntered = true;
                    typeTextEntered = "LOAD";
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    std::ostringstream oss;
                    oss << endOfLevel;
                    stringTextEntered = oss.str();
                    textEntered = true;
                    typeTextEntered = "ENDOFLEVEL";
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
                {
                    std::ostringstream oss;
                    oss << heightLevel;
                    stringTextEntered = oss.str();
                    textEntered = true;
                    typeTextEntered = "HEIGHTLEVEL";
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::T) && tool > 50)
                {
                    std::list<infoEvent>::iterator j;
                    for(j = listEvent.begin(); j != listEvent.end(); ++j)
                    {
                        if(j->surface.getPosition().x > tmpInfoEvent.surface.getPosition().x)
                        {
                            listEvent.insert(j, tmpInfoEvent);
                            break;
                        }
                    }
                    if(j == listEvent.end())
                    {
                        listEvent.insert(j, tmpInfoEvent);
                    }
                    tool = 2;
                    maxInTool = 2;
                    numberItem = 0;
                    setItemTexture();
                }
            }
        }
        else
        {
            if(event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode < 128 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.text.unicode != 58 && event.text.unicode != 92 && event.text.unicode != 47 && event.text.unicode != 63 && event.text.unicode != 60 && event.text.unicode != 62 && event.text.unicode != 42 && event.text.unicode != 34 && event.text.unicode != 124 && event.text.unicode != 0)
                {
                    if(event.text.unicode == 8)
                    {
                        if(!stringTextEntered.empty())
                        {
                            stringTextEntered.erase(stringTextEntered.end() - 1);
                        }
                    }
                    else if(event.text.unicode == 13)
                    {
                        if(stringTextEntered.size() > 1)
                        {
                            textEntered = false;
                            if(typeTextEntered == "LOAD")
                            {
                                deleteLevel();
                                level.readLevelEdit("level/" + stringTextEntered + ".txt", listEvent, listEnemy, mapLevel, endOfLevel, heightLevel, typeLevel);
                                camera.setCenter(320, heightLevel - 240);
                                spritePlayer.setPosition(50.f, heightLevel - 80.f);
                            }
                            else if(typeTextEntered == "SAVE")
                            {
                                saveLevel("level/" + stringTextEntered + ".txt");
                            }
                            else if(typeTextEntered == "ENDOFLEVEL")
                            {
                                endOfLevel = std::atoi(stringTextEntered.c_str());
                                stringTextEntered.erase(0);
                                if(endOfLevel < 640)
                                    endOfLevel = 640;
                                if(camera.getCenter().x + 320 > endOfLevel)
                                    camera.setCenter(endOfLevel - 320, camera.getCenter().y);
                            }
                            else if(typeTextEntered == "HEIGHTLEVEL")
                            {
                                heightLevel = std::atoi(stringTextEntered.c_str());
                                stringTextEntered.erase(0);
                                if(heightLevel < 480)
                                    heightLevel = 480;
                                spritePlayer.setPosition(50.f, heightLevel - 80.f);
                                if(camera.getCenter().y + 240 > heightLevel)
                                    camera.setCenter(camera.getCenter().x, heightLevel - 240);
                            }
                            else if(typeTextEntered == "MESSAGE")
                            {
                                poseCurrentEvent->action.push_back(stringTextEntered);
                                stringTextEntered.erase(0);
                            }
                            else if(typeTextEntered == "EDIT MESSAGE")
                            {
                                poseCurrentEvent->action.pop_back();
                                poseCurrentEvent->action.push_back(stringTextEntered);
                                stringTextEntered.erase(0);
                            }
                        }
                    }
                    else if(stringTextEntered.size() < 40)
                    {
                        if(((typeTextEntered == "ENDOFLEVEL" || typeTextEntered == "HEIGHTLEVEL") && (event.text.unicode >= '0' && event.text.unicode <= '9')) || (typeTextEntered != "ENDOFLEVEL" && typeTextEntered != "HEIGHTLEVEL"))
                        {
                            char tmp = event.text.unicode;
                            stringTextEntered.push_back(tmp);
                        }
                    }
                }
            }
        }
    }
}

void editLevelStateClass::draw()
{
    window->clear(sf::Color::White);
    window->setView(camera);
    for(std::list<infoEvent>::iterator i = listEvent.begin(); i != listEvent.end(); ++i)
    {
        if(tool == 3 && i->surface.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320, sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240))
        {
            i->surface.setFillColor(sf::Color::Magenta);
            window->draw(i->surface);
            i->surface.setFillColor(sf::Color::Cyan);
        }
        else
        {
            window->draw(i->surface);
        }
    }
    for(std::list<characterClass*>::iterator i = listEnemy.begin(); i != listEnemy.end(); ++i)
    {
        window->draw((*i)->getSpriteDraw());
    }
    if(tool == 98)
    {
        std::string tmpStr;
        std::string name;
        std::string tmpPoseX;
        std::string tmpPoseY;
        for(std::list<std::string>::reverse_iterator i = tmpInfoEvent.action.rbegin(); i != tmpInfoEvent.action.rend(); ++i)
        {
            tmpStr = *i;
            name = tmpStr.substr(0, tmpStr.find(' '));
            tmpStr.erase(0, tmpStr.find(' ') + 1);
            tmpPoseX = tmpStr.substr(0, tmpStr.find(' '));
            tmpStr.erase(0, tmpStr.find(' ') + 1);
            tmpPoseY = tmpStr;
            if(name == "WAIT")
            {
                break;
            }
            drawEnemy(name, atoi(tmpPoseX.c_str()), atoi(tmpPoseY.c_str()));
        }
    }
    window->draw(spritePlayer);
    for(int i = (camera.getCenter().x - 320) / 20; i < (camera.getCenter().x + 320) / 20; ++i)
    {
        for(int j = (camera.getCenter().y - 200) / 20; j < (camera.getCenter().y + 240) / 20; ++j)
        {
            if(mapLevel.find(std::pair<int, int>(i, j)) != mapLevel.end())
            {
                window->draw(mapLevel.find(std::pair<int, int>(i, j))->second->getSkin());
            }
        }
    }
    if(tool == 99)
    {
        std::list<std::string>::iterator i;
        std::string tmpStr;
        std::string name;
        std::string tmpPoseX;
        std::string tmpPoseY;
        for(i = tmpInfoEvent.action.begin(); i != tmpInfoEvent.action.end(); ++i)
        {
            tmpStr = *i;
            name = tmpStr.substr(0, tmpStr.find(' '));
            tmpStr.erase(0, tmpStr.find(' ') + 1);
            tmpPoseX = tmpStr.substr(0, tmpStr.find(' '));
            tmpStr.erase(0, tmpStr.find(' ') + 1);
            tmpPoseY = tmpStr;
            drawBlock(name, atoi(tmpPoseX.c_str()), atoi(tmpPoseY.c_str()));
        }
    }
    window->setView(window->getDefaultView());
    window->draw(border);
    if(tool == 0 || tool == 99)
    {
        sf::Sprite tmpItem = item;
        window->draw(item);
        drawMessage("Bloc place", 450, 0);
        if(sf::Mouse::getPosition(*window).y > 40 && textEntered == false)
        {
            int poseX = (sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320) / 20;
            int poseY = (sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240) / 20;
            tmpItem.setPosition(poseX * 20 - camera.getCenter().x + 320, poseY * 20 - camera.getCenter().y + 240);
            window->draw(tmpItem);
        }
    }
    else if(tool == 1 || tool == 98)
    {
        drawMessage(nameOfItem, 10, 0);
        drawMessage("Enemy place", 450, 0);
        if(sf::Mouse::getPosition(*window).y > 40 && textEntered == false)
        {
            int poseX = (sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320) / 20;
            int poseY = (sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240) / 20;
            item.setPosition(poseX * 20 - camera.getCenter().x + 320, poseY * 20 - camera.getCenter().y + 240);
            window->draw(item);
        }
    }
    else if(tool == 2)
    {
        if(textEntered == false)
        {
            if(firstClick == false)
            {
                sf::RectangleShape surfaceDraw;
                surfaceDraw.setFillColor(sf::Color::Cyan);
                surfaceDraw.setPosition(tmpInfoEvent.surface.getPosition().x - camera.getCenter().x + 320, tmpInfoEvent.surface.getPosition().y - camera.getCenter().y + 240);
                int tmpWidth = sf::Mouse::getPosition(*window).x + camera.getCenter().x - 320 - tmpInfoEvent.surface.getPosition().x;
                if(tmpWidth < 5)
                {
                    tmpWidth = 5;
                }
                int tmpHeight = sf::Mouse::getPosition(*window).y + camera.getCenter().y - 240 - tmpInfoEvent.surface.getPosition().y;
                if(tmpHeight < 5)
                {
                    tmpHeight = 5;
                }
                surfaceDraw.setSize(sf::Vector2f(tmpWidth, tmpHeight));
                window->draw(surfaceDraw);
            }
            if(numberItem == 2)
            {
                drawPoint(320, 240);
            }
        }
        window->draw(border);
        drawMessage(nameOfItem, 10, 0);
        drawMessage("Event place", 450, 0);
    }
    else if(tool == 3)
    {
        drawMessage(nameOfItem, 10, 0);
        drawMessage("Event edit", 450, 0);
    }
    if(textEntered)
    {
        window->draw(backgroundText);
        drawMessage(stringTextEntered, 10, 220, true);
    }
}

void editLevelStateClass::setItemTexture()
{
    firstClick = true;
    if(tool == 0 || tool == 99)
    {
        item.setTexture(spriteClass::getImage("skinItem"));
        item.setPosition(10, 10);
        if(numberItem == 0)
        {
            item.setTextureRect(sf::IntRect(0, 0, 20, 20));
            nameOfItem = "WALL";
        }
        else if(numberItem == 1)
        {
            item.setTextureRect(sf::IntRect(20, 0, 20, 20));
            nameOfItem = "LAVA";
        }
        else if(numberItem == 2)
        {
            item.setTextureRect(sf::IntRect(20, 20, 20, 20));
            nameOfItem = "MINE";
        }
        else if(numberItem == 3)
        {
            item.setTextureRect(sf::IntRect(0, 20, 20, 20));
            nameOfItem = "MEDIKIT";
        }
        else if(numberItem == 4)
        {
            item.setTextureRect(sf::IntRect(40, 0, 20, 20));
            nameOfItem = "BLOCK_DOWN";
        }
        else if(numberItem == 5)
        {
            item.setTextureRect(sf::IntRect(40, 20, 20, 20));
            nameOfItem = "BLOCK_UP";
        }
        else if(numberItem == 6)
        {
            item.setTextureRect(sf::IntRect(40, 40, 20, 20));
            nameOfItem = "BLOCK_LEFT";
        }
        else if(numberItem == 7)
        {
            item.setTextureRect(sf::IntRect(20, 40, 20, 20));
            nameOfItem = "BLOCK_RIGHT";
        }
        else if(numberItem == 8)
        {
            item.setTextureRect(sf::IntRect(60, 0, 20, 20));
            nameOfItem = "STAIR_RIGHT";
        }
        else if(numberItem == 9)
        {
            item.setTextureRect(sf::IntRect(60, 20, 20, 20));
            nameOfItem = "STAIR_LEFT";
        }
        else if(numberItem == 10)
        {
            item.setTextureRect(sf::IntRect(60, 40, 20, 20));
            nameOfItem = "WALL_LIGHT";
        }
        else if(numberItem == 11 && tool == 99)
        {
            item.setTextureRect(sf::IntRect(0, 40, 20, 20));
            nameOfItem = "ERASE";
        }
    }
    else if(tool == 1 || tool == 98)
    {
        if(numberItem == 0)
        {
            item.setTexture(spriteClass::getImage("enemy"));
            item.setTextureRect(sf::IntRect(82, 0, 40, 80));
            nameOfItem = "BASIC";
        }
        else if(numberItem == 1)
        {
            item.setTexture(spriteClass::getImage("explosiveEnemy"));
            item.setTextureRect(sf::IntRect(0, 0, 40, 40));
            nameOfItem = "EXPLOSIVE";
        }
        else if(numberItem == 2)
        {
            item.setTexture(spriteClass::getImage("laserEnemy"));
            item.setTextureRect(sf::IntRect(0, 0, 40, 80));
            nameOfItem = "LASER_E";
        }
        else if(numberItem == 3)
        {
            item.setTexture(spriteClass::getImage("turret"));
            item.setTextureRect(sf::IntRect(0, 0, 40, 60));
            nameOfItem = "TURRET_L";
        }
        else if(numberItem == 4)
        {
            item.setTexture(spriteClass::getImage("turret"));
            item.setTextureRect(sf::IntRect(41, 0, 40, 60));
            nameOfItem = "TURRET_R";
        }
        else if(numberItem == 5)
        {
            item.setTexture(spriteClass::getImage("laserShipEnemy"));
            item.setTextureRect(sf::IntRect(0, 0, 40, 40));
            nameOfItem = "LASER_SE";
        }
        else if(numberItem == 6 && tool == 98)
        {
            item.setTexture(spriteClass::getImage("skinItem"));
            item.setTextureRect(sf::IntRect(0, 40, 20, 20));
            nameOfItem = "WAIT";
        }
        else if(numberItem == 7 && tool == 98)
        {
            item.setTexture(spriteClass::getImage("boss"));
            item.setTextureRect(sf::IntRect(0, 0, 300, 480));
            nameOfItem = "BOSS";
        }
    }
    else if(tool == 2)
    {
        if(numberItem == 0)
        {
            nameOfItem = "MESSAGE";
        }
        else if(numberItem == 1)
        {
            nameOfItem = "BLOCK";
        }
        else if(numberItem == 2)
        {
            nameOfItem = "ENEMY";
        }
    }
    else if(tool == 3)
    {
        if(numberItem == 0)
        {
            nameOfItem = "EDIT MESSAGE";
        }
    }
}

void editLevelStateClass::drawMessage(std::string message, float x, float y, bool isTextEntered)
{
    sf::Text textMessage(message, font, 25);
    textMessage.setPosition(x, y);
    textMessage.setColor(isTextEntered ? sf::Color::Black : sf::Color::White);
    window->draw(textMessage);
}

void editLevelStateClass::deleteLevel()
{
    for(std::list<infoEvent>::iterator i = listEvent.begin(); i != listEvent.end(); )
    {
        listEvent.erase(i++);
    }
    for(std::list<characterClass*>::iterator i = listEnemy.begin(); i != listEnemy.end(); )
    {
        delete (*i);
        listEnemy.erase(i++);
    }
    for(std::map<std::pair<int, int>, itemClass*>::iterator i = mapLevel.begin(); i != mapLevel.end(); )
    {
        delete i->second;
        mapLevel.erase(i++);
    }
    numberItem = 0;
    tool = 0;
    maxInTool = 10;
    item.setTexture(spriteClass::getImage("skinItem"));
    item.setPosition(10, 10);
    setItemTexture();
    typeTextEntered = "NONE";
}

void editLevelStateClass::saveLevel(std::string nameLevel)
{
    std::ofstream file(nameLevel.c_str(), std::ios_base::trunc);

    if(file.is_open())
    {
        file << "MAP" << std::endl;
        for(std::map<std::pair<int, int>, itemClass*>::iterator i = mapLevel.begin(); i != mapLevel.end(); ++i)
        {
            file << i->second->getType() << " " << i->second->getSkin().getPosition().x / 20 << " " << i->second->getSkin().getPosition().y / 20 << std::endl;
        }
        file << "END" << std::endl;
        file << "ENEMY" << std::endl;
        for(std::list<characterClass*>::iterator i = listEnemy.begin(); i != listEnemy.end(); ++i)
        {
            file << (*i)->getType() << " " << (*i)->getPosePlayer().x << " " << (*i)->getPosePlayer().y << std::endl;
        }
        file << "END" << std::endl;
        file << "EVENT" << std::endl;
        for(std::list<infoEvent>::iterator i = listEvent.begin(); i != listEvent.end(); ++i)
        {
            if(i->name == "MESSAGE")
            {
                while(i->action.back().find("&n") != std::string::npos)
                {
                    i->action.back().replace(i->action.back().find("&n"), 2, "\\n");
                }
                file << i->name << " " << i->surface.getPosition().x << " " << i->surface.getPosition().y << " " << i->surface.getGlobalBounds().width << " " << i->surface.getGlobalBounds().height << " " << i->action.back() << std::endl;
            }
            else if(i->name == "SPAWN_ENEMY")
            {
                file << i->name << " " << i->surface.getPosition().x << " " << i->surface.getPosition().y << " " << i->surface.getGlobalBounds().width << " " << i->surface.getGlobalBounds().height << " " << i->valX << " " << i->valY << std::endl;
                for(std::list<std::string>::iterator j = i->action.begin(); j != i->action.end(); ++j)
                {
                    file << (*j) << std::endl;
                }
                file << "END" << std::endl;
            }
            else if(i->name == "CHANGE_MAP")
            {
                file << i->name << " " << i->surface.getPosition().x << " " << i->surface.getPosition().y << " " << i->surface.getGlobalBounds().width << " " << i->surface.getGlobalBounds().height << " " << std::endl;
                for(std::list<std::string>::iterator j = i->action.begin(); j != i->action.end(); ++j)
                {
                    file << (*j) << std::endl;
                }
                file << "END" << std::endl;
            }
        }
        file << "END" << std::endl;
        file << "LIGHT_WALL" << std::endl;
        makeLightWall(file);
        file << "END" << std::endl;
        file << "HEIGHT" << std::endl;
        file << heightLevel << std::endl;
        file << "END" << std::endl;
        file << "ENDOFLEVEL" << std::endl;
        file << endOfLevel << std::endl;
        file << "END" << std::endl;
        file << "TYPELEVEL" << std::endl;
        file << typeLevel << std::endl;
        file << "END" << std::endl;
        file.close();
    }
}

void editLevelStateClass::makeLightWall(std::ofstream& file)
{
    std::map<std::pair<int, int>, itemClass*>::iterator j;
    for(std::map<std::pair<int, int>, itemClass*>::iterator i = mapLevel.begin(); i != mapLevel.end(); ++i)
    {
        if(i->second->getStatBlock("BLOCK_LIGHT") == true)
        {
            j = mapLevel.find(std::pair<int, int>(i->first.first, i->first.second - 1));
            if(j != mapLevel.end())
            {
                if(j->second->getStatBlock("BLOCK_LIGHT") != true)
                {
                    file << i->first.first * 20 << " " << i->first.second * 20 << " " << (i->first.first + 1) * 20 << " " << i->first.second * 20 << std::endl;
                }
            }
            else
            {
                file << i->first.first * 20 << " " << i->first.second * 20 << " " << (i->first.first + 1) * 20 << " " << i->first.second * 20 << std::endl;
            }

            j = mapLevel.find(std::pair<int, int>(i->first.first + 1, i->first.second));
            if(j != mapLevel.end())
            {
                if(j->second->getStatBlock("BLOCK_LIGHT") != true)
                {
                    file << (i->first.first + 1) * 20 << " " << i->first.second * 20 << " " << (i->first.first + 1) * 20 << " " << (i->first.second + 1) * 20 << std::endl;
                }
            }
            else
            {
                file << (i->first.first + 1) * 20 << " " << i->first.second * 20 << " " << (i->first.first + 1) * 20 << " " << (i->first.second + 1) * 20 << std::endl;
            }

            j = mapLevel.find(std::pair<int, int>(i->first.first, i->first.second + 1));
            if(j != mapLevel.end())
            {
                if(j->second->getStatBlock("BLOCK_LIGHT") != true)
                {
                    file << i->first.first * 20 << " " << (i->first.second + 1) * 20 << " " << (i->first.first + 1) * 20 << " " << (i->first.second + 1) * 20 << std::endl;
                }
            }
            else
            {
                file << i->first.first * 20 << " " << (i->first.second + 1) * 20 << " " << (i->first.first + 1) * 20 << " " << (i->first.second + 1) * 20 << std::endl;
            }

            j = mapLevel.find(std::pair<int, int>(i->first.first - 1, i->first.second));
            if(j != mapLevel.end())
            {
                if(j->second->getStatBlock("BLOCK_LIGHT") != true)
                {
                    file << i->first.first * 20 << " " << i->first.second * 20 << " " << i->first.first * 20 << " " << (i->first.second + 1) * 20 << std::endl;
                }
            }
            else
            {
                file << i->first.first * 20 << " " << i->first.second * 20 << " " << i->first.first * 20 << " " << (i->first.second + 1) * 20 << std::endl;
            }
        }
    }
}

void editLevelStateClass::drawBlock(std::string name, int x, int y)
{
    sf::Sprite tmpBlock;
    tmpBlock.setTexture(spriteClass::getImage("skinItem"));
    tmpBlock.setPosition(x * 20, y * 20);
    if(name == "WALL")
    {
        tmpBlock.setTextureRect(sf::IntRect(0, 0, 20, 20));
    }
    else if(name == "LAVA")
    {
        tmpBlock.setTextureRect(sf::IntRect(20, 0, 20, 20));
    }
    else if(name == "MINE")
    {
        tmpBlock.setTextureRect(sf::IntRect(20, 20, 20, 20));
    }
    else if(name == "MEDIKIT")
    {
        tmpBlock.setTextureRect(sf::IntRect(0, 20, 20, 20));
    }
    else if(name == "BLOCK_DOWN")
    {
        tmpBlock.setTextureRect(sf::IntRect(40, 0, 20, 20));
    }
    else if(name == "BLOCK_UP")
    {
        tmpBlock.setTextureRect(sf::IntRect(40, 20, 20, 20));
    }
    else if(name == "BLOCK_LEFT")
    {
        tmpBlock.setTextureRect(sf::IntRect(40, 40, 20, 20));
    }
    else if(name == "BLOCK_RIGHT")
    {
        tmpBlock.setTextureRect(sf::IntRect(20, 40, 20, 20));
    }
    else if(name == "STAIR_RIGHT")
    {
        tmpBlock.setTextureRect(sf::IntRect(60, 0, 20, 20));
    }
    else if(name == "STAIR_LEFT")
    {
        tmpBlock.setTextureRect(sf::IntRect(60, 20, 20, 20));
    }
    else if(name == "WALL_LIGHT")
    {
        tmpBlock.setTextureRect(sf::IntRect(60, 40, 20, 20));
    }
    else if(name == "ERASE")
    {
        tmpBlock.setTextureRect(sf::IntRect(0, 40, 20, 20));
    }
    window->draw(tmpBlock);
}

void editLevelStateClass::drawEnemy(std::string name, int x, int y)
{
    sf::Sprite tmpEnemy;
    tmpEnemy.setPosition(x, y);
    if(name == "BASIC")
    {
        tmpEnemy.setTexture(spriteClass::getImage("enemy"));
        tmpEnemy.setTextureRect(sf::IntRect(82, 0, 40, 80));
    }
    else if(name == "EXPLOSIVE")
    {
        tmpEnemy.setTexture(spriteClass::getImage("explosiveEnemy"));
        tmpEnemy.setTextureRect(sf::IntRect(0, 0, 40, 40));
    }
    else if(name == "LASER_E")
    {
        tmpEnemy.setTexture(spriteClass::getImage("laserEnemy"));
        tmpEnemy.setTextureRect(sf::IntRect(0, 0, 40, 80));
    }
    else if(name == "TURRET_L")
    {
        tmpEnemy.setTexture(spriteClass::getImage("turret"));
        tmpEnemy.setTextureRect(sf::IntRect(0, 0, 40, 60));
    }
    else if(name == "TURRET_R")
    {
        tmpEnemy.setTexture(spriteClass::getImage("turret"));
        tmpEnemy.setTextureRect(sf::IntRect(41, 0, 40, 60));
    }
    else if(name == "LASER_SE")
    {
        tmpEnemy.setTexture(spriteClass::getImage("laserShipEnemy"));
        tmpEnemy.setTextureRect(sf::IntRect(0, 0, 40, 40));
    }
    else if(name == "WAIT")
    {
        tmpEnemy.setTexture(spriteClass::getImage("skinItem"));
        tmpEnemy.setTextureRect(sf::IntRect(0, 40, 20, 20));
    }
    else if(name == "BOSS")
    {
        tmpEnemy.setTexture(spriteClass::getImage("boss"));
        tmpEnemy.setTextureRect(sf::IntRect(0, 0, 300, 480));
    }
    window->draw(tmpEnemy);
}

void editLevelStateClass::drawPoint(int x, int y)
{
    sf::RectangleShape point;
    point.setFillColor(sf::Color::Red);
    point.setPosition(x - 5, y - 5);
    point.setSize(sf::Vector2f(10, 10));
    window->draw(point);
}
