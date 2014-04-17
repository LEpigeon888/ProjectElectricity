#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "gameState.hpp"
#include "gamePlayed.hpp"

class playStateClass : public gameStateClass
{
public:
    playStateClass();
    playStateClass(int level, int life, int money, int speedUpgrad, int jumpUpgrad, double damageUpgrad, double resistanceUpgrad, int lifeUpgrad, bool getLaserRifle, std::string weaponActu);
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
private:
    float velocity;
    bool error;
    gamePlayedClass gamePlayed;
};

#endif
