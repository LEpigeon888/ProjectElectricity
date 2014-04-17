#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "gameStateStack.hpp"

class gameClass
{
public:
    void initialize();
    void run();
    void loadOption();
private:
    sf::RenderWindow window;
    sf::Clock timeFrame;
    gameStateStackClass gameStateStack;
};

#endif
