#include "storeState.hpp"
#include "gameStateStack.hpp"

playerClass* storeStateClass::player;

void storeStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
    window->setView(window->getDefaultView());
    font.loadFromFile("cour.ttf");
    cursor.setFillColor(sf::Color::Black);
    cursor.setSize(sf::Vector2f(10, 10));
    cursor.setPosition(225, 216);
    modeSelect = 0;
    typeSelect = 1;
    numberModeOfType = 4;
}

void storeStateClass::update()
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
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                    modeSelect -= 1;
                    if(modeSelect < 0)
                        modeSelect = numberModeOfType;
                    cursor.setPosition(225, 216 + (50 * modeSelect));
                    break;

                case sf::Keyboard::Down:
                    modeSelect += 1;
                    if(modeSelect > numberModeOfType)
                        modeSelect = 0;
                    cursor.setPosition(225, 216 + (50 * modeSelect));
                    break;

                case sf::Keyboard::Return:
                    if(typeSelect == 1)
                    {
                        if(modeSelect == 0 && player->getMoney() > 0 && player->getSpeed() < 58)
                        {
                            player->moveMoney(-1);
                            player->moveUpgrad(1, "speed");
                        }
                        else if(modeSelect == 1 && player->getMoney() > 0 && player->getJumpPower() < 98)
                        {
                            player->moveMoney(-1);
                            player->moveUpgrad(1, "jump");
                        }
                        else if(modeSelect == 2 && player->getMoney() > 0)
                        {
                            player->moveMoney(-1);
                            player->moveUpgrad(0.1, "damage");
                        }
                        else if(modeSelect == 3 && player->getMoney() > 0)
                        {
                            player->moveMoney(-1);
                            player->moveUpgrad(0.05, "resistance");
                        }
                        else if(modeSelect == 4 && player->getMoney() > 0)
                        {
                            player->moveMoney(-1);
                            player->moveUpgrad(10, "life");
                        }
                    }
                    else if(typeSelect == 2)
                    {
                        if(modeSelect == 0)
                        {
                            player->setWeapon("FISTS");
                        }
                        else if(modeSelect == 1)
                        {
                            if(player->getWeaponInStore("LASER_RIFLE"))
                            {
                                player->setWeapon("LASER_RIFLE");
                            }
                            else if(player->getMoney() > 9)
                            {
                                player->moveMoney(-10);
                                player->setWeaponInStore(true, "LASER_RIFLE");
                                player->setWeapon("LASER_RIFLE");
                            }
                        }
                    }
                    break;

                case sf::Keyboard::Escape:
                    parent->pop();
                    return;

                case sf::Keyboard::Num1:
                    if(typeSelect != 1)
                    {
                        numberModeOfType = 4;
                        typeSelect = 1;
                        modeSelect = 0;
                        cursor.setPosition(225, 216 + (50 * modeSelect));
                    }
                    break;

                case sf::Keyboard::Num2:
                    if(typeSelect != 2)
                    {
                        numberModeOfType = 1;
                        typeSelect = 2;
                        modeSelect = 0;
                        cursor.setPosition(225, 216 + (50 * modeSelect));
                    }
                    break;

                default:
                    break;
            }

        }
    }
}

void storeStateClass::draw()
{
    window->clear(sf::Color::White);
    drawMessage("Upgrad", 10, 10, typeSelect == 1 ? sf::Color::Red : sf::Color::Black);
    drawMessage("Weapons", 150, 10, typeSelect == 2 ? sf::Color::Red : sf::Color::Black);
    if(typeSelect == 1)
    {

        drawMessage("Speed", 240, 200);
        drawMessage("(1 coin)", 330, 220,sf::Color::Black, 10);
        drawMessage(": " + player->getUpgradInString("speed"), 400, 200);
        drawMessage("Jump", 240, 250);
        drawMessage("(1 coin)", 310, 270,sf::Color::Black, 10);
        drawMessage(": " + player->getUpgradInString("jump"), 400, 250);
        drawMessage("Damage", 240, 300);
        drawMessage("(1 coin)", 350, 320,sf::Color::Black, 10);
        drawMessage(": " + player->getUpgradInString("damage"), 400, 300);
        drawMessage("Resist", 240, 350);
        drawMessage("(1 coin)", 350, 370,sf::Color::Black, 10);
        drawMessage(": " + player->getUpgradInString("resistance"), 400, 350);
        drawMessage("Life", 240, 400);
        drawMessage("(1 coin)", 310, 420,sf::Color::Black, 10);
        drawMessage(": " + player->getUpgradInString("life"), 400, 400);
    }
    else if(typeSelect == 2)
    {
        drawMessage("Fists", 280, 200, player->getWeapon() == "FISTS" ? sf::Color::Yellow : sf::Color::Green);
        drawMessage("Laser rifle", 240, 250, player->getWeapon() == "LASER_RIFLE" ? sf::Color::Yellow : (player->getWeaponInStore("LASER_RIFLE") ? sf::Color::Green : sf::Color::Red));
        if(!player->getWeaponInStore("LASER_RIFLE"))
        {
            drawMessage("(10 coin)", 440, 270,sf::Color::Red, 10);
        }
    }
    drawMessage("To leave, press escape.", 10, 460, sf::Color::Black, 15);
    drawMessage("Coin : " + player->getMoneyInString(), 530, 460, sf::Color::Black, 15);
    window->draw(cursor);
}

void storeStateClass::drawMessage(std::string message, float x, float y, sf::Color color, int size)
{
    sf::Text textMessage(message, font, size);
    textMessage.setPosition(x, y);
    textMessage.setColor(color);
    window->draw(textMessage);
}

void storeStateClass::setPlayer(playerClass* newPlayer)
{
    player = newPlayer;
}
