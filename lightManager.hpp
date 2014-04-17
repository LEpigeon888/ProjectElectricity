#ifndef LIGHTMANAGER_HPP
#define LIGHTMANAGER_HPP

#include "light.hpp"

class lightManagerClass
{
public:
    lightManagerClass();
    ~lightManagerClass();
    lightEntity addDynamicLight();
    lightEntity addDynamicLight(lightClass light);
    lightEntity addDynamicLight(sf::Vector2f newPosition, float newIntensity, float newRadius, int newQuality, sf::Color newColor);
    wallEntity addWall(sf::Vector2f pt1, sf::Vector2f pt2);
    void deleteLight(lightEntity light);
    void deleteWall(wallEntity wallActu);
    void deleteAllLight();
    void deleteAllWall();
    void generate();
    void generate(lightEntity light);
    void draw(sf::RenderWindow *window);
    void setPosition(lightEntity actuLight, sf::Vector2f newVal);
    void setQuality(lightEntity actuLight, int newVal);
    void setRadius(lightEntity actuLight, int newVal);
    void setColor(lightEntity actuLight, sf::Color newVal);
    void setIntensity(lightEntity actuLight, int newVal);
    void setPoseImg(int x, int y);
    float getIntensity(lightEntity actuLight);
    float getRadius(lightEntity actuLight);
    int getQuality(lightEntity actuLight);
    sf::Color getColor(lightEntity actuLight);
    sf::Vector2f getPosition(lightEntity actuLight);
    void setPosition(wallEntity wallActu, sf::Vector2f newVal);
    void unSmoothLighting();
private:
    sf::Shader blurEffect;
    std::vector<lightClass*>::iterator ite;
    sf::RenderTexture renderImg;
    sf::RenderTexture backgroundImg;
    std::vector<lightClass*> dynamicLight;
    std::vector<wall> wallList;
    sf::Color basicLight;
    int lightSmooth;
    int poseX;
    int poseY;
};

#endif
