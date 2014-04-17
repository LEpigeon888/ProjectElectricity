#include "dialogueState.hpp"
#include "gameStateStack.hpp"

dialogueStateClass::dialogueStateClass(std::string newmessage)
{
    message = newmessage;
    font.loadFromFile("cour.ttf");
    messageText.setFont(font);
    messageText.setCharacterSize(20);
    messageText.setColor(sf::Color::White);
    messageText.setString(message);
    messageText.setPosition(20.f, 20.f);
}

void dialogueStateClass::initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow)
{
    parent = newparent;
    window = newwindow;
    window->setView(window->getDefaultView());
}

void dialogueStateClass::update()
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
                parent->pop();
                return;
            }
        }
    }
}

void dialogueStateClass::draw()
{
    window->clear(sf::Color::Black);
    window->draw(messageText);
}
