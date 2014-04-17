#ifndef ENDGAMESTATE_HPP
#define ENDGAMESTATE_HPP

#include "gameState.hpp"

class endGameStateClass : public gameStateClass
{
public:
    endGameStateClass(bool setwin);
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
    void drawMessage(std::string message, float x, float y);
private:
    bool win;
    int modeSelect;
    sf::Font font;
    sf::RectangleShape cursor;
};

#endif

