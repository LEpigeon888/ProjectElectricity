#include "endLevelState.hpp"
#include "mainMenuState.hpp"
#include "storeState.hpp"
#include "gameStateStack.hpp"

void endLevelStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
    window->setView(window->getDefaultView());
    font.loadFromFile("cour.ttf");
    cursor.setFillColor(sf::Color::White);
    cursor.setSize(sf::Vector2f(10, 10));
    cursor.setPosition(265, 216);
    modeSelect = 0;
}

void endLevelStateClass::update()
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
            if(event.key.code == sf::Keyboard::Up)
            {
                modeSelect -= 1;
                if(modeSelect < 0)
                    modeSelect = 3;
                cursor.setPosition(265, 216 + (50 * modeSelect));
            }
            else if(event.key.code == sf::Keyboard::Down)
            {
                modeSelect += 1;
                if(modeSelect > 3)
                    modeSelect = 0;
                cursor.setPosition(265, 216 + (50 * modeSelect));
            }
            else if(event.key.code == sf::Keyboard::Return)
            {
                if(modeSelect == 0)
                {
                    parent->pop();
                    return;
                }
                else if(modeSelect == 1)
                {
                    parent->add(new storeStateClass);
                    return;
                }
                else if(modeSelect == 2)
                {
                    parent->set(new mainMenuStateClass);
                    return;
                }
                else if(modeSelect == 3)
                    window->close();
            }
        }
    }
}

void endLevelStateClass::draw()
{
    window->clear(sf::Color::Black);
    drawMessage("Gnablablablabla.", 10, 10);
    drawMessage("Continue", 280, 200);
    drawMessage("Store", 280, 250);
    drawMessage("Menu", 280, 300);
    drawMessage("Quit", 280, 350);
    window->draw(cursor);
}

void endLevelStateClass::drawMessage(std::string message, float x, float y)
{
    sf::Text textMessage(message, font, 30);
    textMessage.setPosition(x, y);
    textMessage.setColor(sf::Color::White);
    window->draw(textMessage);
}
