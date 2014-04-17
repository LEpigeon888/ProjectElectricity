#include "character.hpp"

characterClass::characterClass()
{
    frame = 0, skid = 0, speedFalling = 0;
    inJump = false, timeStrikeIsStart = false, timeInvincibleIsStart = false;
    staticChara = false;
    moveDir = false;
    changeDir = true;
    directDamage = true;
    versusEnemy = false;
    isMoney = false;
    deathToColli = false;
    constSpeedFalling = false;
    bounceChara = false;
    affectToGravity = true;
    affectToWall = true;
    isBoss = false;
    damage = 0;
    resistance = 1.f;
    isPushed = false;
    isLaser = false;
    isInvincible = false;
    firstFrameJump = false;
    lenghtPushed = 0;
    powerPushed = 0;
    distanceJump = 0;
    oldPosY = 0;
    dirChara = LEFT;
    typeChara = NOTHING;
}

bool characterClass::decreaseLife(float strenght)
{
    life -= strenght;
    if(life <= 0)
        return true;
    else
        return false;
}

void characterClass::stopStrike()
{
    timeStrikeIsStart = false;
}

bool characterClass::getTimeInvincibleIsStart()
{
    return timeInvincibleIsStart;
}

timerClass& characterClass::getTimeInvincible()
{
    return timeInvincible;
}

void characterClass::setTimeInvincibleIsStart(bool mode)
{
    timeInvincibleIsStart = mode;
}

typePlayer characterClass::getTypePlayer()
{
    return typeChara;
}

dirPlayer characterClass::getDirPlayer()
{
    return dirChara;
}

int characterClass::getSkid()
{
    return skid;
}

const sf::Vector2f& characterClass::getPosePlayer()
{
    return posePlayer;
}

bool characterClass::inStriking()
{
    return timeStrikeIsStart;
}

float characterClass::getLife()
{
    return life;
}

int characterClass::getSpeed()
{
    return speed;
}

int characterClass::getJumpPower()
{
    return jumpPower;
}

double characterClass::getSpeedJump()
{
    return speedJump;
}

bool characterClass::getInJump()
{
    return inJump;
}

double characterClass::getSpeedFalling()
{
    return speedFalling;
}

const std::string& characterClass::getType()
{
    return type;
}

void characterClass::setJumping()
{
    if(!inJump && typeChara != STRIKING && speedFalling == 0)
        inJump = true;
}

timerClass& characterClass::getTimeStrikeWait()
{
    return timeStrikWait;
}

void characterClass::setTimeStrikeWaitIsStart(bool value)
{
    timeStrikeWaitIsStart = value;
}

bool characterClass::getTimeStrikeWaitIsStart()
{
    return timeStrikeWaitIsStart;
}

void characterClass::setDirPlayer(dirPlayer newDir)
{
    dirChara = newDir;
}

void characterClass::setSkid(int newVal)
{
    skid = newVal;
}

void characterClass::moveSkid(int val)
{
    skid += val;
}

void characterClass::setTypePlayer(typePlayer newType)
{
    typeChara = newType;
}

void characterClass::movePosePlayer(double x, double y)
{
    if(x != 0 && (int) (x + (x > 0 ? 0.5f : -0.5f)) == 0)
    {
        x = (x > 0 ? 1 : -1);
    }
    if(y != 0 && (int) (y + (y > 0 ? 0.5f : -0.5f)) == 0)
    {
        y = (y > 0 ? 1 : -1);
    }
    posePlayer.x += (int) (x + (x > 0 ? 0.5f : -0.5f));
    posePlayer.y += (int) (y + (y > 0 ? 0.5f : -0.5f));
    updatePoseSprite();
}

void characterClass::setPosePlayer(double x, double y)
{
    posePlayer.x = (int) (x + (x > 0 ? 0.5f : -0.5f));
    posePlayer.y = (int) (y + (y > 0 ? 0.5f : -0.5f));
    updatePoseSprite();
}

void characterClass::setSpeedJump(double newVal)
{
    speedJump = newVal;
}

void characterClass::moveSpeedJump(double val)
{
    speedJump += val;
}

void characterClass::setLife(float newVal)
{
    life = newVal;
}

void characterClass::moveLife(float val)
{
    life += val;
}

void characterClass::setSpeedFalling(double newVal)
{
    speedFalling = newVal;
}

void characterClass::moveSpeedFalling(double val)
{
    speedFalling += val;
}

void characterClass::setJumpPower(int newVal)
{
    jumpPower = newVal;
}

void characterClass::moveJumpPower(int val)
{
    jumpPower += val;
}

void characterClass::setSpeed(int newVal)
{
    speed = newVal;
}

void characterClass::moveSpeed(int val)
{
    speed += val;
}

void characterClass::setInJump(bool newVal)
{
    inJump = newVal;
}

const std::string& characterClass::getWeapon() const
{
    return typeWeapon;
}

bool characterClass::getStaticChara()
{
    return staticChara;
}

bool characterClass::getMoveDir()
{
    return moveDir;
}

bool characterClass::getChangeDir()
{
    return changeDir;
}

float characterClass::getDamage()
{
    return damage;
}

bool characterClass::getDirectDamage()
{
    return directDamage;
}

bool characterClass::getVersusEnemy()
{
    return versusEnemy;
}

bool characterClass::getIsMoney()
{
    return isMoney;
}

bool characterClass::getDeathToColli()
{
    return deathToColli;
}

bool characterClass::getConstSpeedFalling()
{
    return constSpeedFalling;
}

bool characterClass::getBounceChara()
{
    return bounceChara;
}

bool characterClass::getAffectToGravity()
{
    return affectToGravity;
}

const sf::FloatRect characterClass::getHitBox()
{
    return getSpriteDraw().getGlobalBounds();
}

bool characterClass::getAffectToWall()
{
    return affectToWall;
}

void characterClass::setDamage(float value)
{
    damage = value;
}

bool characterClass::getIsBoss()
{
    return isBoss;
}

float characterClass::getResistance()
{
    return resistance;
}

void characterClass::moveResistance(float value)
{
    resistance += value;
}

bool characterClass::getIsPushed()
{
    return isPushed;
}

int characterClass::getLenghtPushed()
{
    return lenghtPushed;
}

int characterClass::getPowerPushed()
{
    return powerPushed;
}

void characterClass::setIsPushed(bool val)
{
    isPushed = val;
}

void characterClass::setLenghtPushed(int val)
{
    lenghtPushed = val;
}

void characterClass::setPowerPushed(int val)
{
    powerPushed = val;
}

void characterClass::moveLenghtPushed(int val)
{
    lenghtPushed += val;
}

void characterClass::movePowerPushed(int val)
{
    powerPushed += val;
}

int characterClass::getDistanceJump()
{
    return distanceJump;
}

void characterClass::setDistanceJump(int newVal)
{
    distanceJump = newVal;
}

void characterClass::moveDistanceJump(int val)
{
    distanceJump += val;
}

int characterClass::getOldPosY()
{
    return oldPosY;
}

void characterClass::setOldPosY(int newVal)
{
    oldPosY = newVal;
}

int characterClass::getOldPosX()
{
    return oldPosX;
}

void characterClass::setOldPosX(int newVal)
{
    oldPosX = newVal;
}

bool characterClass::getIsLaser()
{
    return isLaser;
}

bool characterClass::getIsInvinsible()
{
    return isInvincible;
}

void characterClass::setFirstFrameJump(bool val)
{
    firstFrameJump = val;
}

bool characterClass::getFirstFrameJump()
{
    return firstFrameJump;
}
