#include <sstream>

#include "player.hpp"
#include "sprite.hpp"

playerClass::playerClass()
{
    typeWeapon = "FISTS";
    type = "PLAYER";
    money = 2000;
    moneySup = 0;
    numberOfLife = 3;
    speed = 6;
    jumpPower = 10;
    damage = 1;
    speedUpgrad = 0, jumpPowerUpgrad = 0;
    damageUpgrad = 0.f;
    resistanceUpgrad = 0.f;
    lifeUpgrad = 0;
    getLaserRifle = false;
    timeComboIsStart = false;
    momentStrike = false;
    timerCombo.start();
    speedJump = jumpPower, life = 200;
    for(int i = jumpPower; i > 0; --i)
    {
        distanceJump += i;
    }
    dirChara = RIGHT;
    typeChara = NOTHING;
    initialize();
}

void playerClass::setPosePlayer(float x, float y)
{
    posePlayer.x = x;
    posePlayer.y = y;
    updatePoseSprite();
}

void playerClass::setStrike()
{
    if(typeWeapon == "FISTS")
    {
        if(!timeStrikeIsStart)
        {
            typeChara = STRIKING;
            timeStrike.start();
            timeStrikeIsStart = true;
            if(timeComboIsStart == true)
            {
                if(timerCombo.getTime() < 0.4)
                {
                    timeComboIsStart = false;
                    timerCombo.start();
                }
                else
                {
                    timerCombo.start();
                }
            }
            else
            {
                timeComboIsStart = true;
                timerCombo.start();
            }
            if(dirChara == LEFT)
            {
                posePlayer.x -= 20;
                updatePoseSprite();
            }
        }
    }
    else if(typeWeapon == "LASER_RIFLE")
    {
        if(!timeStrikeIsStart)
        {
            timeStrike.start();
            timeStrikeIsStart = true;
        }
    }
}

void playerClass::update()
{
    ++frame %= 10;
    timerCombo.update();
    timeInvincible.update();
    timeStrike.update();
    timeStrikWait.update();
    if(timeStrikeIsStart)
    {
        if(typeWeapon == "FISTS")
        {
            if(timeStrike.getTime() > 0.2)
            {
                typeChara = NOTHING;
                if(dirChara == LEFT)
                {
                    posePlayer.x += 20;
                    updatePoseSprite();
                }
                timeStrikeIsStart = false;
            }
            else if(timeStrike.getTime() > 0.05 && timeStrike.getTime() < 0.15)
            {
                momentStrike = true;
            }
            else
            {
                if(timeStrike.getTime() > 0.05 && momentStrike == false)
                {
                    momentStrike = true;
                }
                else
                {
                    momentStrike = false;
                }
            }
        }
        else if(typeWeapon == "LASER_RIFLE")
        {
            if(timeStrike.getTime() > 0.5f)
            {
                timeStrikeIsStart = false;
            }
        }
    }
    if(timeInvincibleIsStart)
    {
        if(timeInvincible.getTime() > 0.1f)
            timeInvincibleIsStart = false;
    }
    if(inJump && firstFrameJump == true)
    {
        firstFrameJump = false;
    }
}

const sf::Sprite& playerClass::getSpriteDraw()
{
    if(typeChara == NOTHING && dirChara == LEFT)
        return spriteSheet[2];
    else if(typeChara == NOTHING && dirChara == RIGHT)
        return spriteSheet[7];
    else if(dirChara == LEFT && typeChara == WALKING)
        return spriteSheet[frame > 5 ? 0 : 1];
    else if(dirChara == RIGHT && typeChara == WALKING)
        return spriteSheet[frame > 5 ? 3 : 4];
    else if(typeChara == JUMP && dirChara == LEFT)
        return spriteSheet[frame > 5 ? 5 : 6];
    else if(typeChara == JUMP && dirChara == RIGHT)
        return spriteSheet[frame > 5 ? 8 : 9];
    else if(typeChara == STRIKING && dirChara == RIGHT)
        return (timeComboIsStart ? spriteSheet[10] : spriteSheet[12]);
    else if(typeChara == STRIKING && dirChara == LEFT)
        return (timeComboIsStart ? spriteSheet[11] : spriteSheet[13]);

    return spriteSheet[2];
}

const sf::RectangleShape playerClass::getColliBox()
{
    sf::RectangleShape colliBox;
    if(timeStrikeIsStart == true && dirChara == LEFT && typeWeapon == "FISTS")
    {
        colliBox.setPosition(posePlayer.x + 20, posePlayer.y);
    }
    else
    {
        colliBox.setPosition(posePlayer.x, posePlayer.y);
    }
    colliBox.setSize(sf::Vector2f(40.f, 80.f));

    return colliBox;
}

const sf::RectangleShape playerClass::getPoseStrike()
{
    sf::RectangleShape poseStrike;
    if(typeWeapon == "FISTS")
    {
        poseStrike.setSize(sf::Vector2f(40.f, 20.f));
        if(dirChara == RIGHT)
            poseStrike.setPosition(posePlayer.x + 20, posePlayer.y + 20);
        else
            poseStrike.setPosition(posePlayer.x, posePlayer.y + 20);
    }

    return poseStrike;
}

void playerClass::initialize()
{
    for(int i = 0; i < 5; ++i)
    {
        spriteSheet[i].setTexture(spriteClass::getImage("player"));
        spriteSheet[i].setTextureRect(sf::IntRect(i * (40 + 1), 0, 40, 80));
    }
    for(int i = 5; i < 10; ++i)
    {
        spriteSheet[i].setTexture(spriteClass::getImage("player"));
        spriteSheet[i].setTextureRect(sf::IntRect((i-5) * (40 + 1), 81, 40, 80));
    }
    for(int i = 10; i < 12; ++i)
    {
        spriteSheet[i].setTexture(spriteClass::getImage("player"));
        spriteSheet[i].setTextureRect(sf::IntRect((i-10) * (60 + 1), 162, 60, 80));
    }
    for(int i = 12; i < 14; ++i)
    {
        spriteSheet[i].setTexture(spriteClass::getImage("player"));
        spriteSheet[i].setTextureRect(sf::IntRect((i-12) * (60 + 1), 244, 60, 80));
    }
}

void playerClass::updatePoseSprite()
{
    for(int i = 0; i < 14; ++i)
    {
        spriteSheet[i].setPosition(posePlayer);
    }
}

int playerClass::getMoney() const
{
    return money;
}

const std::string playerClass::getMoneyInString()
{
    std::ostringstream oss;
    oss << money;
    std::string moneyToString = oss.str();
    return moneyToString;
}

float playerClass::getUpgrad(std::string upgrad) const
{
    if(upgrad == "speed")
        return speedUpgrad;
    else if(upgrad == "jump")
        return jumpPowerUpgrad;
    else if(upgrad == "damage")
        return damageUpgrad;
    else if(upgrad == "resistance")
        return resistanceUpgrad;
    else if(upgrad == "life")
        return lifeUpgrad;
    else
        return 0;
}

const std::string playerClass::getUpgradInString(std::string upgrad)
{
    std::ostringstream oss;
    if(upgrad == "speed")
        oss << speedUpgrad;
    else if(upgrad == "jump")
        oss << jumpPowerUpgrad;
    else if(upgrad == "damage")
        oss << damageUpgrad;
    else if(upgrad == "resistance")
        oss << resistanceUpgrad;
    else if(upgrad == "life")
        oss << lifeUpgrad;
    std::string upgradToString = oss.str();
    return upgradToString;
}

bool playerClass::getWeaponInStore(std::string weapon) const
{
    if(weapon == "LASER_RIFLE")
        return getLaserRifle;
    else
        return false;
}

void playerClass::moveMoney(int val)
{
    money += val;
}

void playerClass::setMoney(int val)
{
    money = val;
}

void playerClass::moveUpgrad(double val, std::string upgrad)
{
    if(upgrad == "speed")
    {
        speed += val * 2;
        speedUpgrad += val;
    }
    else if(upgrad == "jump")
    {
        jumpPower += val * 2;
        speedJump = jumpPower;
        jumpPowerUpgrad += val;
    }
    else if(upgrad == "damage")
    {
        damage += val;
        damageUpgrad += val;
    }
    else if(upgrad == "resistance")
    {
        resistance += val;
        resistanceUpgrad += val;
    }
    else if(upgrad == "life")
    {
        lifeUpgrad += val;
        life = lifeUpgrad + 200;
    }
}

void playerClass::setWeapon(std::string newWeapon)
{
    typeWeapon = newWeapon;
}

void playerClass::setWeaponInStore(bool newVal, std::string weapon)
{
    if(weapon == "LASER_RIFLE")
        getLaserRifle = newVal;
}

int playerClass::getMoneySup()
{
    return moneySup;
}

const std::string playerClass::getMoneySupInString()
{
    std::ostringstream oss;
    oss << moneySup;
    std::string moneySupToString = oss.str();
    return moneySupToString;
}

void playerClass::moveMoneySup(int val)
{
    moneySup += val;
}

void playerClass::setMoneySup(int val)
{
    moneySup = val;
}

int playerClass::getNumberOfLife() const
{
    return numberOfLife;
}

const std::string playerClass::getNumberOfLifeInString()
{
    std::ostringstream oss;
    oss << numberOfLife;
    std::string numberOfLifeToString = oss.str();
    return numberOfLifeToString;
}

void playerClass::moveNumberOfLife(int val)
{
    numberOfLife += val;
}

void playerClass::setNumberOfLife(int val)
{
    numberOfLife = val;
}

bool playerClass::inMomentStrike()
{
    return momentStrike;
}
