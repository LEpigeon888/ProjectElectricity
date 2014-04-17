#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "character.hpp"
#include "timer.hpp"

class playerClass : public characterClass
{
public:
    playerClass();
    void setPosePlayer(float x, float y);
    void updatePoseSprite();
    void setStrike();
    void update();
    const sf::Sprite& getSpriteDraw();
    const sf::RectangleShape getColliBox();
    const sf::RectangleShape getPoseStrike();
    void initialize();
    int getMoney() const;
    void moveMoney(int val);
    void setMoney(int val);
    int getMoneySup();
    void moveMoneySup(int val);
    void setMoneySup(int val);
    const std::string getMoneyInString();
    const std::string getMoneySupInString();
    int getNumberOfLife() const;
    void moveNumberOfLife(int val);
    void setNumberOfLife(int val);
    const std::string getNumberOfLifeInString();
    float getUpgrad(std::string upgrad) const;
    void moveUpgrad(double val, std::string upgrad);
    const std::string getUpgradInString(std::string upgrad);
    bool getWeaponInStore(std::string weapon) const;
    void setWeaponInStore(bool newVal, std::string weapon);
    void setWeapon(std::string newWeapon);
    bool inMomentStrike();
private:
    int money;
    int speedUpgrad;
    int jumpPowerUpgrad;
    int lifeUpgrad;
    int numberOfLife;
    int moneySup;
    double damageUpgrad;
    double resistanceUpgrad;
    bool getLaserRifle;
    bool timeComboIsStart;
    bool momentStrike;
    timerClass timerCombo;
    sf::Sprite spriteSheet[14];
};

#endif
