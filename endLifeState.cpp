#include "endLifeState.hpp"
#include "gameStateStack.hpp"

endLifeStateClass::endLifeStateClass(std::string life)
{
    menu.changeSet(sf::Color::White);
    menu.addToStaticList("Il te reste " + life + " vie(s).", 20, 20);
    menu.addToMoveList("Continue", 280, 200);
    menu.addToMoveList("Quit");
}

void endLifeStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
    window->setView(window->getDefaultView());
}

void endLifeStateClass::update()
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
            if(event.key.code == sf::Keyboard::Return)
            {
                if(menu.getSelectedMode() == 0)
                {
                    parent->pop();
                    return;
                }
                else if(menu.getSelectedMode() == 1)
                    window->close();
            }
            else
            {
                menu.update(event);
            }
        }
    }
}

void endLifeStateClass::draw()
{
    window->clear(sf::Color::Black);
    menu.draw(window);
}
