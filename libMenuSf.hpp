#ifndef LIBMENUSF_HPP
#define LIBMENUSF_HPP

#include <list>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

namespace msf
{
    struct message
    {
        std::string mess;
        int poseX;
        int poseY;
    };

    struct entryMenu
    {
        std::list<entryMenu> listEntryMenu;
        std::string type;
        message mess;
    };

    class menuSfClass
    {
    public:
        menuSfClass(bool isSubMenu = false);
        ~menuSfClass();
        menuSfClass(sf::Color newTextColor, std::string path, bool isSubMenu = false);
        void update(sf::Event event);
        void draw(sf::RenderWindow* window);
        int getSelectedMode();
        void changeSet(sf::Color newTextColor = sf::Color::Black, std::string path = "cour.ttf");
        void drawMessage(std::string message, float x, float y, sf::RenderWindow *window);
        void addToStaticList(std::string mess, int x, int y);
        int addToMoveList(std::string mess, int x = -1, int y = -1, bool center = false, std::string newType = "MOVE_MESS");
        int addEntryToListEntry(int number, std::string newType, std::string mess, int x, int y, bool center = false);
        void setEntryToListEntry(int number, int numberEntry, std::string newType);
        int getSubMenu();
        bool getIsActive();
    private:
        sf::Font font;
        sf::Color textColor;
        int modeSelect;
        int actuPoseX;
        int actuPoseY;
        int numberSubMenu;
        sf::RectangleShape cursor;
        bool isActive;
        std::unique_ptr<menuSfClass> subMenuActu;
        std::list<message> staticMess;
        std::vector<entryMenu> moveMess;
    };
}

#endif
