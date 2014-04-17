#ifndef ENDLIFESTATE_HPP
#define ENDLIFESTATE_HPP

#include "gameState.hpp"
#include "libMenuSf.hpp"

class endLifeStateClass : public gameStateClass
{
public:
    endLifeStateClass(std::string life);
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
private:
    msf::menuSfClass menu;
};

#endif

