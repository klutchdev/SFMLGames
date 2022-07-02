#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

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

    // Player
    Player *player;

    // Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy *> enemies;

    // GUI
    sf::Font font;
    sf::Text pointText;

    void initWindow();
    void initTextures();
    void initGUI();

    void initPlayer();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    void run();

    void updatePollEvents();
    void updateInput();
    void updateGUI();
    void updateBullets();
    void updateEnemies();
    void updateCombat();
    void update();

    void renderGUI();
    void render();
};