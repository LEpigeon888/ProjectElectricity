#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "gameState.hpp"
#include "gamePlayed.hpp"
#include "libMenuSf.hpp"

#include <iostream>

class pauseStateClass : public gameStateClass
{
public:
    pauseStateClass(gamePlayedClass* newInfoGame);
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
    void saveGame();
private:
    msf::menuSfClass menu;
    gamePlayedClass* infoGame;
};

#endif

