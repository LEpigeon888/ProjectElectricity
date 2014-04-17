#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class particleClass
{
public:
    particleClass(sf::Vector2f newMoveVector, sf::Time newLiveTime, sf::Time newStartTime, std::string nameImage, sf::Vector2f poseActu);
    void update();
    const sf::Sprite& getSprite();
    bool getStart();
    bool getEnd();
private:
    sf::Clock time;
    sf::Vector2f moveVector;
    sf::Time liveTime;
    sf::Time startTime;
    sf::Sprite particle;
    bool isStart;
    bool isEnd;
};

#endif
