#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "Video Game"

class Game
{
private:
    // Window
    sf::RenderWindow *window;
    sf::Event event;
    sf::VideoMode videoMode;
    sf::String windowTitle;

    // Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Resources
    sf::Font font;

    // Text
    sf::Text uiText;

    // Game logic
    bool endGame;
    bool mouseHeld;

    int health;
    int shots;
    int maxEnemies;

    unsigned points;
    unsigned enemiesDestroyed;

    float accuracy;
    float enemySpawnTimer;
    float enemySpawnTimerMax;

    std::string lastScore;

    // Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

private:
    void createSaveFile();
    void loadSaveFile();
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    // Accessors
    const bool running() const;
    const bool getEndGame() const;

    // Functions
    void spawnEnemy();
    void showGameLog();

    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget &target);
    void renderEnemies(sf::RenderTarget &target);
    void render();
};
