#include "libMenuSf.hpp"
#include <iostream>

using namespace msf;

menuSfClass::menuSfClass(bool isSubMenu)
{
    font.loadFromFile("cour.ttf");
    textColor = sf::Color::Black;
    cursor.setSize(sf::Vector2f(10, 10));
    cursor.setPosition(0, 0);
    cursor.setFillColor(textColor);
    if(isSubMenu == true)
    {
        numberSubMenu = -1;
    }
    else
    {
        numberSubMenu = 0;
    }
    modeSelect = 0;
    actuPoseX = 0;
    actuPoseY = 0;
    isActive = true;
}

menuSfClass::menuSfClass(sf::Color newTextColor, std::string path, bool isSubMenu)
{
    font.loadFromFile(path);
    textColor = newTextColor;
    cursor.setSize(sf::Vector2f(10, 10));
    cursor.setPosition(0, 0);
    cursor.setFillColor(newTextColor);
    if(isSubMenu == true)
    {
        numberSubMenu = -1;
    }
    else
    {
        numberSubMenu = 0;
    }
    modeSelect = 0;
    actuPoseX = 0;
    actuPoseY = 0;
    isActive = true;
}

menuSfClass::~menuSfClass()
{

}

void menuSfClass::changeSet(sf::Color newTextColor, std::string path)
{
    font.loadFromFile(path);
    textColor = newTextColor;
    cursor.setFillColor(newTextColor);
}

void menuSfClass::update(sf::Event event)
{
    if(isActive == false && subMenuActu)
    {
        subMenuActu->update(event);
        if(subMenuActu->getIsActive() == false)
        {
            isActive = true;
            numberSubMenu = 0;
        }
    }
    else
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Up && moveMess.empty() == false)
            {
                modeSelect -= 1;
                if(modeSelect < 0)
                    modeSelect = moveMess.size() - 1;
                cursor.setPosition(moveMess[modeSelect].mess.poseX - 15, moveMess[modeSelect].mess.poseY + 15);
            }
            else if(event.key.code == sf::Keyboard::Down && moveMess.empty() == false)
            {
                modeSelect += 1;
                if(modeSelect > moveMess.size() - 1)
                    modeSelect = 0;
                cursor.setPosition(moveMess[modeSelect].mess.poseX - 15, moveMess[modeSelect].mess.poseY + 15);
            }
            else if(event.key.code == sf::Keyboard::Escape && numberSubMenu == -1)
            {
                isActive = false;
            }
            else if(event.key.code == sf::Keyboard::Return && moveMess.empty() == false)
            {
                if(moveMess[modeSelect].type == "SUB_MENU")
                {
                    subMenuActu.reset(new menuSfClass(true));
                    for(std::list<entryMenu>::iterator i = moveMess[modeSelect].listEntryMenu.begin(); i != moveMess[modeSelect].listEntryMenu.end(); ++i)
                    {
                        if(i->type == "STATIC_MESS")
                        {
                            subMenuActu->addToStaticList(i->mess.mess, i->mess.poseX, i->mess.poseY);
                        }
                        else
                        {
                            subMenuActu->addToMoveList(i->mess.mess, i->mess.poseX, i->mess.poseY, false, i->type);
                        }
                    }
                    isActive = false;
                    numberSubMenu = modeSelect;
                }
                else if(moveMess[modeSelect].type == "BOOL_TRUE")
                {
                    moveMess[modeSelect].type = "BOOL_FALSE";
                }
                else if(moveMess[modeSelect].type == "BOOL_FALSE")
                {
                    moveMess[modeSelect].type = "BOOL_TRUE";
                }
            }
        }
    }
}

void menuSfClass::draw(sf::RenderWindow* window)
{
    if(isActive == false && subMenuActu)
    {
        subMenuActu->draw(window);
    }
    else
    {
        for(std::list<message>::iterator i = staticMess.begin(); i != staticMess.end(); ++i)
        {
            drawMessage(i->mess, i->poseX, i->poseY, window);
        }
        for(std::vector<entryMenu>::iterator i = moveMess.begin(); i != moveMess.end(); ++i)
        {
            if(i->type == "BOOL_TRUE")
            {
                drawMessage(i->mess.mess + " On", i->mess.poseX, i->mess.poseY, window);
            }
            else if(i->type == "BOOL_FALSE")
            {
                drawMessage(i->mess.mess + " Off", i->mess.poseX, i->mess.poseY, window);
            }
            else
            {
                drawMessage(i->mess.mess, i->mess.poseX, i->mess.poseY, window);
            }
        }
        window->draw(cursor);
    }
}

int menuSfClass::getSelectedMode()
{
    if(isActive == false && subMenuActu)
    {
        return subMenuActu->getSelectedMode();
    }
    return modeSelect;
}

void menuSfClass::addToStaticList(std::string mess, int x, int y)
{
    message staticMessage;
    staticMessage.mess = mess;
    staticMessage.poseX = x;
    staticMessage.poseY = y;
    staticMess.push_back(staticMessage);
}

int menuSfClass::addToMoveList(std::string mess, int x, int y, bool center, std::string newType)
{
    bool first = false;
    entryMenu newEntryMenu;
    newEntryMenu.type = newType;
    if(actuPoseX == 0 && actuPoseY == 0)
    {
        first = true;
    }
    message moveMessage;
    moveMessage.mess = mess;
    if(x == -1)
    {
        if(center == true)
        {
            sf::Text tmpText(mess, font, 30);
            moveMessage.poseX = (640 / 2) - (tmpText.getGlobalBounds().width / 2);
            actuPoseX = x;
        }
        else
        {
            moveMessage.poseX = actuPoseX;
        }
    }
    else
    {
        moveMessage.poseX = x;
        actuPoseX = x;
    }
    if(y == -1)
    {
        moveMessage.poseY = actuPoseY + 50;
        actuPoseY += 50;
    }
    else
    {
        moveMessage.poseY = y;
        actuPoseY = y;
    }

    if(first == true)
    {
        cursor.setPosition(moveMessage.poseX - 15, moveMessage.poseY + 15);
    }
    newEntryMenu.mess = moveMessage;
    moveMess.push_back(newEntryMenu);

    return moveMess.size() - 1;
}

int menuSfClass::addEntryToListEntry(int number, std::string newType, std::string mess, int x, int y, bool center)
{
    entryMenu newEntry;
    newEntry.type = newType;
    newEntry.mess.mess = mess;
    if(center == true)
    {
        sf::Text tmpText(mess, font, 30);
        newEntry.mess.poseX = (640 / 2) - (tmpText.getGlobalBounds().width / 2);
    }
    else
    {
        newEntry.mess.poseX = x;
    }
    newEntry.mess.poseY = y;
    moveMess[number].listEntryMenu.push_back(newEntry);

    return moveMess[number].listEntryMenu.size() - 1;
}

void menuSfClass::setEntryToListEntry(int number, int numberEntry, std::string newType)
{
    int j = 0;
    for(std::list<entryMenu>::iterator i = moveMess[number].listEntryMenu.begin(); i != moveMess[modeSelect].listEntryMenu.end(); ++i, ++j)
    {
        if(j == numberEntry)
        {
            i->type = newType;
        }
    }
}

void menuSfClass::drawMessage(std::string message, float x, float y, sf::RenderWindow *window)
{
    sf::Text textMessage(message, font, 30);
    textMessage.setPosition(x, y);
    textMessage.setColor(textColor);
    window->draw(textMessage);
}

int menuSfClass::getSubMenu()
{
    return numberSubMenu;
}

bool menuSfClass::getIsActive()
{
    return isActive;
}
