#include "basicEnemy.hpp"
#include "sprite.hpp"

basicEnemyClass::basicEnemyClass(float x, float y, std::string newTypeBasic)
{
    type = newTypeBasic;
    if(type == "BASIC")
    {
        life = 4;
        speed = 4;
        jumpPower = 5;
        spriteSheet.resize(12);
        typeWeapon = "FISTS";
        damage = 0.5f;
    }
    else if(type == "EXPLOSIVE")
    {
        life = 1;
        speed = 1;
        jumpPower = 5;
        timeStrikeIsStart = true;
        spriteSheet.resize(1);
        typeWeapon = "SUICIDE";
        damage = 20.f;
        affectToGravity = false;
    }
    else if(type == "LASER_E")
    {
        life = 2;
        speed = 4;
        jumpPower = 5;
        spriteSheet.resize(2);
        typeWeapon = "LASER_RIFLE";
        damage = 1.f;
        directDamage = false;
    }
    else if(type == "TURRET_L")
    {
        life = 8;
        speed = 0;
        jumpPower = 0;
        dirChara = LEFT;
        spriteSheet.resize(1);
        typeWeapon = "LASER_RIFLE";
        damage = 1.f;
        staticChara = true;
        changeDir = false;
        directDamage = false;
    }
    else if(type == "TURRET_R")
    {
        life = 8;
        speed = 0;
        jumpPower = 0;
        dirChara = RIGHT;
        spriteSheet.resize(1);
        typeWeapon = "LASER_RIFLE";
        damage = 1.f;
        staticChara = true;
        changeDir = false;
        directDamage = false;
    }
    else if(type == "COIN")
    {
        life = 999;
        speed = 5;
        jumpPower = -999;
        typeChara = WALKING;
        spriteSheet.resize(1);
        moveDir = true;
        damage = 1.f;
        isMoney = true;
        bounceChara = true;
        isInvincible = true;
    }
    else if(type == "LASER")
    {
        life = 999;
        speed = 15;
        jumpPower = 5;
        timeStrikeIsStart = true;
        spriteSheet.resize(1);
        typeChara = WALKING;
        moveDir = true;
        deathToColli = true;
        affectToGravity = false;
        isLaser = true;
        isInvincible = true;
    }
    else if(type == "LASER_POSI")
    {
        life = 999;
        speed = 15;
        jumpPower = 5;
        timeStrikeIsStart = true;
        spriteSheet.resize(1);
        typeChara = WALKING;
        moveDir = true;
        versusEnemy = true;
        damage = 1.5f;
        deathToColli = true;
        affectToGravity = false;
        isLaser = true;
        isInvincible = true;
    }
    else if(type == "LASER_SE")
    {
        life = 2;
        speed = 4;
        jumpPower = 5;
        spriteSheet.resize(1);
        typeWeapon = "BEAM_RIFLE";
        damage = 1.f;
        directDamage = false;
        affectToGravity = false;
    }
    else if(type == "BEAM")
    {
        life = 999;
        speed = 15;
        jumpPower = 5;
        timeStrikeIsStart = true;
        spriteSheet.resize(1);
        typeChara = WALKING;
        deathToColli = true;
        constSpeedFalling = true;
        isLaser = true;
        isInvincible = true;
    }
    for(int i = jumpPower; i > 0; --i)
    {
        distanceJump += i;
    }
    speedJump = jumpPower;
    posePlayer.x = x, posePlayer.y = y;
    initialize();
    updatePoseSprite();
    timeStrikeWaitIsStart = false;
}

const sf::Sprite& basicEnemyClass::getSpriteDraw()
{
    if(type == "BASIC")
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
            return spriteSheet[10];
        else if(typeChara == STRIKING && dirChara == LEFT)
            return spriteSheet[11];
    }
    else if(type == "EXPLOSIVE")
    {
        return spriteSheet[0];
    }
    else if(type == "LASER_E")
    {
        if(dirChara == LEFT)
            return spriteSheet[0];
        else if(dirChara == RIGHT)
            return spriteSheet[1];
    }
    else if(type == "TURRET_L" || type == "TURRET_R")
    {
        return spriteSheet[0];
    }
    else if(type == "COIN")
    {
        return spriteSheet[0];
    }
    else if(type == "LASER")
    {
        return spriteSheet[0];
    }
    else if(type == "LASER_POSI")
    {
        return spriteSheet[0];
    }
    else if(type == "LASER_SE")
    {
        return spriteSheet[0];
    }
    else if(type == "BEAM")
    {
        return spriteSheet[0];
    }

    return spriteSheet[0];
}

const sf::RectangleShape basicEnemyClass::getColliBox()
{
    sf::RectangleShape colliBox;
    if(type == "BASIC")
    {
        if(timeStrikeIsStart == true && dirChara == LEFT)
        {
            colliBox.setPosition(posePlayer.x + 20, posePlayer.y);
        }
        else
        {
            colliBox.setPosition(posePlayer.x, posePlayer.y);
        }
        colliBox.setSize(sf::Vector2f(40.f, 80.f));
    }
    else
    {
        sf::RectangleShape colliBox;
        colliBox.setPosition(posePlayer.x, posePlayer.y);
        colliBox.setSize(sf::Vector2f(getSpriteDraw().getGlobalBounds().width, getSpriteDraw().getGlobalBounds().height));
        return colliBox;
    }

    return colliBox;
}

void basicEnemyClass::update()
{
    ++frame %= 10;
    timeInvincible.update();
    timeStrike.update();
    timeStrikWait.update();
    if(timeStrikeIsStart)
    {
        if(type == "BASIC")
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
        }
        else if(type == "LASER_E")
        {
            if(timeStrike.getTime() > 2.)
            {
                timeStrikeIsStart = false;
            }
        }
        else if(type == "TURRET_L" || type == "TURRET_R")
        {
            if(timeStrike.getTime() > 1.5)
            {
                timeStrikeIsStart = false;
            }
        }
        else if(type == "LASER_SE")
        {
            if(timeStrike.getTime() > 2.)
            {
                timeStrikeIsStart = false;
            }
        }
    }
    if(timeInvincibleIsStart)
    {
        if(timeInvincible.getTime() > 0.1)
            timeInvincibleIsStart = false;
    }
    if(inJump && firstFrameJump == true)
    {
        firstFrameJump = false;
    }
}

void basicEnemyClass::initialize()
{
    if(type == "BASIC")
    {
        for(int i = 0; i < 5; ++i)
        {
            spriteSheet[i].setTexture(spriteClass::getImage("enemy"));
            spriteSheet[i].setTextureRect(sf::IntRect(i * (40 + 1), 0, 40, 80));
        }
        for(int i = 5; i < 10; ++i)
        {
            spriteSheet[i].setTexture(spriteClass::getImage("enemy"));
            spriteSheet[i].setTextureRect(sf::IntRect((i-5) * (40 + 1), 81, 40, 80));
        }
        for(int i = 10; i < 12; ++i)
        {
            spriteSheet[i].setTexture(spriteClass::getImage("enemy"));
            spriteSheet[i].setTextureRect(sf::IntRect((i-10) * (60 + 1), 162, 60, 80));
        }
    }
    else if(type == "EXPLOSIVE")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("explosiveEnemy"));
    }
    else if(type == "LASER_E")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("laserEnemy"));
        spriteSheet[0].setTextureRect(sf::IntRect(0, 0, 40, 80));
        spriteSheet[1].setTexture(spriteClass::getImage("laserEnemy"));
        spriteSheet[1].setTextureRect(sf::IntRect(41, 0, 40, 80));
    }
    else if(type == "TURRET_L")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("turret"));
        spriteSheet[0].setTextureRect(sf::IntRect(0, 0, 40, 60));
    }
    else if(type == "TURRET_R")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("turret"));
        spriteSheet[0].setTextureRect(sf::IntRect(41, 0, 40, 60));
    }
    else if(type == "COIN")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("coin"));
    }
    else if(type == "LASER")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("laser"));
    }
    else if(type == "LASER_POSI")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("laserPosi"));
    }
    else if(type == "LASER_SE")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("laserShipEnemy"));
    }
    else if(type == "BEAM")
    {
        spriteSheet[0].setTexture(spriteClass::getImage("beam"));
    }
}

void basicEnemyClass::updatePoseSprite()
{
    for(size_t i = 0; i < spriteSheet.size(); ++i)
    {
        spriteSheet[i].setPosition(posePlayer);
    }
}

void basicEnemyClass::setStrike()
{
    if(type == "BASIC")
    {
        if(!timeStrikeIsStart)
        {
            typeChara = STRIKING;
            timeStrike.start();
            timeStrikeIsStart = true;
            if(dirChara == LEFT)
            {
                posePlayer.x -= 20;
                updatePoseSprite();
            }
        }
    }
    else if(type == "LASER_E" || type == "TURRET_L" || type == "TURRET_R" || type == "LASER_SE")
    {
        if(!timeStrikeIsStart)
        {
            timeStrike.start();
            timeStrikeIsStart = true;
        }
    }
    else if(type == "COIN")
    {
        timeStrikeIsStart = true;
    }
}

const sf::RectangleShape basicEnemyClass::getPoseStrike()
{
    if(type == "BASIC")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(40.f, 20.f));
        if(dirChara == RIGHT)
            poseStrike.setPosition(posePlayer.x + 20, posePlayer.y + 20);
        else
            poseStrike.setPosition(posePlayer.x, posePlayer.y + 20);

        return poseStrike;
    }
    else if(type == "EXPLOSIVE")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(40.f, 40.f));
        poseStrike.setPosition(posePlayer);

        return poseStrike;
    }
    else if(type == "COIN")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(10.f, 10.f));
        poseStrike.setPosition(posePlayer);

        return poseStrike;
    }
    else if(type == "LASER")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(30.f, 10.f));
        poseStrike.setPosition(posePlayer);

        return poseStrike;
    }
    else if(type == "LASER_POSI")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(30.f, 10.f));
        poseStrike.setPosition(posePlayer);

        return poseStrike;
    }
    else if(type == "BEAM")
    {

        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(15.f, 30.f));
        poseStrike.setPosition(posePlayer);

        return poseStrike;
    }
    else if(type == "LASER_E")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(30.f, 10.f));
        if(dirChara == LEFT)
        {
            poseStrike.setPosition(posePlayer.x - 19, posePlayer.y + 32);
        }
        else
        {
            poseStrike.setPosition(posePlayer.x + 28, posePlayer.y + 32);
        }

        return poseStrike;
    }
    else if(type == "LASER_SE")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(15.f, 30.f));
        poseStrike.setPosition(posePlayer.x + 12, posePlayer.y + 26);

        return poseStrike;
    }
    else if(type == "TURRET_L")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(30.f, 10.f));
        poseStrike.setPosition(posePlayer.x - 18, posePlayer.y + 22);

        return poseStrike;
    }
    else if(type == "TURRET_R")
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(30.f, 10.f));
        poseStrike.setPosition(posePlayer.x + 28, posePlayer.y + 22);

        return poseStrike;
    }
    else
    {
        sf::RectangleShape poseStrike;
        poseStrike.setSize(sf::Vector2f(spriteSheet[0].getGlobalBounds().width, spriteSheet[0].getGlobalBounds().height));
        poseStrike.setPosition(posePlayer);

        return poseStrike;
    }
}

void basicEnemyClass::stopStrike()
{
    if(timeStrikeIsStart)
    {
        if(type == "BASIC")
        {
            typeChara = NOTHING;
            if(dirChara == LEFT)
            {
                posePlayer.x += 20;
                updatePoseSprite();
            }
            timeStrikeIsStart = false;
        }
    }
}
