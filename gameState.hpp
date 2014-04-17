#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class gameStateStackClass;

class gameStateClass
{
public:
    virtual ~gameStateClass() {};
    virtual void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    gameStateStackClass* parent;
    sf::RenderWindow* window;
};

#endif
