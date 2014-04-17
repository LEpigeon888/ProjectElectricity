#include "game.hpp"
#include "mainMenuState.hpp"
#include "sprite.hpp"
#include "global.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

void gameClass::initialize()
{
    window.create(sf::VideoMode(640, 480), "SFML window");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    globalClass::getFont().loadFromFile("cour.ttf");
    gameStateStack.setWindow(&window);
    loadOption();
    gameStateStack.set(new mainMenuStateClass());
    spriteClass::initText();
    srand(time(NULL));
    globalClass::getTimer().restart();
}

void gameClass::run()
{
    while(window.isOpen())
    {
        gameStateStack.update();
        if(gameStateStack.getChange())
        {
            gameStateStack.setChange(false);
            gameStateStack.update();
            gameStateStack.draw();
        }
        else
        {
            gameStateStack.draw();
        }
        window.display();
        std::cout << (1/globalClass::getTimeFrame()) << std::endl;
        globalClass::getTimeFrame() = globalClass::getTimer().getElapsedTime().asSeconds();
        globalClass::getTimer().restart();
    }
}

void gameClass::loadOption()
{
    std::ifstream file("conf.zip");

    if(file.is_open())
    {
        file >> globalClass::getSmoothLighting();
    }
    file.close();
}
