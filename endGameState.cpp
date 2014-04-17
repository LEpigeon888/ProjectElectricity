#include "endGameState.hpp"
#include "mainMenuState.hpp"
#include "playState.hpp"

endGameStateClass::endGameStateClass(bool setwin)
{
    win = setwin;
}

void endGameStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
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

void endGameStateClass::update()
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
                    modeSelect = 2;
                cursor.setPosition(265, 216 + (50 * modeSelect));
            }
            else if(event.key.code == sf::Keyboard::Down)
            {
                modeSelect += 1;
                if(modeSelect > 2)
                    modeSelect = 0;
                cursor.setPosition(265, 216 + (50 * modeSelect));
            }
            else if(event.key.code == sf::Keyboard::Return)
            {
                if(modeSelect == 0)
                {
                    parent->set(new playStateClass);
                    return;
                }
                else if(modeSelect == 1)
                {
                    parent->set(new mainMenuStateClass);
                    return;
                }
                else if(modeSelect == 2)
                    window->close();
            }
        }
    }
}

void endGameStateClass::draw()
{
    window->clear(sf::Color::Black);
    drawMessage( win ? "GG MONSIEUR LE PGM" : "KOM T NUL", 10, 10);
    drawMessage("Restart", 280, 200);
    drawMessage("Menu", 280, 250);
    drawMessage("Quit", 280, 300);
    window->draw(cursor);
}

void endGameStateClass::drawMessage(std::string message, float x, float y)
{
    sf::Text textMessage(message, font, 30);
    textMessage.setPosition(x, y);
    textMessage.setColor(sf::Color::White);
    window->draw(textMessage);
}
