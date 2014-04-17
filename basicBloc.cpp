#include "basicBloc.hpp"
#include "sprite.hpp"

basicBlocClass::basicBlocClass(std::string name, int x, int y)
{
    type = name;
    skin.setTexture(spriteClass::getImage("skinItem"));

    if(type == "WALL")
    {
        skin.setTextureRect(sf::IntRect(0, 0, 20, 20));
        solidBlock = true;
        solidLaserBlock = true;
    }
    else if(type == "LAVA")
    {
        skin.setTextureRect(sf::IntRect(20, 0, 20, 20));
        damageBlock = true;
        valueDamage = 20;
    }
    else if(type == "MINE")
    {
        skin.setTextureRect(sf::IntRect(20, 20, 20, 20));
        damageBlock = true;
        tempBlock = true;
        valueDamage = 15;
    }
    else if(type == "MEDIKIT")
    {
        skin.setTextureRect(sf::IntRect(0, 20, 20, 20));
        damageBlock = true;
        tempBlock = true;
        valueDamage = -15;
    }
    else if(type == "BLOCK_DOWN")
    {
        skin.setTextureRect(sf::IntRect(40, 0, 20, 20));
        moveDownBlock = true;
    }
    else if(type == "BLOCK_UP")
    {
        skin.setTextureRect(sf::IntRect(40, 20, 20, 20));
        moveUpBlock = true;
    }
    else if(type == "BLOCK_LEFT")
    {
        skin.setTextureRect(sf::IntRect(40, 40, 20, 20));
        moveLeftBlock = true;
    }
    else if(type == "BLOCK_RIGHT")
    {
        skin.setTextureRect(sf::IntRect(20, 40, 20, 20));
        moveRightBlock = true;
    }
    else if(type == "STAIR_RIGHT")
    {
        skin.setTextureRect(sf::IntRect(60, 0, 20, 20));
        moveLeftBlock = true;
        moveUpBlock = true;
        stairRight = true;
    }
    else if(type == "STAIR_LEFT")
    {
        skin.setTextureRect(sf::IntRect(60, 20, 20, 20));
        moveRightBlock = true;
        moveUpBlock = true;
        stairLeft = true;
    }
    else if(type == "WALL_LIGHT")
    {
        skin.setTextureRect(sf::IntRect(60, 40, 20, 20));
        blockLight = true;
        solidBlock = true;
        solidLaserBlock = true;
    }
    else
    {
        skin.setTextureRect(sf::IntRect(0, 0, 20, 20));
    }

    skin.setPosition(x * 20, y * 20);
}
