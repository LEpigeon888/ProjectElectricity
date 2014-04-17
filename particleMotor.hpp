#ifndef PARTICLEMOTOR_HPP
#define PARTICLEMOTOR_HPP

#include <SFML/Graphics.hpp>
#include <list>

#include "particle.hpp"

class particleMotorClass
{
public:
    void update();
    void draw(sf::RenderWindow* window);
    void creatFlame(sf::Vector2f pose, sf::Vector2f size);
    void creatExplosion(sf::Vector2f pose, sf::Vector2f size);
private:
    std::list<particleClass> listOfParticle;
};

#endif
