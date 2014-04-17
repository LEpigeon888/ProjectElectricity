#include "gamePlayed.hpp"
#include "endLevelState.hpp"
#include "endGameState.hpp"
#include "global.hpp"
#include "basicEnemy.hpp"
#include "sprite.hpp"
#include "storeState.hpp"
#include "endLifeState.hpp"

gamePlayedClass::gamePlayedClass()
{
    endOfLevel = 1280;
    heightLevel = 480;
    level.setNextLevel();
    level.setLevel(listEvent, listEnemy, mapLevel, endOfLevel, heightLevel, typeLevel, lightManager);
    background[0].setTexture(spriteClass::getImage("background"));
    background[0].setPosition(0, heightLevel - 480);
    background[1].setTexture(spriteClass::getImage("background"));
    background[1].setPosition(800, heightLevel - 480);
    camera.setSize(640, 480);
    camera.setCenter(320, heightLevel - 240);
    player.setPosePlayer(50.f, heightLevel - 80.f);
    lifePlayer.setPosition(10, 10);
    lifePlayer.setFillColor(sf::Color::Green);
    lifePlayer.setSize(sf::Vector2f(player.getLife(), 10));
    storeStateClass::setPlayer(&player);
    if(typeLevel == "DARK")
    {
        playerLight = lightManager.addDynamicLight(sf::Vector2f(player.getColliBox().getPosition().x + (player.getColliBox().getGlobalBounds().width / 2), player.getColliBox().getPosition().y + (player.getColliBox().getGlobalBounds().height / 2)), 255, 160, 32, sf::Color::White);
    }
    moveCam = true;
}

gamePlayedClass::~gamePlayedClass()
{
    for(std::list<eventClass*>::iterator i = listEvent.begin(); i != listEvent.end(); )
    {
        delete (*i);;
        listEvent.erase(i++);
    }
    for(std::list<characterClass*>::iterator i = listEnemy.begin(); i != listEnemy.end(); )
    {
        delete (*i);
        listEnemy.erase(i++);
    }
    for(std::list<characterClass*>::iterator i = listActiveEnemy.begin(); i != listActiveEnemy.end(); )
    {
        delete (*i);
        listActiveEnemy.erase(i++);
    }
    for(std::list<characterClass*>::iterator i = listEntity.begin(); i != listEntity.end(); )
    {
        delete (*i);
        listEntity.erase(i++);
    }
    for(std::map<std::pair<int, int>, itemClass*>::iterator i = mapLevel.begin(); i != mapLevel.end(); )
    {
        delete i->second;
        mapLevel.erase(i++);
    }

    lightManager.deleteAllLight();
    lightManager.deleteAllWall();
}

void gamePlayedClass::update()
{
    lifePlayer.setSize(sf::Vector2f(player.getLife(), 10));
    if(player.getInJump())
    {
        if(player.getFirstFrameJump() == false)
        {
            jumping(player);
        }
    }
    else
        falling(player);
    if(camera.getCenter().x + 320 > background[1].getPosition().x + 800)
    {
        background[0].setPosition(background[1].getPosition());
        background[1].move(800, 0);
    }
    else if(camera.getCenter().x - 320 < background[0].getPosition().x )
    {
        background[1].setPosition(background[0].getPosition());
        background[0].move(-800, 0);
    }
    for(std::list<characterClass*>::iterator i = listEnemy.begin(); i != listEnemy.end(); )
    {
        if((*i)->getSpriteDraw().getPosition().x > camera.getCenter().x + 320)
            break;
        else if((*i)->getSpriteDraw().getPosition().x > camera.getCenter().x - (320 + (*i)->getSpriteDraw().getGlobalBounds().width) && (*i)->getSpriteDraw().getPosition().y < camera.getCenter().y + 240 && (*i)->getSpriteDraw().getPosition().y > camera.getCenter().y - (240 + (*i)->getSpriteDraw().getGlobalBounds().height))
        {
            if(player.getPosePlayer().x < (*i)->getSpriteDraw().getPosition().x)
                listActiveEnemy.push_back((*i));
            else
                listActiveEnemy.push_front((*i));
            listEnemy.erase(i++);
        }
        else
            ++i;
    }
    std::list<characterClass*>::iterator j;
    for(std::list<characterClass*>::iterator i = listActiveEnemy.begin(); i != listActiveEnemy.end(); )
    {
        (*i)->update();
        moveEnemyWithChara(*(*i));
        if((*i)->getLife() <= 0)
        {
            delete (*i);
            listActiveEnemy.erase(i++);
            continue;
        }
        if((*i)->getAffectToGravity())
        {
            if((*i)->getInJump())
            {
                if((*i)->getFirstFrameJump() == false)
                {
                    jumping(*(*i));
                }
            }
            else
                falling(*(*i));
        }
        if((*i)->getSpriteDraw().getPosition().x < camera.getCenter().x - (320 + (*i)->getSpriteDraw().getGlobalBounds().width) || (*i)->getSpriteDraw().getPosition().x > camera.getCenter().x + 320 || (*i)->getSpriteDraw().getPosition().y > camera.getCenter().y + 240 || (*i)->getSpriteDraw().getPosition().y < camera.getCenter().y - (240 + (*i)->getSpriteDraw().getGlobalBounds().height))
        {
            for(j = listEnemy.begin(); j != listEnemy.end(); ++j)
            {
                if((*j)->getSpriteDraw().getPosition().x > (*i)->getSpriteDraw().getPosition().x)
                {
                    listEnemy.insert(j, (*i));
                    listActiveEnemy.erase(i++);
                    break;
                }
            }
            if(j == listEnemy.end())
            {
                listEnemy.insert(j, (*i));
                listActiveEnemy.erase(i++);
                break;
            }
        }
        else
            ++i;
    }
    for(std::list<characterClass*>::iterator i = listEntity.begin(); i != listEntity.end(); )
    {
        (*i)->update();
        moveEnemyWithChara(*(*i));
        if((*i)->getLife() <= 0)
        {
            delete (*i);
            listEntity.erase(i++);
            continue;
        }
        if((*i)->getAffectToGravity())
        {
            if((*i)->getInJump())
            {
                if((*i)->getFirstFrameJump() == false)
                {
                    jumping(*(*i));
                }
            }
            else
                falling(*(*i));
        }
        if((*i)->getSpriteDraw().getPosition().x < camera.getCenter().x - (320 + (*i)->getSpriteDraw().getGlobalBounds().width) || (*i)->getSpriteDraw().getPosition().x > camera.getCenter().x + 320 || (*i)->getSpriteDraw().getPosition().y > camera.getCenter().y + 240 || (*i)->getSpriteDraw().getPosition().y < camera.getCenter().y - (320 + (*i)->getSpriteDraw().getGlobalBounds().height))
        {
            delete (*i);
            listEntity.erase(i++);
            continue;
        }
        ++i;
    }
    if(checkCollision() == true)
    {
        if(typeLevel == "DARK")
        {
            lightManager.setPoseImg(camera.getCenter().x - 320, camera.getCenter().y - 240);
            lightManager.setPosition(playerLight, sf::Vector2f(player.getColliBox().getPosition().x + (player.getColliBox().getGlobalBounds().width / 2), player.getColliBox().getPosition().y + (player.getColliBox().getGlobalBounds().height / 2)));
            lightManager.generate();
        }
        return;
    }
    if(player.getLife() <= 0)
    {
        player.moveNumberOfLife(-1);
        if(player.getNumberOfLife() < 0)
        {
            gameStateStack->set(new endGameStateClass(false));
            return;
        }
        else
        {
            player.setMoneySup(0);
            newLevel(true);
            gameStateStack->add(new endLifeStateClass(player.getNumberOfLifeInString()));
            return;
        }
    }
    if(listActiveEnemy.empty())
    {
        if(listEvent.empty())
        {
            if(!level.setNextLevel())
            {
                newLevel();
                gameStateStack->add(new endLevelStateClass);
            }
            else
            {
                gameStateStack->set(new endGameStateClass(true));
            }
            return;
        }
        else if(listEvent.back()->getSurface().getPosition().x + listEvent.back()->getSurface().getGlobalBounds().width < player.getPosePlayer().x)
        {
            if(!level.setNextLevel())
            {
                newLevel();
                gameStateStack->add(new endLevelStateClass);
            }
            else
            {
                gameStateStack->set(new endGameStateClass(true));
            }
            return;
        }
    }

    if(typeLevel == "DARK")
    {
        lightManager.setPoseImg(camera.getCenter().x - 320, camera.getCenter().y - 240);
        lightManager.setPosition(playerLight, sf::Vector2f(player.getColliBox().getPosition().x + (player.getColliBox().getGlobalBounds().width / 2), player.getColliBox().getPosition().y + (player.getColliBox().getGlobalBounds().height / 2)));
        lightManager.generate();
    }

    particleMotor.update();
}

void gamePlayedClass::draw()
{
    window->setView(camera);
    window->draw(background[0]);
    window->draw(background[1]);
    for(std::list<characterClass*>::iterator i = listActiveEnemy.begin(); i != listActiveEnemy.end(); ++i)
    {
        window->draw((*i)->getSpriteDraw());
    }
    for(std::list<characterClass*>::iterator i = listEntity.begin(); i != listEntity.end(); ++i)
    {
        window->draw((*i)->getSpriteDraw());
    }
    for(int i = (camera.getCenter().x - 320) / 20; i < (camera.getCenter().x + 320) / 20; ++i)
    {
        for(int j = (camera.getCenter().y - 240) / 20; j < (camera.getCenter().y + 240) / 20; ++j)
        {
            std::map<std::pair<int, int>, itemClass*>::iterator k = mapLevel.find(std::pair<int, int>(i, j));
            if(k != mapLevel.end())
            {
                if(k->second->getStatBlock("BLOCK_LIGHT") != true)
                {
                    window->draw(mapLevel.find(std::pair<int, int>(i, j))->second->getSkin());
                }
            }
        }
    }
    window->draw(player.getSpriteDraw());
    particleMotor.draw(window);
    if(typeLevel == "DARK")
    {
        lightManager.draw(window);
    }
    window->setView(window->getDefaultView());
    window->draw(lifePlayer);
    drawMessage(player.getMoneyInString() + " : " + player.getMoneySupInString(), 10, 20);
    drawMessage(player.getNumberOfLifeInString(), 10, 35);
}

void gamePlayedClass::setWindowAndStack(sf::RenderWindow* newwindow, gameStateStackClass* newGameStateStack)
{
    window = newwindow;
    gameStateStack = newGameStateStack;
}

bool gamePlayedClass::checkCollision()
{
    static bool moveFinish = false;
    bool returnStat = false;

    for(std::list<eventClass*>::iterator i = listEvent.begin(); i != listEvent.end(); ++i)
    {
        if((*i)->getSurface().getPosition().x > player.getColliBox().getPosition().x + player.getColliBox().getGlobalBounds().width)
        {
            break;
        }
        if((*i)->getSurface().getGlobalBounds().intersects(player.getColliBox().getGlobalBounds()))
        {
            if((*i)->getType() == "MESSAGE" || (*i)->getType() == "CHANGE_MAP")
            {
                (*i)->action(this);
                returnStat = true;
                delete (*i);
                listEvent.erase(i);
                break;
            }
            else if((*i)->getType() == "SPAWN_ENEMY")
            {
                if(moveCam == true)
                {
                    moveFinish = camera.getCenter().x == (*i)->getPoseX() && camera.getCenter().y == (*i)->getPoseY();
                }
                if(!moveFinish)
                {
                    if(camera.getCenter().y > (*i)->getPoseY() + 10)
                    {
                        camera.move(0, -10);
                    }
                    else if(camera.getCenter().y < (*i)->getPoseY() - 10)
                    {
                        camera.move(0, 10);
                    }
                    else
                    {
                        camera.setCenter(camera.getCenter().x, (*i)->getPoseY());
                    }

                    if(camera.getCenter().x > (*i)->getPoseX() + 10)
                    {
                        camera.move(-10, 0);
                    }
                    else if(camera.getCenter().x < (*i)->getPoseX() - 10)
                    {
                        camera.move(10, 0);
                    }
                    else
                    {
                        camera.setCenter((*i)->getPoseX(), camera.getCenter().y);
                    }

                    if(camera.getCenter().x == (*i)->getPoseX() && camera.getCenter().y == (*i)->getPoseY())
                    {
                        moveFinish = true;
                    }
                }
                if(moveCam == true)
                {
                    moveCam = false;
                    if((*i)->action(this))
                    {
                        moveCam = true;
                        moveFinish = false;
                        delete (*i);
                        listEvent.erase(i);
                    }
                }
                if(listActiveEnemy.empty())
                {
                    if((*i)->action(this))
                    {
                        moveCam = true;
                        moveFinish = false;
                        delete (*i);
                        listEvent.erase(i);
                    }
                }
                break;
            }
        }
    }

    return returnStat;
}

void gamePlayedClass::checkCollisionWithChara(characterClass& chara)
{
    if(chara.getType() == "PLAYER")
    {
        for(std::list<characterClass*>::iterator i = listActiveEnemy.begin(); i != listActiveEnemy.end(); )
        {
            if(player.getWeapon() == "FISTS")
            {
                if(player.inStriking() && player.inMomentStrike())
                {
                    if(player.getPoseStrike().getGlobalBounds().intersects((*i)->getHitBox()) && ((*i)->getIsBoss() == false || ((*i)->getIsBoss() == true && listActiveEnemy.size() == 1)))
                    {
                        if((*i)->getWeapon() == "FISTS")
                        {
                            if(player.getDirPlayer() == RIGHT)
                            {
                                pusheChara(*(*i), 20, 3);
                            }
                            else
                            {
                                pusheChara(*(*i), 20, -3);
                            }
                        }
                        if(getBlow(*(*i), player.getDamage()))
                        {
                            listEntity.push_back(new basicEnemyClass((*i)->getPosePlayer().x + ((*i)->getSpriteDraw().getGlobalBounds().width / 2) - 5, (*i)->getPosePlayer().y + ((*i)->getSpriteDraw().getGlobalBounds().height / 2) - 5, "COIN"));
                            if(rand() % 100 > 50)
                                listEntity.back()->setDirPlayer(LEFT);
                            else
                                listEntity.back()->setDirPlayer(RIGHT);
                            (*i)->setLife(0);
                            ++i;
                            continue;
                        }
                    }
                }
            }

            if((*i)->inStriking() && (*i)->getLife() > 0)
            {
                if((*i)->getDirectDamage())
                {
                    if((*i)->getPoseStrike().getGlobalBounds().intersects(player.getHitBox()))
                    {
                        getBlow(player, (*i)->getDamage());
                        if((*i)->getWeapon() == "SUICIDE")
                        {
                            (*i)->setLife(0);
                            particleMotor.creatExplosion((*i)->getPosePlayer(), sf::Vector2f((*i)->getSpriteDraw().getGlobalBounds().width, (*i)->getSpriteDraw().getGlobalBounds().height));
                        }
                    }
                }
            }
            ++i;
        }
    }
    else if(chara.getLife() > 0)
    {
        if(chara.inStriking())
        {
            if(chara.getDirectDamage())
            {
                if(chara.getVersusEnemy())
                {
                    for(std::list<characterClass*>::iterator j = listActiveEnemy.begin(); j != listActiveEnemy.end(); )
                    {
                        if(chara.getPoseStrike().getGlobalBounds().intersects((*j)->getHitBox()) && ((*j)->getIsBoss() == false || ((*j)->getIsBoss() == true && listActiveEnemy.size() == 1)))
                        {
                            if(getBlow(*(*j), chara.getDamage() * player.getDamage()))
                            {
                                listEntity.push_back(new basicEnemyClass((*j)->getPosePlayer().x + ((*j)->getSpriteDraw().getGlobalBounds().width / 2) - 5, (*j)->getPosePlayer().y + ((*j)->getSpriteDraw().getGlobalBounds().height / 2) - 5, "COIN"));
                                if(rand() % 100 > 50)
                                    listEntity.back()->setDirPlayer(LEFT);
                                else
                                    listEntity.back()->setDirPlayer(RIGHT);
                                (*j)->setLife(0);
                            }
                            chara.setLife(0);
                            break;
                        }
                        ++j;
                    }
                }
                else
                {
                    if(player.inStriking() && player.getWeapon() == "FISTS" && chara.getIsInvinsible() == false && player.inMomentStrike())
                    {
                        if(player.getPoseStrike().getGlobalBounds().intersects(chara.getHitBox()) && (chara.getIsBoss() == false || (chara.getIsBoss() == true && listActiveEnemy.size() == 1)))
                        {
                            if(chara.getWeapon() == "FISTS")
                            {
                                if(player.getDirPlayer() == RIGHT)
                                {
                                    pusheChara(chara, 20, 3);
                                }
                                else
                                {
                                    pusheChara(chara, 20, -3);
                                }
                            }
                            if(getBlow(chara, 1 * player.getDamage()))
                            {
                                listEntity.push_back(new basicEnemyClass(chara.getPosePlayer().x + (chara.getSpriteDraw().getGlobalBounds().width / 2) - 5, chara.getPosePlayer().y + (chara.getSpriteDraw().getGlobalBounds().height / 2) - 5, "COIN"));
                                if(rand() % 100 > 50)
                                    listEntity.back()->setDirPlayer(LEFT);
                                else
                                    listEntity.back()->setDirPlayer(RIGHT);
                                chara.setLife(0);
                            }
                        }
                    }
                    if(chara.getPoseStrike().getGlobalBounds().intersects(player.getHitBox()) && chara.getLife() > 0)
                    {
                        if(chara.getIsMoney())
                        {
                            player.moveMoneySup(chara.getDamage());
                            chara.setLife(0);
                        }
                        else
                        {
                            getBlow(player, chara.getDamage());
                            if(chara.getDeathToColli() == true)
                            {
                                chara.setLife(0);
                            }
                        }
                    }
                }
            }
        }
    }
}

bool gamePlayedClass::getBlow(characterClass& character, float strenght)
{
    if(!character.getTimeInvincibleIsStart())
    {
        character.getTimeInvincible().start();
        character.setTimeInvincibleIsStart(true);
        return character.decreaseLife(strenght / character.getResistance());
    }
    return false;
}

void gamePlayedClass::addXPosePlayer(characterClass& character, double x, bool updateCamera)
{
    x *= (globalClass::getTimeFrame() * 61);
    x *= character.getSpeed();

    if((x == 0 || character.getTypePlayer() == STRIKING))
    {
        if(character.getSkid() != 0)
        {
            if(character.getSkid() > 0)
                character.setDirPlayer(RIGHT);
            else
                character.setDirPlayer(LEFT);

            if(!moveChara(character, character.getSkid()))
                character.setSkid(0);
            else
            {
                int tmpTime = (globalClass::getTimeFrame() * 61);
                if(tmpTime == 0)
                {
                    tmpTime = 1;
                }
                if(character.getSkid() > 0)
                {
                    character.moveSkid(-tmpTime);
                    if(character.getSkid() < 0)
                        character.setSkid(0);
                }
                else
                {
                    character.moveSkid(tmpTime);
                    if(character.getSkid() > 0)
                        character.setSkid(0);
                }
            }

            if(updateCamera)
                setCameraTo(character);
        }
        else
        {
            colliWithItem(character, false);
            if(updateCamera)
                setCameraTo(character);
        }
    }
    if(character.getTypePlayer() == STRIKING)
        return;
    if(x == 0)
    {
        if(character.getTypePlayer() != JUMP)
        {
            character.setTypePlayer(NOTHING);
        }
        return;
    }
    if(character.getTypePlayer() != JUMP)
        character.setTypePlayer(WALKING);
    if(x > 0)
        character.setDirPlayer(RIGHT);
    else
        character.setDirPlayer(LEFT);

    moveChara(character, x);
    if(updateCamera)
            setCameraTo(character);

    character.setSkid(x / (globalClass::getTimeFrame() * 61));
    if(character.getSkid() > 10 || character.getSkid() < -10)
    {
        character.setSkid(character.getSkid() > 10 ? 10 : -10);
    }
}

void gamePlayedClass::jumping(characterClass& jumpPlayer, float percentDist)
{
    int tmpJumpLong = 0;
    static int totDistJump = 0;
    static int actuDistJump = 0;

    if(jumpPlayer.getTypePlayer() != STRIKING)
        jumpPlayer.setTypePlayer(JUMP);
    if(jumpPlayer.getSpeedJump() == 0)
        setNoJump(jumpPlayer);
    else
    {
        if(percentDist == 0 && totDistJump != 0)
        {
            tmpJumpLong = totDistJump - actuDistJump;
            totDistJump = 0;
            actuDistJump = 0;
        }
        else if(percentDist == 0 && totDistJump == 0)
        {
            jumpPlayer.setOldPosY(jumpPlayer.getColliBox().getPosition().y);
            if(jumpPlayer.getDistanceJump() == 0)
            {
                jumpPlayer.setSpeedJump(0);
            }
            else if((jumpPlayer.getSpeedJump() * globalClass::getTimeFrame() * 61) > jumpPlayer.getDistanceJump())
            {
                tmpJumpLong = jumpPlayer.getDistanceJump();
                jumpPlayer.setDistanceJump(0);
                jumpPlayer.setSpeedJump(0);
            }
            else
            {
                tmpJumpLong = jumpPlayer.getSpeedJump() * (globalClass::getTimeFrame() * 61);
                jumpPlayer.moveDistanceJump(-jumpPlayer.getSpeedJump() * (globalClass::getTimeFrame() * 61));
                jumpPlayer.moveSpeedJump(-1 * (globalClass::getTimeFrame() * 61));
                if(jumpPlayer.getSpeedJump() < 0 || jumpPlayer.getSpeedJump() < (1 * (globalClass::getTimeFrame() * 61)) / 2)
                {
                    jumpPlayer.setDistanceJump(0);
                    jumpPlayer.setSpeedJump(0);
                }
            }
        }
        else if(percentDist != 0 && totDistJump == 0)
        {
            jumpPlayer.setOldPosY(jumpPlayer.getColliBox().getPosition().y);
            if(jumpPlayer.getDistanceJump() == 0)
            {
                jumpPlayer.setSpeedJump(0);
            }
            else if((jumpPlayer.getSpeedJump() * globalClass::getTimeFrame() * 61) > jumpPlayer.getDistanceJump())
            {
                totDistJump = jumpPlayer.getDistanceJump();
                jumpPlayer.setDistanceJump(0);
                jumpPlayer.setSpeedJump(0);
            }
            else
            {
                totDistJump = jumpPlayer.getSpeedJump() * (globalClass::getTimeFrame() * 61);
                jumpPlayer.moveDistanceJump(-jumpPlayer.getSpeedJump() * (globalClass::getTimeFrame() * 61));
                jumpPlayer.moveSpeedJump(-1 * (globalClass::getTimeFrame() * 61));
                if(jumpPlayer.getSpeedJump() < 0 || jumpPlayer.getSpeedJump() < (1 * (globalClass::getTimeFrame() * 61)) / 2)
                {
                    jumpPlayer.setDistanceJump(0);
                    jumpPlayer.setSpeedJump(0);
                }
            }

            tmpJumpLong = totDistJump / (100.f / percentDist);
            if(tmpJumpLong == 0)
            {
                tmpJumpLong = 1;
            }
            actuDistJump += tmpJumpLong;
        }
        else if(percentDist != 0 && totDistJump != 0)
        {
            tmpJumpLong = totDistJump / (100.f / percentDist);
            if(tmpJumpLong == 0)
            {
                tmpJumpLong = 1;
            }
            actuDistJump += tmpJumpLong;
            if(actuDistJump >= totDistJump)
            {
                tmpJumpLong -= actuDistJump - totDistJump;
            }
            if(tmpJumpLong == 0)
            {
                tmpJumpLong = 1;
            }
        }

        while(tmpJumpLong > 0)
        {
            if(tmpJumpLong > 19)
            {
                jumpPlayer.movePosePlayer(0, -19);
                tmpJumpLong -= 19;
            }
            else
            {
                jumpPlayer.movePosePlayer(0, -tmpJumpLong);
                tmpJumpLong = 0;
            }

            if(((jumpPlayer.getType() == "PLAYER" || moveCam == false) ? jumpPlayer.getColliBox().getPosition().y < (camera.getCenter().y - 240) : jumpPlayer.getColliBox().getPosition().y < 0))
            {
                jumpPlayer.setPosePlayer(jumpPlayer.getPosePlayer().x, ((jumpPlayer.getType() == "PLAYER" || moveCam == false) ? (camera.getCenter().y - 240) - (jumpPlayer.getColliBox().getPosition().y - jumpPlayer.getPosePlayer().y) : 0 - (jumpPlayer.getColliBox().getPosition().y - jumpPlayer.getPosePlayer().y)));

                setNoJump(jumpPlayer);
                totDistJump = 0;
                actuDistJump = 0;
                break;
            }
            else if(!colliWithItem(jumpPlayer, true, true))
            {
                setNoJump(jumpPlayer);
                totDistJump = 0;
                actuDistJump = 0;
                break;
            }
        }
    }
}

void gamePlayedClass::setStrikePlayer()
{
    if(player.inStriking() == false)
    {
        player.setStrike();
        if(player.getWeapon() == "LASER_RIFLE")
        {
            if(player.getDirPlayer() == LEFT)
            {
                listEntity.push_back(new basicEnemyClass(player.getPosePlayer().x - 19, player.getPosePlayer().y + 32, "LASER_POSI"));
                listEntity.back()->setDirPlayer(LEFT);
            }
            else
            {
                listEntity.push_back(new basicEnemyClass(player.getPosePlayer().x + 28, player.getPosePlayer().y + 32, "LASER_POSI"));
                listEntity.back()->setDirPlayer(RIGHT);
            }
        }
    }
}

void gamePlayedClass::setJumpingPlayer()
{
    player.setJumping();
}

void gamePlayedClass::movePlayer(int x)
{
    addXPosePlayer(player, x, moveCam);
}

void gamePlayedClass::moveEnemyWithChara(characterClass& chara)
{
    if(chara.getWeapon() == "FISTS")
    {
        if(chara.getIsPushed())
        {
            pusheChara(chara);
        }
        else
        {
            if(chara.getStaticChara())
            {
                addXPosePlayer(chara, 0);
                if(chara.getChangeDir())
                {
                    if(chara.getPosePlayer().x <= player.getPosePlayer().x + 64 && chara.getPosePlayer().x >= player.getPosePlayer().x - 44)
                    {
                        if(!chara.inStriking())
                        {
                            if(chara.getTimeStrikeWaitIsStart() && chara.getTimeStrikeWait().getTime() > 0.2)
                            {
                                if(chara.getPosePlayer().x  > player.getPosePlayer().x + 20)
                                    chara.setDirPlayer(LEFT);
                                else if(chara.getPosePlayer().x  < player.getPosePlayer().x - 18)
                                    chara.setDirPlayer(RIGHT);
                                chara.setStrike();
                                chara.setTimeStrikeWaitIsStart(false);
                            }
                            else if(!chara.getTimeStrikeWaitIsStart())
                            {
                                chara.setTimeStrikeWaitIsStart(true);
                                chara.getTimeStrikeWait().start();
                            }
                        }
                    }
                }
                else
                {
                    if(chara.getDirPlayer() == LEFT)
                    {
                        if(chara.getPosePlayer().x >= player.getPosePlayer().x && chara.getPosePlayer().x <= player.getPosePlayer().x + 64)
                        {
                            if(!chara.inStriking())
                            {
                                if(chara.getTimeStrikeWaitIsStart() && chara.getTimeStrikeWait().getTime() > 0.2)
                                {
                                    chara.setStrike();
                                    chara.setTimeStrikeWaitIsStart(false);
                                }
                                else if(!chara.getTimeStrikeWaitIsStart())
                                {
                                    chara.setTimeStrikeWaitIsStart(true);
                                    chara.getTimeStrikeWait().start();
                                }
                            }
                        }

                    }
                    else
                    {
                        if(chara.getPosePlayer().x >= player.getPosePlayer().x - 44 && chara.getPosePlayer().x <= player.getPosePlayer().x + 64)
                        {
                            if(!chara.inStriking())
                            {
                                if(chara.getTimeStrikeWaitIsStart() && chara.getTimeStrikeWait().getTime() > 0.2)
                                {
                                    chara.setStrike();
                                    chara.setTimeStrikeWaitIsStart(false);
                                }
                                else if(!chara.getTimeStrikeWaitIsStart())
                                {
                                    chara.setTimeStrikeWaitIsStart(true);
                                    chara.getTimeStrikeWait().start();
                                }
                            }
                        }
                    }
                }

            }
            else
            {
                if(chara.getPosePlayer().x > player.getPosePlayer().x + 64)
                    addXPosePlayer(chara, -1);
                else if(chara.getPosePlayer().x < player.getPosePlayer().x - 44)
                    addXPosePlayer(chara, 1);
                else
                {
                    addXPosePlayer(chara, 0);
                    if(!chara.inStriking())
                    {
                        if(chara.getTimeStrikeWaitIsStart() && chara.getTimeStrikeWait().getTime() > 0.2)
                        {
                            if(chara.getPosePlayer().x  > player.getPosePlayer().x + 20)
                                chara.setDirPlayer(LEFT);
                            else if(chara.getPosePlayer().x  < player.getPosePlayer().x - 18)
                                chara.setDirPlayer(RIGHT);
                            chara.setStrike();
                            chara.setTimeStrikeWaitIsStart(false);
                        }
                        else if(!chara.getTimeStrikeWaitIsStart())
                        {
                            chara.setTimeStrikeWaitIsStart(true);
                            chara.getTimeStrikeWait().start();
                        }
                    }
                }
            }
        }
    }
    else if(chara.getWeapon() == "SUICIDE")
    {
        if(!chara.getStaticChara())
        {
            if(chara.getPosePlayer().x >= player.getPosePlayer().x + 40)
                addXPosePlayer(chara, -1);
            else if(chara.getPosePlayer().x + 40 <= player.getPosePlayer().x)
                addXPosePlayer(chara, 1);
            else
                addXPosePlayer(chara, 0);
        }
        else
            addXPosePlayer(chara, 0);
    }
    else if(chara.getWeapon() == "LASER_RIFLE")
    {
        if(chara.getStaticChara())
        {
            addXPosePlayer(chara, 0);
            if(chara.getChangeDir())
            {
                if(!chara.inStriking())
                {
                    if(player.getPosePlayer().x < chara.getPoseStrike().getGlobalBounds().left + chara.getPoseStrike().getGlobalBounds().width)
                    {
                        chara.setDirPlayer(LEFT);
                        chara.setStrike();
                        listEntity.push_back(new basicEnemyClass(chara.getPoseStrike().getPosition().x, chara.getPoseStrike().getPosition().y, "LASER"));
                        listEntity.back()->setDirPlayer(LEFT);
                        listEntity.back()->setDamage(chara.getDamage());
                    }
                    else if(player.getPosePlayer().x + player.getSpriteDraw().getGlobalBounds().width > chara.getPoseStrike().getGlobalBounds().left)
                    {
                        chara.setDirPlayer(RIGHT);
                        chara.setStrike();
                        listEntity.push_back(new basicEnemyClass(chara.getPoseStrike().getPosition().x, chara.getPoseStrike().getPosition().y, "LASER"));
                        listEntity.back()->setDirPlayer(RIGHT);
                        listEntity.back()->setDamage(chara.getDamage());
                    }
                }
            }
            else
            {
                if(!chara.inStriking())
                {
                    if(chara.getDirPlayer() == LEFT)
                    {
                        if(player.getPosePlayer().x < chara.getPoseStrike().getGlobalBounds().left + chara.getPoseStrike().getGlobalBounds().width)
                        {
                            chara.setStrike();
                            listEntity.push_back(new basicEnemyClass(chara.getPoseStrike().getPosition().x, chara.getPoseStrike().getPosition().y, "LASER"));
                            listEntity.back()->setDirPlayer(LEFT);
                            listEntity.back()->setDamage(chara.getDamage());
                        }
                    }
                    else
                    {
                        if(player.getPosePlayer().x + player.getSpriteDraw().getGlobalBounds().width > chara.getPoseStrike().getGlobalBounds().left)
                        {
                            chara.setStrike();
                            listEntity.push_back(new basicEnemyClass(chara.getPoseStrike().getPosition().x, chara.getPoseStrike().getPosition().y, "LASER"));
                            listEntity.back()->setDirPlayer(RIGHT);
                            listEntity.back()->setDamage(chara.getDamage());
                        }
                    }
                }
            }

        }
        else
        {
            if(chara.getPosePlayer().x > player.getPosePlayer().x + 264)
                addXPosePlayer(chara, -1);
            else if(chara.getPosePlayer().x < player.getPosePlayer().x - 244)
                addXPosePlayer(chara, 1);
            else if(chara.getPosePlayer().x > player.getPosePlayer().x && chara.getPosePlayer().x < player.getPosePlayer().x + 80)
                addXPosePlayer(chara, 1);
            else if(chara.getPosePlayer().x < player.getPosePlayer().x && chara.getPosePlayer().x > player.getPosePlayer().x - 60)
                addXPosePlayer(chara, -1);
            else
            {
                addXPosePlayer(chara, 0);
                if(chara.getPosePlayer().x > player.getPosePlayer().x)
                    chara.setDirPlayer(LEFT);
                else
                    chara.setDirPlayer(RIGHT);
                if(!chara.inStriking())
                {
                    chara.setStrike();
                    if(chara.getDirPlayer() == LEFT)
                    {
                        listEntity.push_back(new basicEnemyClass(chara.getPoseStrike().getPosition().x, chara.getPoseStrike().getPosition().y, "LASER"));
                        listEntity.back()->setDirPlayer(LEFT);
                        listEntity.back()->setDamage(chara.getDamage());
                    }
                    else
                    {
                        listEntity.push_back(new basicEnemyClass(chara.getPoseStrike().getPosition().x, chara.getPoseStrike().getPosition().y, "LASER"));
                        listEntity.back()->setDirPlayer(RIGHT);
                        listEntity.back()->setDamage(chara.getDamage());
                    }
                }
            }
        }
    }
    else if(chara.getWeapon() == "BEAM_RIFLE")
    {
        if(chara.getStaticChara())
        {
            addXPosePlayer(chara, 0);
            if(chara.getPosePlayer().x + 12 < player.getPosePlayer().x + 40 && chara.getPosePlayer().x + 27 > player.getPosePlayer().x)
            {
                if(!chara.inStriking())
                {
                    chara.setStrike();
                    listEntity.push_back(new basicEnemyClass(chara.getPoseStrike().getPosition().x, chara.getPoseStrike().getPosition().y, "BEAM"));
                    listEntity.back()->setDamage(chara.getDamage());
                }
            }
        }
        else
        {
            if(chara.getPosePlayer().x + 12 >= player.getPosePlayer().x + 40)
                addXPosePlayer(chara, -1);
            else if(chara.getPosePlayer().x + 27 <= player.getPosePlayer().x)
                addXPosePlayer(chara, 1);
            else
                addXPosePlayer(chara, 0);

            if(!chara.inStriking())
            {
                chara.setStrike();
                listEntity.push_back(new basicEnemyClass(chara.getPosePlayer().x + 12, chara.getPosePlayer().y + 26, "BEAM"));
                listEntity.back()->setDamage(chara.getDamage());
            }
        }
    }
    if(chara.getMoveDir())
    {
        if(chara.getTypePlayer() != NOTHING)
        {
            if(chara.getDirPlayer() == LEFT)
                addXPosePlayer(chara, -1);
            else if(chara.getDirPlayer() == RIGHT)
                addXPosePlayer(chara, 1);
        }
        else
            addXPosePlayer(chara, 0);
    }
}

void gamePlayedClass::newLevel(bool dead)
{
    player.moveMoney(player.getMoneySup());
    player.setMoneySup(0);
    endOfLevel = 1280;
    heightLevel = 480;
    typeLevel.clear();
    for(std::list<eventClass*>::iterator i = listEvent.begin(); i != listEvent.end(); )
    {
        delete (*i);;
        listEvent.erase(i++);
    }

    for(std::list<characterClass*>::iterator i = listEnemy.begin(); i != listEnemy.end(); )
    {
        delete (*i);
        listEnemy.erase(i++);
    }

    for(std::list<characterClass*>::iterator i = listActiveEnemy.begin(); i != listActiveEnemy.end(); )
    {
        delete (*i);
        listActiveEnemy.erase(i++);
    }
    for(std::list<characterClass*>::iterator i = listEntity.begin(); i != listEntity.end(); )
    {
        delete (*i);
        listEntity.erase(i++);
    }
    for(std::map<std::pair<int, int>, itemClass*>::iterator i = mapLevel.begin(); i != mapLevel.end(); )
    {
        delete i->second;
        mapLevel.erase(i++);
    }
    lightManager.deleteAllLight();
    lightManager.deleteAllWall();
    player.setLife(player.getUpgrad("life") + 200);
    player.setDirPlayer(RIGHT);
    player.setSkid(0);
    player.setSpeedJump(player.getJumpPower());
    player.setSpeedFalling(0);
    player.setTypePlayer(NOTHING);
    lifePlayer.setSize(sf::Vector2f(player.getLife(), 10));
    moveCam = true;
    if(dead == true)
    {
        level.setLevel(listEvent, listEnemy, mapLevel, endOfLevel, heightLevel, typeLevel, lightManager, player.getPosePlayer().x);
    }
    else
    {
        level.setLevel(listEvent, listEnemy, mapLevel, endOfLevel, heightLevel, typeLevel, lightManager);
    }
    if(typeLevel == "DARK")
    {
        playerLight = lightManager.addDynamicLight(sf::Vector2f(player.getColliBox().getPosition().x + (player.getColliBox().getGlobalBounds().width / 2), player.getColliBox().getPosition().y + (player.getColliBox().getGlobalBounds().height / 2)), 255, 160, 32, sf::Color::White);
    }
    background[0].setPosition(0, heightLevel - 480);
    background[1].setPosition(800, heightLevel - 480);
    camera.setCenter(320, heightLevel - 240);
    player.setPosePlayer(50.f, heightLevel - 80.f);
    setNoJump(player);
}

bool gamePlayedClass::colliWithItem(characterClass& chara, bool move, bool inJump, bool secondPass)
{
    std::map<std::pair<int, int>, itemClass*>::iterator tmpItem;
    int charaMove = true;
    for(int i = chara.getPosePlayer().x / 20 - 1; i <= chara.getPosePlayer().x / 20 + 3; ++i)
    {
        for(int j = chara.getPosePlayer().y / 20 - 1; j <= chara.getPosePlayer().y / 20 + 5; ++j)
        {
            tmpItem = mapLevel.find(std::pair<int, int>(i, j));
            if(tmpItem != mapLevel.end())
            {
                if(tmpItem->second->getStatBlock("DAMAGE") && secondPass)
                {
                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        if(tmpItem->second->getValueDamage() > 0)
                        {
                            if(getBlow(chara, tmpItem->second->getValueDamage()) == true && tmpItem->second->getType() == "LAVA")
                            {
                                particleMotor.creatFlame(chara.getPosePlayer(), sf::Vector2f(chara.getSpriteDraw().getGlobalBounds().width, chara.getSpriteDraw().getGlobalBounds().height));
                            }
                        }
                        else
                            chara.moveLife(-tmpItem->second->getValueDamage());
                    }
                }
                if(tmpItem->second->getStatBlock("SOLID") && move == true && chara.getAffectToWall())
                {
                    if(tmpItem->second->getStatBlock("SOLID_LASER") == false && chara.getIsLaser())
                    {
                        continue;
                    }

                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        if(!inJump)
                        {
                            charaMove = false;
                            if(chara.getDirPlayer() == LEFT)
                            {
                                chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x + 20 - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                if(chara.getDeathToColli())
                                    chara.setLife(0);
                            }
                            else
                            {
                                chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x - chara.getColliBox().getGlobalBounds().width - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                if(chara.getDeathToColli())
                                    chara.setLife(0);
                            }
                        }
                        else
                        {
                            charaMove = false;
                            if(chara.getInJump())
                                chara.setPosePlayer(chara.getPosePlayer().x, tmpItem->second->getSkin().getPosition().y + 20 - (chara.getColliBox().getPosition().y - chara.getPosePlayer().y));
                            else
                                chara.setPosePlayer(chara.getPosePlayer().x, tmpItem->second->getSkin().getPosition().y - chara.getColliBox().getGlobalBounds().height - (chara.getColliBox().getPosition().y - chara.getPosePlayer().y));
                        }
                    }
                }
                if(tmpItem->second->getStatBlock("MOVE_DOWN"))
                {
                    if(tmpItem->second->getStatBlock("SOLID_LASER") == false && chara.getIsLaser())
                    {
                        continue;
                    }

                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        if(inJump)
                        {
                            if(!chara.getInJump() && ((chara.getOldPosY() - 1 + chara.getColliBox().getGlobalBounds().height) <= tmpItem->second->getSkin().getPosition().y))
                            {
                                chara.setPosePlayer(chara.getPosePlayer().x, tmpItem->second->getSkin().getPosition().y - chara.getColliBox().getGlobalBounds().height - (chara.getColliBox().getPosition().y - chara.getPosePlayer().y));
                                charaMove = false;
                            }
                        }
                    }
                }
                if(tmpItem->second->getStatBlock("MOVE_UP"))
                {
                    if(tmpItem->second->getStatBlock("SOLID_LASER") == false && chara.getIsLaser())
                    {
                        continue;
                    }

                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        if(inJump)
                        {
                            if(chara.getInJump() && ((chara.getOldPosY() + 2) >= tmpItem->second->getSkin().getPosition().y + 20))
                            {
                                chara.setPosePlayer(chara.getPosePlayer().x, tmpItem->second->getSkin().getPosition().y + 20 - (chara.getColliBox().getPosition().y - chara.getPosePlayer().y));
                                charaMove = false;
                            }
                        }
                    }
                }
                if(tmpItem->second->getStatBlock("MOVE_LEFT"))
                {
                    if(tmpItem->second->getStatBlock("SOLID_LASER") == false && chara.getIsLaser())
                    {
                        continue;
                    }

                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        if(!inJump)
                        {
                            if(chara.getDirPlayer() == LEFT && ((chara.getOldPosX() + 1) >= tmpItem->second->getSkin().getPosition().x + 20))
                            {
                                chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x + 20 - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                charaMove = false;
                            }
                        }
                    }
                }
                if(tmpItem->second->getStatBlock("MOVE_RIGHT"))
                {
                    if(tmpItem->second->getStatBlock("SOLID_LASER") == false && chara.getIsLaser())
                    {
                        continue;
                    }

                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        if(!inJump)
                        {
                            if(chara.getDirPlayer() == RIGHT && (chara.getOldPosX() - 1 + chara.getColliBox().getGlobalBounds().width) <= tmpItem->second->getSkin().getPosition().x)
                            {
                                chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x - 40 - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                charaMove = false;
                            }
                        }
                    }
                }
                if(tmpItem->second->getStatBlock("STAIR_LEFT"))
                {
                    if(tmpItem->second->getStatBlock("SOLID_LASER") == false && chara.getIsLaser())
                    {
                        continue;
                    }

                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        bool tmpMove = true;
                        std::map<std::pair<int, int>, itemClass*>::iterator secondTmpItem;
                        if(!inJump)
                        {
                            secondTmpItem = mapLevel.find(std::pair<int, int>(i + 1, j + 1));
                            if(secondTmpItem == mapLevel.end())
                            {
                                if(chara.getDirPlayer() == LEFT && ((chara.getColliBox().getPosition().y + chara.getColliBox().getGlobalBounds().height) > tmpItem->second->getSkin().getPosition().y + 20))
                                {
                                    chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x + 20 - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                    charaMove = false;
                                    tmpMove = false;
                                }
                            }
                            else
                            {
                                if(chara.getDirPlayer() == LEFT && ((chara.getColliBox().getPosition().y + chara.getColliBox().getGlobalBounds().height) > tmpItem->second->getSkin().getPosition().y + (secondTmpItem->second->getStatBlock("STAIR_LEFT") ? 40 : 20)))
                                {
                                    chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x + 20 - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                    charaMove = false;
                                    tmpMove = false;
                                }
                            }
                        }
                        if(tmpMove)
                        {
                            int tmpPoseStair = (tmpItem->second->getSkin().getPosition().x + 20 - chara.getColliBox().getPosition().x);
                            int tmpWidthChara = chara.getColliBox().getGlobalBounds().width / 20;
                            int tmpHeightChara = chara.getColliBox().getGlobalBounds().height / 20;
                            if((int)chara.getColliBox().getGlobalBounds().width % 20 != 0)
                            {
                                tmpWidthChara += 1;
                            }
                            if((int)chara.getColliBox().getGlobalBounds().height % 20 != 0)
                            {
                                tmpHeightChara += 1;
                            }

                            for(int l = j - 1; l >= j - tmpHeightChara; --l)
                            {
                                secondTmpItem = mapLevel.find(std::pair<int, int>(i, l));
                                if(secondTmpItem != mapLevel.end())
                                {
                                    if(secondTmpItem->second->getStatBlock("MOVE_LEFT") || secondTmpItem->second->getStatBlock("MOVE_UP") || secondTmpItem->second->getStatBlock("SOLID"))
                                    {
                                        chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x + 20 - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                        tmpMove = false;
                                        break;
                                    }
                                }
                            }

                            if(tmpMove)
                            {
                                for(int k = i + 1; k <= i + tmpWidthChara; ++k)
                                {
                                    secondTmpItem = mapLevel.find(std::pair<int, int>(k, j - tmpHeightChara));
                                    if(secondTmpItem != mapLevel.end() && tmpPoseStair < 20)
                                    {
                                        if(secondTmpItem->second->getStatBlock("MOVE_LEFT") || secondTmpItem->second->getStatBlock("MOVE_UP") || secondTmpItem->second->getStatBlock("SOLID"))
                                        {
                                            chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x + 20 - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                            tmpMove = false;
                                            break;
                                        }
                                    }
                                }
                            }

                            if(tmpMove)
                            {
                                if(tmpPoseStair > 20)
                                {
                                    tmpPoseStair = 20;
                                }
                                int newPos = tmpItem->second->getSkin().getPosition().y + 20 - tmpPoseStair - chara.getColliBox().getGlobalBounds().height - (chara.getColliBox().getPosition().y - chara.getPosePlayer().y);
                                if(newPos < chara.getPosePlayer().y)
                                {
                                    chara.setPosePlayer(chara.getPosePlayer().x, newPos);
                                    charaMove = false;
                                }
                            }
                        }
                    }
                }
                if(tmpItem->second->getStatBlock("STAIR_RIGHT"))
                {
                    if(tmpItem->second->getStatBlock("SOLID_LASER") == false && chara.getIsLaser())
                    {
                        continue;
                    }

                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        bool tmpMove = true;
                        std::map<std::pair<int, int>, itemClass*>::iterator secondTmpItem;
                        if(!inJump)
                        {
                            secondTmpItem = mapLevel.find(std::pair<int, int>(i - 1, j - 1));
                            if(secondTmpItem == mapLevel.end())
                            {
                                if(chara.getDirPlayer() == RIGHT && ((chara.getColliBox().getPosition().y + chara.getColliBox().getGlobalBounds().height) > tmpItem->second->getSkin().getPosition().y + 20))
                                {
                                    chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x - chara.getColliBox().getGlobalBounds().width - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                    charaMove = false;
                                    tmpMove = false;
                                }
                            }
                            else
                            {
                                if(chara.getDirPlayer() == RIGHT && ((chara.getColliBox().getPosition().y + chara.getColliBox().getGlobalBounds().height) > tmpItem->second->getSkin().getPosition().y + (secondTmpItem->second->getStatBlock("STAIR_RIGHT") ? 40 : 20)))
                                {
                                    chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x - chara.getColliBox().getGlobalBounds().width - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                    charaMove = false;
                                    tmpMove = false;
                                }
                            }
                        }
                        if(tmpMove)
                        {
                            int tmpPoseStair = (chara.getColliBox().getPosition().x + chara.getColliBox().getGlobalBounds().width - tmpItem->second->getSkin().getPosition().x);
                            int tmpWidthChara = chara.getColliBox().getGlobalBounds().width / 20;
                            int tmpHeightChara = chara.getColliBox().getGlobalBounds().height / 20;
                            if((int)chara.getColliBox().getGlobalBounds().width % 20 != 0)
                            {
                                tmpWidthChara += 1;
                            }
                            if((int)chara.getColliBox().getGlobalBounds().height % 20 != 0)
                            {
                                tmpHeightChara += 1;
                            }

                            for(int l = j - 1; l >= j - tmpHeightChara; --l)
                            {
                                secondTmpItem = mapLevel.find(std::pair<int, int>(i, l));
                                if(secondTmpItem != mapLevel.end())
                                {
                                    if(secondTmpItem->second->getStatBlock("MOVE_RIGHT") || secondTmpItem->second->getStatBlock("MOVE_UP") || secondTmpItem->second->getStatBlock("SOLID"))
                                    {
                                        chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x - chara.getColliBox().getGlobalBounds().width - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                        tmpMove = false;
                                        break;
                                    }
                                }
                            }

                            if(tmpMove)
                            {
                                for(int k = i - 1; k >= i - tmpWidthChara; --k)
                                {
                                    secondTmpItem = mapLevel.find(std::pair<int, int>(k, j - tmpHeightChara));
                                    if(secondTmpItem != mapLevel.end() && tmpPoseStair < 20)
                                    {
                                        if(secondTmpItem->second->getStatBlock("MOVE_RIGHT") || secondTmpItem->second->getStatBlock("MOVE_UP") || secondTmpItem->second->getStatBlock("SOLID"))
                                        {
                                            chara.setPosePlayer(tmpItem->second->getSkin().getPosition().x - chara.getColliBox().getGlobalBounds().width - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                                            tmpMove = false;
                                            break;
                                        }
                                    }
                                }
                            }

                            if(tmpMove)
                            {
                                if(tmpPoseStair > 20)
                                {
                                    tmpPoseStair = 20;
                                }
                                int newPos = tmpItem->second->getSkin().getPosition().y + 20 - tmpPoseStair - chara.getColliBox().getGlobalBounds().height - (chara.getColliBox().getPosition().y - chara.getPosePlayer().y);
                                if(newPos < chara.getPosePlayer().y)
                                {
                                    chara.setPosePlayer(chara.getPosePlayer().x, newPos);
                                    charaMove = false;
                                }
                            }
                        }
                    }
                }
                if(tmpItem->second->getStatBlock("TEMP") && secondPass)
                {
                    if(chara.getColliBox().getGlobalBounds().intersects(tmpItem->second->getSkin().getGlobalBounds()))
                    {
                        delete tmpItem->second;
                        mapLevel.erase(tmpItem);
                    }
                }
            }
        }
    }

    if(secondPass == false)
    {
        colliWithItem(chara, move, inJump, true);
    }
    else
    {
        checkCollisionWithChara(chara);
    }

    return charaMove;
}

bool gamePlayedClass::moveChara(characterClass& chara, float x)
{
    float percentDist = x / 19;
    float actuPercentDist = 0;
    chara.setOldPosX(chara.getColliBox().getPosition().x);
    while(x != 0)
    {
        if(x > 19 || x < -19)
        {
            chara.movePosePlayer((x > 0 ? 19 : -19), 0);
            x -= (x > 0 ? 19 : -19);
        }
        else
        {
            chara.movePosePlayer(x, 0);
            x = 0;
        }
        if(chara.getType() == "PLAYER" || moveCam == false)
        {
            if(chara.getColliBox().getPosition().x < camera.getCenter().x - 320)
            {
                chara.setPosePlayer(camera.getCenter().x - 320 - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                if(chara.getDeathToColli())
                    chara.setLife(0);

                x = 0;
            }
            else if(chara.getColliBox().getPosition().x > (camera.getCenter().x + 320 - chara.getColliBox().getGlobalBounds().width))
            {
                chara.setPosePlayer((camera.getCenter().x + 320 - chara.getColliBox().getGlobalBounds().width) - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                if(chara.getDeathToColli())
                    chara.setLife(0);

                x = 0;
            }
        }
        else
        {
            if(chara.getColliBox().getPosition().x < 0)
            {
                chara.setPosePlayer(-(chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                if(chara.getDeathToColli())
                    chara.setLife(0);

                x = 0;
            }
            else if(chara.getColliBox().getPosition().x > (endOfLevel - chara.getColliBox().getGlobalBounds().width))
            {
                chara.setPosePlayer((endOfLevel - chara.getColliBox().getGlobalBounds().width) - (chara.getColliBox().getPosition().x - chara.getPosePlayer().x), chara.getPosePlayer().y);
                if(chara.getDeathToColli())
                    chara.setLife(0);

                x = 0;
            }
        }

        if(x != 0)
        {
            if(colliWithItem(chara) == false)
            {
                return false;
            }
        }
        else
        {
            return colliWithItem(chara);
        }

        if(chara.getAffectToGravity())
        {
            if(chara.getInJump())
            {
                if(chara.getFirstFrameJump() == false)
                {
                    //jumping(chara, percentDist);
                }

            }
            else
            {
                falling(chara, percentDist, actuPercentDist);
            }
        }
        actuPercentDist += percentDist;
    }

    return true;
}

void gamePlayedClass::setCameraTo(characterClass& chara)
{

    if(chara.getPosePlayer().x + (chara.getDirPlayer() == LEFT && chara.getTypePlayer() == STRIKING ? 40 : 20) > camera.getCenter().x + (globalClass::getTimeFrame() * 61 * chara.getSpeed()))
        camera.move((int) (globalClass::getTimeFrame() * 61 * chara.getSpeed() + 0.5), 0);
    else if(chara.getPosePlayer().x + (chara.getDirPlayer() == LEFT && chara.getTypePlayer() == STRIKING ? 40 : 20) < camera.getCenter().x - (globalClass::getTimeFrame() * 61 * chara.getSpeed()))
        camera.move((int) (globalClass::getTimeFrame() * 61 * -chara.getSpeed() - 0.5), 0);
    else
        camera.setCenter(chara.getPosePlayer().x + (chara.getDirPlayer() == LEFT && chara.getTypePlayer() == STRIKING ? 40 : 20), camera.getCenter().y);

    if(camera.getCenter().x < 320)
        camera.setCenter(320, camera.getCenter().y);
    else if(camera.getCenter().x > endOfLevel - 320)
        camera.setCenter(endOfLevel - 320, camera.getCenter().y);

    if(chara.getPosePlayer().y + 40 > camera.getCenter().y + (20 * (globalClass::getTimeFrame() * 61)))
        camera.move(0, (int) (20 * (globalClass::getTimeFrame() * 61)));
    else if(chara.getPosePlayer().y + 40 < camera.getCenter().y - (20 * (globalClass::getTimeFrame() * 61)))
        camera.move(0, (int) -(20 * (globalClass::getTimeFrame() * 61)));
    else
        camera.setCenter(camera.getCenter().x, chara.getPosePlayer().y + 40);

    if(camera.getCenter().y < 240)
        camera.setCenter(camera.getCenter().x, 240);
    if(camera.getCenter().y > heightLevel - 240)
        camera.setCenter(camera.getCenter().x, heightLevel - 240);
}

void gamePlayedClass::falling(characterClass& chara, float percentDist, float actuPercentDist)
{
    static int totDistFall = 0;
    static int actuDistFall = 0;
    static float thisActuPercentDist = 0;
    bool change = false;
    int tmpDistFall = 0;

    if(percentDist != 0)
    {
        thisActuPercentDist = actuPercentDist;
    }

    if(percentDist == 0 && totDistFall != 0)
    {
        tmpDistFall = totDistFall - actuDistFall;
        totDistFall = 0;
        actuDistFall = 0;
    }
    else if(percentDist == 0 && totDistFall == 0)
    {
        if(chara.getConstSpeedFalling())
        {
            tmpDistFall = chara.getSpeed() * (globalClass::getTimeFrame() * 61);
        }
        else
        {
            chara.setOldPosY(chara.getColliBox().getPosition().y);
            chara.moveSpeedFalling(1 * (globalClass::getTimeFrame() * 61));
            tmpDistFall = chara.getSpeedFalling() * (globalClass::getTimeFrame() * 61);
        }

        tmpDistFall = tmpDistFall / 100.f * (100 - thisActuPercentDist);
        if(tmpDistFall == 0)
        {
            tmpDistFall = 1;
        }
        thisActuPercentDist = 0;
    }
    else if(percentDist != 0 && totDistFall == 0)
    {
        if(chara.getConstSpeedFalling())
        {
            totDistFall = chara.getSpeed() * (globalClass::getTimeFrame() * 61);
        }
        else
        {
            chara.setOldPosY(chara.getColliBox().getPosition().y);
            chara.moveSpeedFalling(1 * (globalClass::getTimeFrame() * 61));
            totDistFall = chara.getSpeedFalling() * (globalClass::getTimeFrame() * 61);
        }

        totDistFall = totDistFall / 100.f * (100 - actuPercentDist);
        tmpDistFall = totDistFall / (100.f / percentDist);
        if(tmpDistFall == 0)
        {
            tmpDistFall = 1;
        }
        if(totDistFall == 0)
        {
            totDistFall = 1;
        }
        actuDistFall += tmpDistFall;
    }
    else if(percentDist != 0 && totDistFall != 0)
    {
        tmpDistFall = totDistFall / (100.f / percentDist);
        if(tmpDistFall == 0)
        {
            tmpDistFall = 1;
        }
        actuDistFall += tmpDistFall;
        if(actuDistFall >= totDistFall)
        {
            tmpDistFall -= actuDistFall - totDistFall;
        }
        if(tmpDistFall == 0)
        {
            tmpDistFall = 1;
        }
    }

    while(tmpDistFall > 0)
    {
        if(tmpDistFall > 19)
        {
            chara.movePosePlayer(0, 19);
            tmpDistFall -= 19;
        }
        else
        {
            chara.movePosePlayer(0, tmpDistFall);
            tmpDistFall = 0;
        }

        if(((moveCam == false) ? chara.getColliBox().getPosition().y > (camera.getCenter().y + 240 - chara.getColliBox().getGlobalBounds().height) : chara.getColliBox().getPosition().y > heightLevel - chara.getColliBox().getGlobalBounds().height))
        {
            change = true;
            chara.setPosePlayer(chara.getPosePlayer().x, ((moveCam == false) ? (camera.getCenter().y + 240 - chara.getColliBox().getGlobalBounds().height) - (chara.getColliBox().getPosition().y - chara.getPosePlayer().y) : heightLevel - chara.getColliBox().getGlobalBounds().height - (chara.getColliBox().getPosition().y - chara.getPosePlayer().y)));
            if(chara.getBounceChara())
            {
                if(chara.getJumpPower() > 0 || chara.getJumpPower() == -999)
                {
                    if(chara.getSpeedFalling() > 10)
                    {
                        int tmpJumpPower = chara.getJumpPower();
                        chara.setJumpPower(chara.getSpeedFalling() / 1.2);
                        if(chara.getJumpPower() >= tmpJumpPower && tmpJumpPower != -999 && chara.getJumpPower() - 5 <= tmpJumpPower)
                        {
                            chara.setJumpPower(tmpJumpPower - 2);
                        }
                        chara.setSpeedJump(chara.getJumpPower());
                        for(int i = chara.getJumpPower(); i > 0; --i)
                        {
                            chara.moveDistanceJump(i);
                        }
                    }
                    else
                    {
                        if(chara.getJumpPower() == -999)
                        {
                            chara.setJumpPower(5);
                        }
                        chara.moveJumpPower(-1);
                        chara.setSpeedJump(chara.getJumpPower());
                        for(int i = chara.getJumpPower(); i > 0; --i)
                        {
                            chara.moveDistanceJump(i);
                        }
                    }
                    chara.setSpeedFalling(0);
                    chara.moveSpeed(-1);
                    if(chara.getSpeed() <= 0)
                        chara.setSpeed(1);
                    chara.setJumping();
                    chara.setFirstFrameJump(true);
                }
                else
                    chara.setTypePlayer(NOTHING);

                chara.setStrike();
            }
            else if(chara.getDeathToColli())
            {
                chara.setLife(0);
            }
            chara.setSpeedFalling(0);
            if(chara.getTypePlayer() != STRIKING && chara.getTypePlayer() != WALKING)
            {
                if((chara.getSkid() == chara.getSpeed() || chara.getSkid() == -chara.getSpeed()) && chara.getMoveDir() == false)
                {
                    chara.setTypePlayer(WALKING);
                }
                else
                {
                    chara.setTypePlayer(NOTHING);
                }
            }
        }
        if(!colliWithItem(chara, true, true))
        {
            change = true;
            if(chara.getBounceChara())
            {
                if(chara.getJumpPower() > 0 || chara.getJumpPower() == -999)
                {
                    if(chara.getSpeedFalling() > 10)
                    {
                        int tmpJumpPower = chara.getJumpPower();
                        chara.setJumpPower(chara.getSpeedFalling() / 1.2);
                        if(chara.getJumpPower() >= tmpJumpPower && tmpJumpPower != -999 && chara.getJumpPower() - 5 <= tmpJumpPower)
                        {
                            chara.setJumpPower(tmpJumpPower - 2);
                        }
                        chara.setSpeedJump(chara.getJumpPower());
                        for(int i = chara.getJumpPower(); i > 0; --i)
                        {
                            chara.moveDistanceJump(i);
                        }
                    }
                    else
                    {
                        if(chara.getJumpPower() == -999)
                        {
                            chara.setJumpPower(5);
                        }
                        chara.moveJumpPower(-1);
                        chara.setSpeedJump(chara.getJumpPower());
                        for(int i = chara.getJumpPower(); i > 0; --i)
                        {
                            chara.moveDistanceJump(i);
                        }
                    }
                    chara.setSpeedFalling(0);
                    chara.moveSpeed(-1);
                    if(chara.getSpeed() <= 0)
                        chara.setSpeed(1);
                    chara.setJumping();
                    chara.setFirstFrameJump(true);
                }
                else
                    chara.setTypePlayer(NOTHING);

                chara.setStrike();
            }
            else if(chara.getDeathToColli())
            {
                chara.setLife(0);
            }
            chara.setSpeedFalling(0);
            if(chara.getTypePlayer() != STRIKING && chara.getTypePlayer() != WALKING)
            {
                if((chara.getSkid() == chara.getSpeed() || chara.getSkid() == -chara.getSpeed()) && chara.getMoveDir() == false)
                {
                    chara.setTypePlayer(WALKING);
                }
                else
                {
                    chara.setTypePlayer(NOTHING);
                }
            }
        }
        if(change)
        {
            totDistFall = 0;
            actuDistFall = 0;
            break;
        }

        if(chara.getTypePlayer() != STRIKING && change == false)
            chara.setTypePlayer(JUMP);
    }
}

void gamePlayedClass::pusheChara(characterClass& chara, int lenght, int power)
{
    if(lenght != 0 || power != 0)
    {
        chara.setIsPushed(true);
        chara.setLenghtPushed(lenght);
        chara.setPowerPushed(power);
    }

    double moveX = chara.getPowerPushed() * (globalClass::getTimeFrame() * 61);
    int tmpMoveX = moveX;
    chara.stopStrike();

    if(tmpMoveX > 0)
    {
        chara.moveLenghtPushed(-tmpMoveX);
        if(chara.getLenghtPushed() < 0)
        {
            tmpMoveX += chara.getLenghtPushed();
        }
    }
    else if(tmpMoveX < 0)
    {
        chara.moveLenghtPushed(tmpMoveX);
        if(chara.getLenghtPushed() < 0)
        {
            tmpMoveX -= chara.getLenghtPushed();
        }
    }
    else
    {
        chara.moveLenghtPushed(-1);
    }

    if(chara.getLenghtPushed() <= 0)
    {
        chara.setIsPushed(false);
    }

    if(moveX > 0)
    {
        chara.setDirPlayer(RIGHT);
        if(tmpMoveX == 0)
        {
            tmpMoveX = 1;
        }
    }
    else
    {
        chara.setDirPlayer(LEFT);
        if(tmpMoveX == 0)
        {
            tmpMoveX = -1;
        }
    }

    moveChara(chara, tmpMoveX);
    chara.setDirPlayer(chara.getDirPlayer() == RIGHT ? LEFT : RIGHT);

    chara.setSkid(tmpMoveX);

}

void gamePlayedClass::setNoJump(characterClass& chara)
{
    chara.setSpeedJump(1.f * chara.getJumpPower());
    chara.setDistanceJump(0);
    for(int i = chara.getJumpPower(); i > 0; --i)
    {
        chara.moveDistanceJump(i);
    }
    chara.setInJump(false);
    falling(chara);
}

void gamePlayedClass::drawMessage(std::string message, float x, float y)
{
    sf::Text textMessage(message, globalClass::getFont(), 15);
    textMessage.setPosition(x, y);
    textMessage.setColor(sf::Color::Black);
    window->draw(textMessage);
}

gameStateStackClass* gamePlayedClass::getGameStateStack()
{
    return gameStateStack;
}

std::list<characterClass*>& gamePlayedClass::getListActiveEnemy()
{
    return listActiveEnemy;
}

std::map<std::pair<int, int>, itemClass*>& gamePlayedClass::getMapLevel()
{
    return mapLevel;
}

sf::View& gamePlayedClass::getCamera()
{
    return camera;
}

const levelClass& gamePlayedClass::getLevelClass()
{
    return level;
}

levelClass& gamePlayedClass::setLevelClass()
{
    return level;
}

const playerClass& gamePlayedClass::getPlayer()
{
    return player;
}

playerClass& gamePlayedClass::setPlayer()
{
    return player;
}

void gamePlayedClass::updatePlayer()
{
    player.update();
}
