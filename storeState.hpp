#ifndef STORESTATE_HPP
#define STORESTATE_HPP

#include "gameState.hpp"
#include "player.hpp"

class storeStateClass : public gameStateClass
{
public:
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
    void drawMessage(std::string message, float x, float y, sf::Color color = sf::Color::Black, int size = 30);
    static void setPlayer(playerClass* player);
private:
    static playerClass* player;
    int modeSelect;
    int typeSelect;
    int numberModeOfType;
    sf::Font font;
    sf::RectangleShape cursor;
};

#endif
