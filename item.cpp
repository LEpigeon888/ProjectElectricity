#include "item.hpp"

itemClass::itemClass()
{
    solidBlock = false;
    solidLaserBlock = false;
    tempBlock = false;
    moveUpBlock = false;
    moveDownBlock = false;
    moveLeftBlock = false;
    moveRightBlock = false;
    stairRight = false;
    stairLeft = false;
    damageBlock = false;
    blockLight = false;
    valueDamage = 0;
}

const sf::Sprite& itemClass::getSkin()
{
    return skin;
}

const std::string& itemClass::getType()
{
    return type;
}

bool itemClass::getStatBlock(std::string stat)
{
    if(stat == "SOLID")
        return solidBlock;
    else if(stat == "SOLID_LASER")
        return solidLaserBlock;
    else if(stat == "TEMP")
        return tempBlock;
    else if(stat == "MOVE_UP")
        return moveUpBlock;
    else if(stat == "MOVE_DOWN")
        return moveDownBlock;
    else if(stat == "MOVE_LEFT")
        return moveLeftBlock;
    else if(stat == "MOVE_RIGHT")
        return moveRightBlock;
    else if(stat == "STAIR_RIGHT")
        return stairRight;
    else if(stat == "STAIR_LEFT")
        return stairLeft;
    else if(stat == "DAMAGE")
        return damageBlock;
    else if(stat == "BLOCK_LIGHT")
        return blockLight;
    else
        return false;
}

int itemClass::getValueDamage()
{
    return valueDamage;
}

void itemClass::setType(std::string newType)
{
    type = newType;
}
