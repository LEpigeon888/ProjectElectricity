#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>

class itemClass
{
public:
    virtual ~itemClass() {};
    itemClass();
    const sf::Sprite& getSkin();
    const std::string& getType();
    void setType(std::string newType);
    bool getStatBlock(std::string stat);
    int getValueDamage();
protected:
    bool solidBlock;
    bool solidLaserBlock;
    bool tempBlock;
    bool moveUpBlock;
    bool moveDownBlock;
    bool moveLeftBlock;
    bool moveRightBlock;
    bool stairRight;
    bool stairLeft;
    bool damageBlock;
    bool blockLight;
    float valueDamage;
    sf::Sprite skin;
    std::string type;
};

#endif
