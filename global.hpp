#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SFML/Graphics.hpp>

class globalClass
{
public:
    static sf::Clock& getTimer();
    static double& getTimeFrame();
    static sf::Font& getFont();
    static bool& getSmoothLighting();
private:
    static sf::Clock timer;
    static double timeFrame;
    static sf::Font font;
    static bool smoothLighting;
};

#endif
