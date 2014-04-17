#ifndef BOSSENEMY_HPP
#define BOSSENEMY_HPP

#include <SFML/Graphics.hpp>
#include <deque>

#include "character.hpp"

class bossEnemyClass : public characterClass
{
public:
    bossEnemyClass(float x, float y, std::string newType);
    const sf::Sprite& getSpriteDraw();
    const sf::RectangleShape getColliBox();
    void update();
    void initialize();
    void updatePoseSprite();
    const sf::RectangleShape getPoseStrike();
    void setStrike();
    virtual const sf::FloatRect getHitBox();
    virtual bool inStriking();
private:
    std::deque<sf::Sprite> spriteSheet;
    bool timeStrikeIsStartWeapons[2];
    int currentWeapon;
    timerClass timeStrikeWeapons[2];
};

#endif

