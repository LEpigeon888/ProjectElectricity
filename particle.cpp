#include "particle.hpp"
#include "sprite.hpp"

particleClass::particleClass(sf::Vector2f newMoveVector, sf::Time newLiveTime, sf::Time newStartTime, std::string nameImage, sf::Vector2f poseActu)
{
    moveVector = newMoveVector;
    liveTime = newLiveTime;
    startTime = newStartTime;
    particle.setTexture(spriteClass::getImage(nameImage));
    particle.setPosition(poseActu);
    isStart = false;
    isEnd = false;

    time.restart();
}

void particleClass::update()
{
    if(isStart)
    {
        particle.move(moveVector);
    }

    if(isStart == false)
    {
        if(time.getElapsedTime() > startTime)
        {
            isStart = true;
            time.restart();
        }
    }
    else if(time.getElapsedTime() > liveTime)
    {
        isEnd = true;
    }
}

const sf::Sprite& particleClass::getSprite()
{
    return particle;
}

bool particleClass::getStart()
{
    return isStart;
}

bool particleClass::getEnd()
{
    return isEnd;
}
