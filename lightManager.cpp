#include "lightManager.hpp"
#include "global.hpp"

lightManagerClass::lightManagerClass()
{
    lightSmooth = 0;
    basicLight = sf::Color::Black;
    poseX = 0;
    poseY = 0;

    blurEffect.loadFromFile("blur.frag", sf::Shader::Fragment);
    blurEffect.setParameter("texture", sf::Shader::CurrentTexture);

    renderImg.create(640, 480);
}

lightManagerClass::~lightManagerClass()
{
    for(size_t i = 0; i < dynamicLight.size(); ++i)
    {
        delete dynamicLight[i];
    }

    dynamicLight.clear();
}

lightEntity lightManagerClass::addDynamicLight()
{
    dynamicLight.push_back(new lightClass());
    return lightEntity((int)dynamicLight.size() - 1, true);
}

lightEntity lightManagerClass::addDynamicLight(lightClass light)
{
    dynamicLight.push_back(new lightClass(light));
    return lightEntity((int)dynamicLight.size() - 1, true);
}

lightEntity lightManagerClass::addDynamicLight(sf::Vector2f newPosition, float newIntensity, float newRadius, int newQuality, sf::Color newColor)
{
    dynamicLight.push_back(new lightClass(sf::Vector2f(newPosition.x - poseX, newPosition.y - poseY), newIntensity, newRadius, newQuality, newColor));
    return lightEntity((int)dynamicLight.size() - 1, true);
}

wallEntity lightManagerClass::addWall(sf::Vector2f pt1, sf::Vector2f pt2)
{
    for(int i = 0; i < (int)wallList.size(); i++)
    {
        if((pt1.y - pt2.y) / (pt1.x - pt2.y) == (wallList[i].getPt1().y - wallList[i].getPt2().y) / (wallList[i].getPt1().x - wallList[i].getPt2().y))
        {
            if(pt1 == wallList[i].getPt1() || pt2 == wallList[i].getPt1() || pt1 == wallList[i].getPt2() || pt2 == wallList[i].getPt2())
            {
                sf::Vector2f min=pt1;
                sf::Vector2f max=pt2;

                if(pt2.x < min.x)
                {
                    min.x = pt2.x;
                }
                if(pt1.x > max.x)
                {
                    max.x = pt2.x;
                }

                if(wallList[i].getPt1().x < min.x)
                {
                    min.x = wallList[i].getPt1().x;
                }
                if(wallList[i].getPt2().x < min.x)
                {
                    min.x = wallList[i].getPt2().x;
                }

                if(wallList[i].getPt1().x > max.x)
                {
                    max.x = wallList[i].getPt1().x;
                }
                if(wallList[i].getPt2().x > max.x)
                {
                    max.x = wallList[i].getPt2().x;
                }

                if(pt2.y < min.y)
                {
                    min.y = pt2.y;
                }
                if(pt1.y > max.y)
                {
                    max.y = pt2.y;
                }

                if(wallList[i].getPt1().y < min.y)
                {
                    min.y = wallList[i].getPt1().y;
                }
                if(wallList[i].getPt2().y < min.y)
                {
                    min.y = wallList[i].getPt2().y;
                }

                if(wallList[i].getPt1().y > max.y)
                {
                    max.y = wallList[i].getPt1().y;
                }
                if(wallList[i].getPt2().y > max.y)
                {
                    max.y = wallList[i].getPt2().y;
                }

                wallList[i].getPt1() = min;
                wallList[i].getPt2() = max;

                return wallEntity(i);
            }
        }
    }
    wallList.push_back(wall(pt1, pt2));
    return wallEntity(wallList.size() - 1);
}

void lightManagerClass::deleteLight(lightEntity light)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            dynamicLight[light.getID()]->setActif(false);
        }
    }
}

void lightManagerClass::deleteAllLight()
{
    for(size_t i = 0; i < dynamicLight.size(); ++i)
    {
        delete dynamicLight[i];
    }

    dynamicLight.clear();
}

void lightManagerClass::deleteWall(wallEntity wallActu)
{
    wallList.erase(wallList.begin() + wallActu.getID());
}

void lightManagerClass::deleteAllWall()
{
    wallList.clear();
}

void lightManagerClass::generate()
{
    renderImg.clear(basicLight);
    blurEffect.setParameter("offset",0.005 * lightSmooth);

    for(ite = dynamicLight.begin(); ite != dynamicLight.end(); ++ite)
    {
        if((*ite)->getActif())
        {
            (*ite)->generate(wallList, poseX, poseY);
            (*ite)->draw(&renderImg);
        }
    }
    renderImg.display();

    if(globalClass::getSmoothLighting() == false)
    {
        unSmoothLighting();
    }
}


void lightManagerClass::generate(lightEntity light)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            dynamicLight[light.getID()]->generate(wallList, poseX, poseY);
        }
    }
}

void lightManagerClass::draw(sf::RenderWindow *window)
{
    sf::RenderStates r(sf::BlendMultiply);
    if(globalClass::getSmoothLighting() == true)
    {
        r.shader = &blurEffect;
    }
    sf::Sprite tmpSprite(renderImg.getTexture());
    tmpSprite.setPosition(poseX, poseY);
    window->draw(tmpSprite, r);
}

void lightManagerClass::setPosition(lightEntity light, sf::Vector2f newVal)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            dynamicLight[light.getID()]->setPosition(sf::Vector2f(newVal.x - poseX, newVal.y - poseY));
        }
    }
}

void lightManagerClass::setQuality(lightEntity light, int newVal)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            dynamicLight[light.getID()]->setQuality(newVal);
        }
    }
}

void lightManagerClass::setRadius(lightEntity light, int newVal)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            dynamicLight[light.getID()]->setRadius(newVal);
        }
    }
}

void lightManagerClass::setColor(lightEntity light, sf::Color newVal)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            dynamicLight[light.getID()]->setColor(newVal);
        }
    }
}

void lightManagerClass::setIntensity(lightEntity light, int newVal)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            dynamicLight[light.getID()]->setIntensity(newVal);
        }
    }
}

void lightManagerClass::setPoseImg(int x, int y)
{
    poseX = x;
    poseY = y;
}

void lightManagerClass::setPosition(wallEntity wallActu, sf::Vector2f newVal)
{
    if(wallActu.getID() >= 0 && wallActu.getID() < (int)wallList.size())
    {
        sf::Vector2f buffer = wallList[wallActu.getID()].getPt1();
        wallList[wallActu.getID()].getPt1() = newVal;
        wallList[wallActu.getID()].getPt2().x = wallList[wallActu.getID()].getPt2().x + (newVal.x - buffer.x);
        wallList[wallActu.getID()].getPt2().y = wallList[wallActu.getID()].getPt2().y + (newVal.y - buffer.y);
    }
}

float lightManagerClass::getIntensity(lightEntity light)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            return dynamicLight[light.getID()]->getIntensity();
        }
    }
    return 0;
}
float lightManagerClass::getRadius(lightEntity light)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            return dynamicLight[light.getID()]->getRadius();
        }
    }
    return 0;
}
int lightManagerClass::getQuality(lightEntity light)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            return dynamicLight[light.getID()]->getQuality();
        }
    }

    return 0;
}
sf::Color lightManagerClass::getColor(lightEntity light)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            return dynamicLight[light.getID()]->getColor();
        }
    }

    return sf::Color(0,0,0);
}
sf::Vector2f lightManagerClass::getPosition(lightEntity light)
{
    if(light.getDynamic())
    {
        if(light.getID() >= 0 && light.getID() < (int)dynamicLight.size())
        {
            return dynamicLight[light.getID()]->getPosition();
        }
    }

    return sf::Vector2f(0,0);
}

void lightManagerClass::unSmoothLighting()
{
    sf::Image tmpImage;
    tmpImage = renderImg.getTexture().copyToImage();
    renderImg.clear(sf::Color::Black);

    for(int i = 0; i < 64; ++i)
    {
        for(int j = 0; j < 48; j++)
        {
            sf::RectangleShape tmpRect;
            tmpRect.setSize(sf::Vector2f(10, 10));
            tmpRect.setPosition(i * 10, j * 10);
            tmpRect.setFillColor(tmpImage.getPixel(i * 10 + 5, j * 10 + 5));

            renderImg.draw(tmpRect);
        }
    }

    renderImg.display();
}
