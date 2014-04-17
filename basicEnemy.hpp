#ifndef BASICENEMY_HPP
#define BASICENEMY_HPP

#include <SFML/Graphics.hpp>
#include <deque>

#include "character.hpp"

class basicEnemyClass : public characterClass
{
public:
    basicEnemyClass(float x, float y, std::string newTypeBasic);
    const sf::Sprite& getSpriteDraw();
    const sf::RectangleShape getColliBox();
    void update();
    void initialize();
    void updatePoseSprite();
    const sf::RectangleShape getPoseStrike();
    void setStrike();
    void stopStrike();
private:
    std::deque<sf::Sprite> spriteSheet;
};

#endif
