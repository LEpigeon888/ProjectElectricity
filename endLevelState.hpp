#ifndef ENDLEVELSTATE_HPP
#define ENDLEVELSTATE_HPP

#include "gameState.hpp"

class endLevelStateClass : public gameStateClass
{
public:
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
    void drawMessage(std::string message, float x, float y);
private:
    int modeSelect;
    sf::Font font;
    sf::RectangleShape cursor;
};

#endif
