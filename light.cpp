#include <math.h>

#include "light.hpp"

#define M_PI 3.14159265358979323846

lightEntity::lightEntity()
{
    dynamic = false;
    ID = 0;
}

wall::wall(sf::Vector2f p1, sf::Vector2f p2)
{
    pt1 = p1;
    pt2 = p2;
}

sf::Vector2f& wall::getPt1()
{
    return pt1;
}

sf::Vector2f& wall::getPt2()
{
    return pt2;
}

wallEntity::wallEntity(int id)
{
    ID = id;
}

int wallEntity::getID()
{
    return ID;
}

lightEntity::lightEntity(int id, bool d)
{
    ID = id;
    dynamic = d;
}

int lightEntity::getID()
{
    return ID;
}

bool lightEntity::getDynamic()
{
    return dynamic;
}

lightClass::lightClass()
{
    intensity = 0;
    radius = 0;
    quality = 0;
    actif = true;
}

lightClass::lightClass(sf::Vector2f newPosition, float newIntensity, float newRadius, int newQuality, sf::Color newColor)
{
    position = newPosition;
    intensity = newIntensity;
    radius = newRadius;
    quality = newQuality;
    color = newColor;
    actif = true;
}

lightClass::~lightClass()
{
    shape.clear();
}


void lightClass::draw(sf::RenderTarget *window)
{
    for(size_t i = 0; i < shape.size(); ++i)
    {
        window->draw(shape[i], sf::BlendAdd);
    }
}

void lightClass::addTriangle(sf::Vector2f pt1, sf::Vector2f pt2, int minimumWall, std::vector<wall>& wallList, int poseX, int poseY)
{
    int mW = minimumWall;
    for(std::vector<wall>::iterator iteWall = wallList.begin() + minimumWall; iteWall != wallList.end(); ++iteWall, ++mW)
    {
        sf::Vector2f l1(iteWall->getPt1().x - position.x - poseX, iteWall->getPt1().y - position.y - poseY);
        sf::Vector2f l2(iteWall->getPt2().x - position.x - poseX, iteWall->getPt2().y - position.y - poseY);

        if((l1.x * l1.x + l1.y * l1.y) < radius * radius)
        {
            sf::Vector2f i = intersect(pt1, pt2, sf::Vector2f(0,0), l1);

            if (pt1 != i && pt2 != i)
            {
                if((pt1.x >= i.x && pt2.x <= i.x) || (pt1.x <= i.x && pt2.x >= i.x))
                {
                    if((pt1.y >= i.y && pt2.y <= i.y) || (pt1.y <= i.y && pt2.y >= i.y))
                    {
                        if((l1.y >= 0 && i.y >= 0) || (l1.y <= 0 && i.y <= 0))
                        {
                            if((l1.x >= 0 && i.x >= 0) || (l1.x <= 0 && i.x <= 0))
                            {
                                addTriangle(i, pt2, mW, wallList, poseX, poseY);
                                pt2 = i;
                            }
                        }
                    }
                }
            }
        }
        if((l2.x * l2.x + l2.y * l2.y) < radius * radius)
        {
            sf::Vector2f i = intersect(pt1, pt2, sf::Vector2f(0,0), l2);

            if (pt1 != i && pt2 != i)
            {
                if((pt1.x >= i.x && pt2.x <= i.x) || (pt1.x <= i.x && pt2.x >= i.x))
                {
                    if((pt1.y >= i.y && pt2.y <= i.y) || (pt1.y <= i.y && pt2.y >= i.y))
                    {
                        if((l2.y >= 0 && i.y >= 0) || (l2.y <= 0 && i.y <= 0))
                        {
                            if((l2.x >= 0 && i.x >= 0) || (l2.x <= 0 && i.x <= 0))
                            {
                                addTriangle(pt1, i, mW, wallList, poseX, poseY);
                                pt1 = i;
                            }
                        }
                    }
                }
            }
        }

        sf::Vector2f m = collision(l1, l2, sf::Vector2f(0,0), pt1);
        sf::Vector2f n = collision(l1, l2, sf::Vector2f(0,0), pt2);
        sf::Vector2f o = collision(l1, l2, pt1, pt2);

        if((m.x != 0 || m.y != 0) && (n.x != 0 || n.y != 0))
        {
            pt1 = m;
            pt2 = n;
        }
        else
        {
            if((m.x != 0 || m.y != 0) && (o.x != 0 || o.y != 0))
            {
                addTriangle(m, o, mW, wallList, poseX, poseY);
                pt1 = o;
            }

            if((n.x != 0 || n.y != 0) && (o.x != 0 || o.y != 0))
            {
                addTriangle(o, n, mW, wallList, poseX, poseY);
                pt2 = o;
            }
        }
    }

    float tmpIntensity;

    shape.push_back(sf::VertexArray());
    shape.back().setPrimitiveType(sf::Triangles);

    shape.back().append(sf::Vertex(position, sf::Color((int)(intensity*color.r/255), (int)(intensity*color.g/255), (int)(intensity*color.b/255))));

    tmpIntensity = intensity-sqrt(pt1.x*pt1.x + pt1.y*pt1.y)*intensity/radius;
    shape.back().append(sf::Vertex(position + pt1, sf::Color((int)(tmpIntensity*color.r/255), (int)(tmpIntensity*color.g/255), (int)(tmpIntensity*color.b/255))));

    tmpIntensity = intensity-sqrt(pt2.x*pt2.x + pt2.y*pt2.y)*intensity/radius;
    shape.back().append(sf::Vertex(position + pt2, sf::Color((int)(tmpIntensity*color.r/255), (int)(tmpIntensity*color.g/255), (int)(tmpIntensity*color.b/255))));
}

void lightClass::generate(std::vector<wall>& wallList, int poseX, int poseY)
{
    shape.clear();

    float buf = (M_PI*2)/(float)quality;

    for(int i = 0; i < quality; ++i)
    {
        addTriangle(sf::Vector2f((float)((float)radius*cos((float)i*buf)), (float)((float)radius*sin((float)i*buf))), sf::Vector2f((float)((float)radius*cos((float)(i+1)*buf)), (float)((float)radius*sin((float)(i+1)*buf))), 0, wallList, poseX, poseY);
    }
}

sf::Vector2f lightClass::intersect(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
    sf::Vector2f i;

    if(((p2.x - p1.x) == 0 && (q2.x - q1.x) == 0))
    {
        i.x = 0;
        i.y = 0;
    }
    else if((p2.x - p1.x) == 0)
    {
        i.x = p1.x;

        float c = (q2.y - q1.y) / (q2.x - q1.x);
        float d = q1.y - q1.x * c;

        i.y = c * i.x + d;
    }

    else if((q2.x - q1.x) == 0)
    {
        i.x = q1.x;

        float a = (p2.y - p1.y) / (p2.x - p1.x);
        float b = p1.y - p1.x * a;

        i.y = a * i.x + b;
    }
    else
    {
        float a = (p2.y - p1.y) / (p2.x - p1.x);
        float b = p1.y - p1.x * a;

        float c = (q2.y - q1.y) / (q2.x - q1.x);
        float d = q1.y - q1.x * c;

        if(a == c)
        {
            i.x = 0;
            i.y = 0;
        }
        else
        {
            i.x = (d-b)/(a-c);
            i.y = a * i.x + b;
        }
    }

    return i;
}

sf::Vector2f lightClass::collision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
    sf::Vector2f i;
    i = intersect(p1, p2, q1, q2);

    if(((i.x >= p1.x - 0.1 && i.x <= p2.x + 0.1) || (i.x >= p2.x - 0.1 && i.x <= p1.x + 0.1)) && ((i.x >= q1.x - 0.1 && i.x <= q2.x + 0.1) || (i.x >= q2.x - 0.1 && i.x <= q1.x + 0.1)) && ((i.y >= p1.y - 0.1 && i.y <= p2.y + 0.1) || (i.y >= p2.y - 0.1 && i.y <= p1.y + 0.1)) && ((i.y >= q1.y - 0.1 && i.y <= q2.y + 0.1) || (i.y >= q2.y - 0.1 && i.y <= q1.y + 0.1)))
    {
        return i;
    }
    else
    {
        return sf::Vector2f (0,0);
    }
}

void lightClass::setIntensity(float newVal)
{
    intensity = newVal;
}

void lightClass::setRadius(float newVal)
{
    radius = newVal;
}

void lightClass::setQuality(int newVal)
{
    quality = newVal;
}

void lightClass::setColor(sf::Color newVal)
{
    color = newVal;
}

void lightClass::setPosition(sf::Vector2f newVal)
{
    position = newVal;
}

void lightClass::setActif(bool newVal)
{
    actif = newVal;
}

float lightClass::getIntensity()
{
    return intensity;
}

float lightClass::getRadius()
{
    return radius;
}

int lightClass::getQuality()
{
    return quality;
}

sf::Vector2f lightClass::getPosition()
{
    return position;
}

sf::Color lightClass::getColor()
{
    return color;
}

bool lightClass::getActif()
{
    return actif;
}
