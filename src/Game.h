#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "Bullet.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <sstream>
#include <fstream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1000
#define WINDOW_TITLE "Video Game"

class Game
{
private:
    // Window
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::String windowTitle;

    // Resources
    std::map<std::string, sf::Texture *> textures;
    std::vector<Bullet *> bullets;

    Player *player;

    void initWindow();
    void initTextures();

    void initPlayer();

public:
    Game();
    virtual ~Game();

    void run();

    void updatePollEvents();
    void updateInput();
    void updateBullets();
    void update();
    void render();
};