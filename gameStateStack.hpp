#ifndef GAMESTATESTACK_HPP
#define GAMESTATESTACK_HPP

#include <list>
#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class gameStateStackClass
{
public:
    void set(gameStateClass* state);
    void add(gameStateClass* state);
    void pop();
    void update();
    void draw();
    void setWindow(sf::RenderWindow* newwindow);
    bool getChange();
    void setChange(bool val);
private:
    std::list<gameStateClass*> stateList;
    sf::RenderWindow* window;
    bool change;
};

#endif
