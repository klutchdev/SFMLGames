#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <sstream>
#include <fstream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

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

    // GUI
    sf::Font font;
    sf::Text pointText;
    sf::Text gameOverText;

    // World
    sf::Texture worldBackgroundTexture;
    sf::Sprite worldBackground;

    // Systems
    unsigned int points;

    // Player
    Player *player;

    // Player GUI
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBase;

    // Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy *> enemies;

    void initWindow();
    void initTextures();
    void initGUI();
    void initWorld();
    void initSystems();

    void initPlayer();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    void run();

    void updatePollEvents();
    void updateInput();
    void updateGUI();
    void updateWorld();
    void updateCollision();
    void updateBullets();
    void updateEnemies();
    void updateCombat();
    void update();

    void renderGUI();
    void renderWorld();
    void render();
};