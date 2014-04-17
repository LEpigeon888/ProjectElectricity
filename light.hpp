#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <SFML/Graphics.hpp>

struct wall
{
public:
    wall(sf::Vector2f p1, sf::Vector2f p2);
    sf::Vector2f& getPt1();
    sf::Vector2f& getPt2();
private:
    sf::Vector2f pt1;
    sf::Vector2f pt2;
};

struct wallEntity
{
public:
    wallEntity(int id);
    int getID();
private:
    int ID;
};

struct lightEntity
{
public:
    lightEntity();
    lightEntity(int id, bool d);
    int getID();
    bool getDynamic();
private:
    int ID;
    bool dynamic;
};

class lightClass
{
public:
    lightClass();
    lightClass(sf::Vector2f newPosition, float newIntensity, float newRadius, int newQuality, sf::Color newColor);
    ~lightClass();
    void draw(sf::RenderTarget *window);
    void generate(std::vector<wall>& wallList, int poseX, int poseY);
    void addTriangle(sf::Vector2f pt1, sf::Vector2f pt2, int minimumWall, std::vector<wall>& wallList, int poseX, int poseY);
    sf::Vector2f intersect(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);
    sf::Vector2f collision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);
    void setIntensity(float newVal);
    void setRadius(float newVal);
    void setQuality(int newVal);
    void setColor(sf::Color newVal);
    void setPosition(sf::Vector2f newVal);
    void setActif(bool newVal);
    float getIntensity();
    float getRadius();
    int getQuality();
    sf::Color getColor();
    sf::Vector2f getPosition();
    bool getActif();
private:
    bool actif;
    sf::Vector2f position;
    float intensity;
    float radius;
    sf::Color color;
    std::vector<sf::VertexArray> shape;
    int quality;
};

#endif
