#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include "timer.hpp"

enum dirPlayer {LEFT, RIGHT};
enum typePlayer {WALKING, NOTHING, JUMP, STRIKING};

class characterClass
{
public:
    characterClass();
    virtual ~characterClass() {};
    bool decreaseLife(float strenght);
    bool getTimeInvincibleIsStart();
    timerClass& getTimeInvincible();
    void setTimeInvincibleIsStart(bool mode);
    typePlayer getTypePlayer();
    void setTypePlayer(typePlayer newType);
    dirPlayer getDirPlayer();
    void setDirPlayer(dirPlayer newDir);
    int getSkid();
    void setSkid(int newVal);
    void moveSkid(int val);
    const sf::Vector2f& getPosePlayer();
    void movePosePlayer(double x, double y);
    void setPosePlayer(double x, double y);
    virtual void updatePoseSprite() = 0;
    virtual bool inStriking();
    float getLife();
    void setLife(float newVal);
    void moveLife(float val);
    int getSpeed();
    void setSpeed(int newVal);
    void moveSpeed(int val);
    int getJumpPower();
    void setJumpPower(int newVal);
    void moveJumpPower(int val);
    virtual const sf::RectangleShape getPoseStrike() = 0;
    virtual const sf::Sprite& getSpriteDraw() = 0;
    virtual const sf::RectangleShape getColliBox() = 0;
    double getSpeedJump();
    void setSpeedJump(double newVal);
    void moveSpeedJump(double val);
    int getDistanceJump();
    void setDistanceJump(int newVal);
    void moveDistanceJump(int val);
    double getSpeedFalling();
    void setSpeedFalling(double newVal);
    void moveSpeedFalling(double val);
    bool getInJump();
    void setInJump(bool newVal);
    const std::string& getType();
    virtual void update() = 0;
    void setJumping();
    virtual void setStrike() = 0;
    timerClass& getTimeStrikeWait();
    void setTimeStrikeWaitIsStart(bool value);
    bool getTimeStrikeWaitIsStart();
    const std::string& getWeapon() const;
    bool getStaticChara();
    bool getMoveDir();
    bool getChangeDir();
    bool getDirectDamage();
    float getDamage();
    bool getVersusEnemy();
    bool getIsMoney();
    bool getDeathToColli();
    bool getConstSpeedFalling();
    bool getBounceChara();
    bool getAffectToGravity();
    bool getIsLaser();
    bool getIsInvinsible();
    virtual const sf::FloatRect getHitBox();
    bool getAffectToWall();
    void setDamage(float value);
    bool getIsBoss();
    float getResistance();
    void moveResistance(float value);
    bool getIsPushed();
    int getLenghtPushed();
    int getPowerPushed();
    int getOldPosY();
    void setOldPosY(int newVal);
    int getOldPosX();
    void setOldPosX(int newVal);
    void setIsPushed(bool val);
    void setLenghtPushed(int val);
    void setPowerPushed(int val);
    void moveLenghtPushed(int val);
    void movePowerPushed(int val);
    void setFirstFrameJump(bool val);
    bool getFirstFrameJump();
    virtual void stopStrike();
protected:
    bool staticChara;
    bool isLaser;
    bool moveDir;
    bool changeDir;
    bool directDamage;
    bool versusEnemy;
    bool isMoney;
    bool deathToColli;
    bool constSpeedFalling;
    bool bounceChara;
    bool affectToGravity;
    bool affectToWall;
    bool isBoss;
    bool firstFrameJump;
    float damage;
    float resistance;
    std::string type;
    double speedFalling;
    bool inJump;
    double speedJump;
    int speed;
    int jumpPower;
    int skid;
    bool isPushed;
    int lenghtPushed;
    int powerPushed;
    float life;
    int frame;
    int oldPosY;
    int oldPosX;
    int distanceJump;
    bool timeInvincibleIsStart;
    bool timeStrikeIsStart;
    bool isInvincible;
    timerClass timeStrike;
    timerClass timeInvincible;
    sf::Vector2f posePlayer;
    dirPlayer dirChara;
    typePlayer typeChara;
    std::string typeWeapon;
    timerClass timeStrikWait;
    bool timeStrikeWaitIsStart;
};

#endif
