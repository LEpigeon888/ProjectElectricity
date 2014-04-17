#include "mainMenuState.hpp"
#include "editLevelState.hpp"
#include "playState.hpp"
#include "global.hpp"
#include <dirent.h>
#include <fstream>

void mainMenuStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
    window->setView(window->getDefaultView());
    saveExist = checkSave();
    menu.addToStaticList("Project Eletricity by LEpigeon888", 10, 10);
    menu.addToMoveList("Play", -1, 150, true);
    if(saveExist)
    {
        menu.addToMoveList("Load", -1, -1, true);
    }
    menu.addToMoveList("Edit", -1, -1, true);
    numberSubMenu = menu.addToMoveList("Option", -1, -1, true, "SUB_MENU");
    menu.addEntryToListEntry(numberSubMenu, "STATIC_MESS", "Option", 10, 10);
    if(globalClass::getSmoothLighting() == true)
    {
        numberEntrySubMenu = menu.addEntryToListEntry(numberSubMenu, "BOOL_TRUE", "SmoothLighting", -1, 200, true);
    }
    else
    {
        numberEntrySubMenu = menu.addEntryToListEntry(numberSubMenu, "BOOL_FALSE", "SmoothLighting", -1, 200, true);
    }
    menu.addToMoveList("Quit", -1, -1, true);
}

void mainMenuStateClass::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if((event.type == sf::Event::Closed))
        {
            window->close();
            break;
        }

        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Return)
            {
                if(menu.getSelectedMode() == 0 && menu.getSubMenu() == 0)
                {
                    parent->set(new playStateClass);
                    return;
                }
                else if(saveExist && menu.getSelectedMode() == 1 && menu.getSubMenu() == 0)
                {
                    std::ifstream file("save/save.avi");

                    if(file.is_open())
                    {
                        int level;
                        int life;
                        int money;
                        int speedUpgrad;
                        int jumpUpgrad;
                        double damageUpgrad;
                        double resistanceUpgrad;
                        int lifeUpgrad;
                        bool getLaserRifle;
                        std::string weaponActu;

                        file >> level >> life >> money >> speedUpgrad >> jumpUpgrad >> damageUpgrad >> resistanceUpgrad >> lifeUpgrad >> getLaserRifle >> weaponActu;

                        parent->set(new playStateClass(level, life, money, speedUpgrad, jumpUpgrad, damageUpgrad, resistanceUpgrad, lifeUpgrad, getLaserRifle, weaponActu));
                        return;
                    }
                    else
                    {
                        parent->set(new playStateClass);
                        return;
                    }
                }
                else if(menu.getSelectedMode() == 1 + saveExist && menu.getSubMenu() == 0)
                {
                    parent->set(new editLevelStateClass);
                    return;
                }
                else if(menu.getSelectedMode() == 3 + saveExist && menu.getSubMenu() == 0)
                {
                    window->close();
                }
                else if(menu.getSelectedMode() == 0 && menu.getSubMenu() != 0)
                {
                    globalClass::getSmoothLighting() = !globalClass::getSmoothLighting();
                }
            }
            else if(event.key.code == sf::Keyboard::Escape)
            {
                if(menu.getSubMenu() != 0)
                {
                    if(globalClass::getSmoothLighting() == true)
                    {
                        menu.setEntryToListEntry(numberSubMenu, numberEntrySubMenu, "BOOL_TRUE");
                    }
                    else
                    {
                        menu.setEntryToListEntry(numberSubMenu, numberEntrySubMenu, "BOOL_FALSE");
                    }

                    std::ofstream file("conf.zip", std::ios_base::trunc);

                    if(file.is_open())
                    {
                        file << globalClass::getSmoothLighting();
                    }

                    file.close();
                }
            }
            menu.update(event);
        }
    }
}

void mainMenuStateClass::draw()
{
    window->clear(sf::Color::White);
    menu.draw(window);
}

bool mainMenuStateClass::checkSave()
{
    DIR* directory = NULL;
    struct dirent* file = NULL;
    directory = opendir("save");
    if(directory != NULL)
    {
        while((file = readdir(directory)) != NULL)
        {
            if(std::string(file->d_name) == "save.avi")
            {
                closedir(directory);
                return true;
            }
        }
    }
    closedir(directory);
    return false;
}
