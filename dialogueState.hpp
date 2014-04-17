#ifndef DIALOGUESTATE_HPP
#define DIALOGUESTATE_HPP

#include "gameState.hpp"

class dialogueStateClass : public gameStateClass
{
public:
    dialogueStateClass(std::string newmessage);
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
private:
    std::string message;
    sf::Font font;
    sf::Text messageText;
};

#endif
