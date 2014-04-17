#include "playState.hpp"
#include "pauseState.hpp"
#include <iostream>

playStateClass::playStateClass()
{
    error = false;
}

playStateClass::playStateClass(int level, int life, int money, int speedUpgrad, int jumpUpgrad, double damageUpgrad, double resistanceUpgrad, int lifeUpgrad, bool getLaserRifle, std::string weaponActu)
{
    error = gamePlayed.setLevelClass().setNumberLevel(level);
    if(error == false)
    {
        gamePlayed.newLevel();
    }
    gamePlayed.setPlayer().setNumberOfLife(life);
    gamePlayed.setPlayer().setMoney(money);
    gamePlayed.setPlayer().moveUpgrad(speedUpgrad, "speed");
    gamePlayed.setPlayer().moveUpgrad(jumpUpgrad, "jump");
    gamePlayed.setPlayer().moveUpgrad(damageUpgrad, "damage");
    gamePlayed.setPlayer().moveUpgrad(resistanceUpgrad, "resistance");
    gamePlayed.setPlayer().moveUpgrad(lifeUpgrad, "life");
    gamePlayed.setPlayer().setWeaponInStore(getLaserRifle, "LASER_RIFLE");
    gamePlayed.setPlayer().setWeapon(weaponActu);
    gamePlayed.setNoJump(gamePlayed.setPlayer());
}

void playStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
    gamePlayed.setWindowAndStack(newwindow, newparent);
    velocity = 0.f;
    if(error == true)
    {
        std::cout << "met pas des niveaux au pif couillon";
        window->close();
    }
}

void playStateClass::update()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if((event.type == sf::Event::Closed))
        {
            window->close();
            break;
        }

        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Space)
            {
                gamePlayed.setStrikePlayer();
            }
            else if(event.key.code == sf::Keyboard::Up)
            {
                gamePlayed.setJumpingPlayer();
            }
            else if(event.key.code == sf::Keyboard::Escape)
            {
                parent->add(new pauseStateClass(&gamePlayed));
            }
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity += 1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity -= 1;

    gamePlayed.updatePlayer();
    gamePlayed.movePlayer(velocity);

    velocity = 0;

    gamePlayed.update();
}

void playStateClass::draw()
{
    window->clear(sf::Color::White);
    gamePlayed.draw();
}
