#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics.hpp>

class spriteClass
{
public:
    static void initText();
    static sf::Texture& getImage(std::string);
private:
    static sf::Texture image[15];
};

#endif
