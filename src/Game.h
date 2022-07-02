#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Player.h"

#include <iostream>
#include <vector>
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
    // sf::Event event;
    sf::VideoMode videoMode;
    sf::String windowTitle;

    Player *player;

    void initWindow();
    void initPlayer();

public:
    Game();
    virtual ~Game();

    void run();

    void updatePollEvents();
    void updateInput();
    void update();
    void render();
};