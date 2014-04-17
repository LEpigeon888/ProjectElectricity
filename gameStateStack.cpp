#include "gameStateStack.hpp"

void gameStateStackClass::set(gameStateClass* state)
{
    while(!stateList.empty())
    {
        pop();
    }
    add(state);
}

void gameStateStackClass::add(gameStateClass* state)
{
    change = true;
    state->initialize(this, window);
    stateList.push_back(state);
}

void gameStateStackClass::pop()
{
    change = true;
    if(!stateList.empty())
    {
        delete stateList.back();
        stateList.pop_back();
    }
}

void gameStateStackClass::update()
{
    if(!stateList.empty())
    {
        stateList.back()->update();
    }
}

void gameStateStackClass::draw()
{
    if(!stateList.empty())
    {
        stateList.back()->draw();
    }
}

void gameStateStackClass::setWindow(sf::RenderWindow* newwindow)
{
    window = newwindow;
}

bool gameStateStackClass::getChange()
{
    return change;
}

void gameStateStackClass::setChange(bool val)
{
    change = val;
}
