#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "gameState.hpp"
#include "libMenuSf.hpp"

class mainMenuStateClass : public gameStateClass
{
public:
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void update();
    void draw();
    bool checkSave();
private:
    msf::menuSfClass menu;
    int numberSubMenu;
    int numberEntrySubMenu;
    bool saveExist;
};

#endif
