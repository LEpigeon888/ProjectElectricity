#ifndef EDITLEVELSTATE_HPP
#define EDITLEVELSTATE_HPP

#include "gameState.hpp"
#include "event.hpp"
#include "character.hpp"
#include "item.hpp"
#include "level.hpp"

class editLevelStateClass : public gameStateClass
{
public:
    ~editLevelStateClass();
    void initialize(gameStateStackClass* newparent, sf::RenderWindow* newwindow);
    void setItemTexture();
    void drawMessage(std::string message, float x, float y, bool isTextEntered = false);
    void drawBlock(std::string name, int x, int y);
    void drawEnemy(std::string name, int x, int y);
    void drawPoint(int x, int y);
    void deleteLevel();
    void saveLevel(std::string nameLevel);
    void makeLightWall(std::ofstream& file);
    void update();
    void draw();
private:
    std::list<infoEvent> listEvent;
    std::list<characterClass*> listEnemy;
    sf::Font font;
    std::map<std::pair<int, int>, itemClass*> mapLevel;
    sf::View camera;
    levelClass level;
    int numberItem;
    int tool;
    int endOfLevel;
    int heightLevel;
    int maxInTool;
    bool textEntered;
    bool firstClick;
    std::string typeTextEntered;
    sf::RectangleShape border;
    sf::RectangleShape backgroundText;
    sf::Sprite spritePlayer;
    sf::Sprite item;
    std::string stringTextEntered;
    std::string nameOfItem;
    std::string typeLevel;
    std::list<infoEvent>::iterator poseCurrentEvent;
    infoEvent tmpInfoEvent;
};

#endif

