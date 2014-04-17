#include "particleMotor.hpp"

void particleMotorClass::update()
{
    for(std::list<particleClass>::iterator i = listOfParticle.begin(); i != listOfParticle.end(); )
    {
        i->update();
        if(i->getEnd() == true)
        {
            listOfParticle.erase(i++);
            continue;
        }
        ++i;
    }
}

void particleMotorClass::draw(sf::RenderWindow* window)
{
    for(std::list<particleClass>::iterator i = listOfParticle.begin(); i != listOfParticle.end(); ++i)
    {
        if(i->getStart() == true)
        {
            window->draw(i->getSprite());
        }
    }
}

void particleMotorClass::creatFlame(sf::Vector2f pose, sf::Vector2f size)
{
    listOfParticle.push_back(particleClass(sf::Vector2f(0, -1), sf::seconds(1), sf::seconds(0), "flameParticle", sf::Vector2f(pose.x, pose.y + (size.y / 2))));
    listOfParticle.push_back(particleClass(sf::Vector2f(0, -1), sf::seconds(1), sf::seconds(0), "flameParticle", sf::Vector2f(pose.x + size.x - 10, pose.y + (size.y / 2))));
    listOfParticle.push_back(particleClass(sf::Vector2f(0, -1), sf::seconds(1), sf::seconds(0), "flameParticle", sf::Vector2f(pose.x, pose.y + size.y - 20)));
    listOfParticle.push_back(particleClass(sf::Vector2f(0, -1), sf::seconds(1), sf::seconds(0), "flameParticle", sf::Vector2f(pose.x + size.x - 10, pose.y + size.y - 20)));
    listOfParticle.push_back(particleClass(sf::Vector2f(0, -1), sf::seconds(1), sf::seconds(0.5), "flameParticle", sf::Vector2f(pose.x + (size.x / 2) - 5, pose.y + (size.y / 2))));
    listOfParticle.push_back(particleClass(sf::Vector2f(0, -1), sf::seconds(1), sf::seconds(0.5), "flameParticle", sf::Vector2f(pose.x + (size.x / 2) - 5, pose.y + size.y - 20)));
}

void particleMotorClass::creatExplosion(sf::Vector2f pose, sf::Vector2f size)
{
    listOfParticle.push_back(particleClass(sf::Vector2f(0, 0), sf::seconds(0.5), sf::seconds(0), "explosionParticle", sf::Vector2f(pose.x + (size.x / 2) - 5, pose.y + (size.y / 2) - 5)));
    listOfParticle.push_back(particleClass(sf::Vector2f(0, 0), sf::seconds(0.5), sf::seconds(0.25), "explosionParticle", sf::Vector2f(pose.x, pose.y)));
    listOfParticle.push_back(particleClass(sf::Vector2f(0, 0), sf::seconds(0.5), sf::seconds(0.25), "explosionParticle", sf::Vector2f(pose.x + size.x - 10, pose.y)));
}
