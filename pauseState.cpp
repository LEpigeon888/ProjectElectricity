#include "pauseState.hpp"
#include "mainMenuState.hpp"
#include "gamePlayed.hpp"
#include "level.hpp"
#include <fstream>

pauseStateClass::pauseStateClass(gamePlayedClass* newInfoGame)
{
    infoGame = newInfoGame;
}

void pauseStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
    window->setView(window->getDefaultView());
    menu.addToStaticList("Pause", 10, 10);
    menu.addToMoveList("Continue", 280, 200);
    menu.addToMoveList("Save");
    menu.addToMoveList("Menu");
    menu.addToMoveList("Quit");
}

void pauseStateClass::update()
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
                if(menu.getSelectedMode() == 0)
                {
                    parent->pop();
                    return;
                }
                else if(menu.getSelectedMode()  == 1)
                {
                    saveGame();
                    return;
                }
                else if(menu.getSelectedMode()  == 2)
                {
                    parent->set(new mainMenuStateClass);
                    return;
                }
                else if(menu.getSelectedMode()  == 3)
                    window->close();
            }
            else if(event.key.code == sf::Keyboard::Escape)
            {
                parent->pop();
                return;
            }
            else
            {
                menu.update(event);
            }
        }
    }
}

void pauseStateClass::draw()
{
    window->clear(sf::Color::White);
    menu.draw(window);
}

void pauseStateClass::saveGame()
{
    std::ofstream file("save/save.avi", std::ios_base::trunc);
    if(file.is_open())
    {
        file << infoGame->getLevelClass().getNumberLevel() << std::endl;
        file << infoGame->getPlayer().getNumberOfLife() << std::endl;
        file << infoGame->getPlayer().getMoney() << std::endl;
        file << infoGame->getPlayer().getUpgrad("speed") << std::endl;
        file << infoGame->getPlayer().getUpgrad("jump") << std::endl;
        file << infoGame->getPlayer().getUpgrad("damage") << std::endl;
        file << infoGame->getPlayer().getUpgrad("resistance") << std::endl;
        file << infoGame->getPlayer().getUpgrad("life") << std::endl;
        file << infoGame->getPlayer().getWeaponInStore("LASER_RIFLE") << std::endl;
        file << infoGame->getPlayer().getWeapon() << std::endl;
    }
}
