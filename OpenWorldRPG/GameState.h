#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "headers.h"
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"

class GameState : public State
{
private:
    PauseMenu pmenu;

    Player *player;
    sf::Texture texture;

    void initKeybinds();
    void initTextures();
    void initPlayers();

public:
    GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~GameState();

    void updateInput(const float &dt);
    void update(const float &dt);

    void render(sf::RenderTarget *target = NULL);
};

#endif