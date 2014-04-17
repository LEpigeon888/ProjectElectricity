#include "bossEnemy.hpp"
#include "sprite.hpp"

bossEnemyClass::bossEnemyClass(float x, float y, std::string newType)
{
    type = newType;
    affectToGravity = false;
    affectToWall = false;
    staticChara = true;
    changeDir = false;
    directDamage = false;
    isBoss = true;
    life = 20;
    speed = 0;
    jumpPower = 0;
    damage = 10.f;
    speedJump = jumpPower;
    posePlayer.x = x, posePlayer.y = y;
    spriteSheet.resize(1);
    initialize();
    updatePoseSprite();
    timeStrikeWaitIsStart = false;
    timeStrikeIsStartWeapons[0] = false;
    timeStrikeIsStartWeapons[1] = false;
    currentWeapon = 0;
    dirChara = RIGHT;
    typeWeapon = "LASER_RIFLE";
}

const sf::Sprite& bossEnemyClass::getSpriteDraw()
{
    return spriteSheet[0];
}
const sf::RectangleShape bossEnemyClass::getColliBox()
{
    sf::RectangleShape colliBox;
    colliBox.setPosition(posePlayer.x, posePlayer.y);
    colliBox.setSize(sf::Vector2f(getSpriteDraw().getGlobalBounds().width, getSpriteDraw().getGlobalBounds().height));
    return colliBox;
}

void bossEnemyClass::update()
{
    ++frame %= 10;
    timeInvincible.update();
    timeStrike.update();
    timeStrikWait.update();
    timeStrikeWeapons[0].update();
    timeStrikeWeapons[1].update();
    if(timeStrikeIsStartWeapons[0])
    {
        if(timeStrikeWeapons[0].getTime() > 2.)
        {
            timeStrikeIsStartWeapons[0] = false;
        }
    }
    if(timeStrikeIsStartWeapons[1])
    {
        if(timeStrikeWeapons[1].getTime() > 2.)
        {
            timeStrikeIsStartWeapons[1] = false;
        }
    }
    if(timeInvincibleIsStart)
    {
        if(timeInvincible.getTime() > 0.1)
            timeInvincibleIsStart = false;
    }
    if(currentWeapon == 0)
    {
        currentWeapon = 1;
        dirChara = LEFT;
    }
    else if(currentWeapon == 1)
    {
        currentWeapon = 0;
        dirChara = RIGHT;
    }
}

void bossEnemyClass::initialize()
{
    spriteSheet[0].setTexture(spriteClass::getImage("boss"));
}

void bossEnemyClass::updatePoseSprite()
{
    for(size_t i = 0; i < spriteSheet.size(); ++i)
    {
        spriteSheet[i].setPosition(posePlayer);
    }
}

void bossEnemyClass::setStrike()
{
    if(currentWeapon == 0 && !timeStrikeIsStartWeapons[0])
    {
        timeStrikeIsStartWeapons[0] = true;
        timeStrikeWeapons[0].start();
    }
    else if(currentWeapon == 1 && !timeStrikeIsStartWeapons[1])
    {
        timeStrikeIsStartWeapons[1] = true;
        timeStrikeWeapons[1].start();
    }
}

const sf::RectangleShape bossEnemyClass::getPoseStrike()
{
    sf::RectangleShape poseStrike;
    poseStrike.setSize(sf::Vector2f(30.f, 10.f));
    if(currentWeapon == 0)
    {
        poseStrike.setPosition(posePlayer.x + 9, posePlayer.y + 108);
    }
    else
    {
        poseStrike.setPosition(posePlayer.x + 261, posePlayer.y + 108);
    }
    return poseStrike;
}

const sf::FloatRect bossEnemyClass::getHitBox()
{
    sf::FloatRect hitBox(posePlayer.x + 145, posePlayer.y + 100, 10, 60);
    return hitBox;
}

bool bossEnemyClass::inStriking()
{
    return timeStrikeIsStartWeapons[currentWeapon];
}

