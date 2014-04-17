#include "sprite.hpp"

sf::Texture spriteClass::image[15];

void spriteClass::initText()
{
    image[0].loadFromFile("background.png");
    image[1].loadFromFile("player.png");
    image[2].loadFromFile("enemy.png");
    image[3].loadFromFile("skinItem.png");
    image[4].loadFromFile("explosiveEnemy.png");
    image[5].loadFromFile("laserEnemy.png");
    image[6].loadFromFile("laser.png");
    image[7].loadFromFile("coin.png");
    image[8].loadFromFile("turret.png");
    image[9].loadFromFile("laserShipEnemy.png");
    image[10].loadFromFile("beam.png");
    image[11].loadFromFile("laserPosi.png");
    image[12].loadFromFile("bossEnemy.png");
    image[13].loadFromFile("explosionParticle.png");
    image[14].loadFromFile("flameParticle.png");
}

sf::Texture& spriteClass::getImage(std::string nameImage)
{
    if(nameImage == "background")
        return image[0];
    else if(nameImage == "player")
        return image[1];
    else if(nameImage == "enemy")
        return image[2];
    else if(nameImage == "skinItem")
        return image[3];
    else if(nameImage == "explosiveEnemy")
        return image[4];
    else if(nameImage == "laserEnemy")
        return image[5];
    else if(nameImage == "laser")
        return image[6];
    else if(nameImage == "coin")
        return image[7];
    else if(nameImage == "turret")
        return image[8];
    else if(nameImage == "laserShipEnemy")
        return image[9];
    else if(nameImage == "beam")
        return image[10];
    else if(nameImage == "laserPosi")
        return image[11];
    else if(nameImage == "boss")
        return image[12];
    else if(nameImage == "explosionParticle")
        return image[13];
    else if(nameImage == "flameParticle")
        return image[14];

    return image[7];
}
