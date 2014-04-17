#ifndef GAMEPLAYED_HPP
#define GAMEPLAYED_HPP

#include <map>

#include "player.hpp"
#include "event.hpp"
#include "gameStateStack.hpp"
#include "character.hpp"
#include "level.hpp"
#include "item.hpp"
#include "lightManager.hpp"
#include "particleMotor.hpp"

class gamePlayedClass
{
public:
    gamePlayedClass();
    ~gamePlayedClass();
    void draw();
    void update();
    void setWindowAndStack(sf::RenderWindow* newwindow, gameStateStackClass* newGameStateStack);
    bool checkCollision();
    void checkCollisionWithChara(characterClass& chara);
    bool getBlow(characterClass& character, float strenght);
    void addXPosePlayer(characterClass& character, double x, bool updateCamera = false);
    void jumping(characterClass& jumpPlayer, float percentDist = 0);
    void setStrikePlayer();
    void setJumpingPlayer();
    void movePlayer(int x);
    void moveEnemyWithChara(characterClass& chara);
    void newLevel(bool dead = false);
    bool colliWithItem(characterClass& chara, bool move = true, bool inJump = false,  bool secondPass = false);
    bool moveChara(characterClass& chara, float x);
    void setCameraTo(characterClass& chara);
    void falling(characterClass& chara, float percentDist = 0, float actuPercentDist = 0);
    void setNoJump(characterClass& chara);
    void pusheChara(characterClass& chara, int lenght = 0, int power = 0);
    void drawMessage(std::string message, float x, float y);
    gameStateStackClass* getGameStateStack();
    std::list<characterClass*>& getListActiveEnemy();
    std::map<std::pair<int, int>, itemClass*>& getMapLevel();
    sf::View& getCamera();
    const levelClass& getLevelClass();
    levelClass& setLevelClass();
    const playerClass& getPlayer();
    playerClass& setPlayer();
    void updatePlayer();
private:
    bool moveCam;
    sf::Sprite background[2];
    int endOfLevel;
    int heightLevel;
    gameStateStackClass* gameStateStack;
    sf::RenderWindow* window;
    playerClass player;
    std::list<eventClass*> listEvent;
    std::list<characterClass*> listEnemy;
    std::list<characterClass*> listActiveEnemy;
    std::list<characterClass*> listEntity;
    std::map<std::pair<int, int>, itemClass*> mapLevel;
    std::string typeLevel;
    sf::View camera;
    levelClass level;
    lightManagerClass lightManager;
    lightEntity playerLight;
    sf::RectangleShape lifePlayer;
    particleMotorClass particleMotor;
};

#endif
