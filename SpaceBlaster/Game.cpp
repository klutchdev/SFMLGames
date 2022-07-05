#include "Game.h"
#include "Player.h"

//============= PRIVATE =================//
// Initialization
void Game::initWindow()
{
    std::cout << "Initializing window..." << std::endl;
    this->videoMode.width = WINDOW_WIDTH;
    this->videoMode.height = WINDOW_HEIGHT;
    this->windowTitle = WINDOW_TITLE;
    this->window = new sf::RenderWindow(this->videoMode, this->windowTitle);

    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false); // VSYNC
    std::cout << "√ Success" << std::endl;
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("src/bullet.png");
}

void Game::initGUI()
{
    if (!this->font.loadFromFile("src/press-start.ttf"))
        std::cout << "Error loading font" << std::endl;

    // Init points text
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(24);
    this->pointText.setFillColor(sf::Color::Yellow);
    this->pointText.setOutlineColor(sf::Color::Black);
    this->pointText.setOutlineThickness(4.f);
    this->pointText.setPosition(15.f, 15.f);
    this->pointText.setString("POINTS: ");

    // Game over text
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(36);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setPosition(
        this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    // Init player GUI
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(15.f, 50.f));

    this->playerHpBarBase = this->playerHpBar;
    this->playerHpBarBase.setFillColor(sf::Color(25, 25, 25, 200));
    this->playerHpBarBase.setOutlineColor(sf::Color::Black);
    this->playerHpBarBase.setOutlineThickness(4.f);
}

void Game::initWorld()
{
    if (!this->worldBackgroundTexture.loadFromFile("src/bg.png"))
        std::cout << "Error loading bg texture" << std::endl;

    this->worldBackground.setTexture(this->worldBackgroundTexture);
    this->worldBackground.scale(1.5f, 1.5f);
}

void Game::initSystems()
{
    this->points = 0;
}

void Game::initPlayer()
{
    this->player = new Player();

    // Initial position
    this->player->setPosition(sf::Vector2f(
        (this->window->getSize().x / 2) - this->player->getBounds().width / 2,
        this->window->getSize().y));
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

//============= CONSTRUCTOR =============//
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initGUI();
    this->initWorld();
    this->initSystems();
    this->initPlayer();
    this->initEnemies();
}

//============= DESTRUCTOR ==============//
Game::~Game()
{
    delete this->window;
    delete this->player;

    // Delete textures
    for (auto &texture : this->textures)
    {
        delete texture.second;
    }

    // Delete bullets
    for (auto *bullet : this->bullets)
    {
        delete bullet;
    }

    // Delete enemies
    for (auto *enemy : this->enemies)
    {
        delete enemy;
    }
}

//============= PUBLIC ==================//
void Game::run()
{

    while (this->window->isOpen())
    {
        this->updatePollEvents();

        if (this->player->getHp() > 0)
            this->update();

        this->render();
    }
}

void Game::updatePollEvents()
{

    sf::Event event;
    while (this->window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            std::cout << "\nQuitting..." << std::endl;
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                std::cout << "\nQuitting..." << std::endl;
                this->window->close();
            }
            break;

        default:
            break;
        }
    }
}

void Game::updateInput()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);

    // TODO: Make different bullet types
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
    {
        this->bullets.push_back(
            new Bullet(this->textures["BULLET"],
                       this->player->getPos().x,
                       this->player->getPos().y,
                       0.f,
                       -1.f,
                       15.f));

        // Doubles shots
        this->bullets.push_back(
            new Bullet(this->textures["BULLET"],
                       this->player->getPos().x + this->player->getBounds().width / 3.5f,
                       this->player->getPos().y,
                       0.f,
                       -1.f,
                       15.f));
    }
}

void Game::updateGUI()
{

    std::stringstream ss;

    ss << "POINTS: " << this->points;

    this->pointText.setString(ss.str());

    // Update player GUI
    float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
    if (this->player->getHp() <= 0)
        this->playerHpBar.setSize(sf::Vector2f(
            0.f,
            this->playerHpBar.getSize().y));
    else
        this->playerHpBar.setSize(sf::Vector2f(
            this->playerHpBarBase.getSize().x * hpPercent,
            this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
    // Left side world collision
    if (this->player->getBounds().left < 0.f)
        this->player->setPosition(
            sf::Vector2f(0.f,
                         this->player->getBounds().top));

    // Right side world collision
    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
        this->player->setPosition(
            sf::Vector2f(this->window->getSize().x - this->player->getBounds().width,
                         this->player->getBounds().top));

    // Top world collision
    if (this->player->getBounds().top < 0.f)
        this->player->setPosition(
            sf::Vector2f(this->player->getBounds().left,
                         0.f));

    // Bottom world collision
    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
        this->player->setPosition(
            sf::Vector2f(this->player->getBounds().left,
                         this->window->getSize().y - this->player->getBounds().height));
}

void Game::updateBullets()
{

    unsigned int counter = 0;
    for (auto *bullet : this->bullets)
    {
        bullet->update();

        // Bullet culling for top of the screen
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
            --counter;
        }

        ++counter;
    }
}

void Game::updateEnemies()
{

    // Spawning
    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
        this->spawnTimer = 0.0f;
    }

    // Update
    unsigned counter = 0;
    for (auto *enemy : this->enemies)
    {
        enemy->update();

        // Enemy culling for bottom of the screen
        if (enemy->getBounds().top > this->window->getSize().y)
        {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
            --counter;
        }

        // Enemy player collision
        else if (enemy->getBounds().intersects(this->player->getBounds()))
        {
            this->player->loseHp(this->enemies.at(counter)->getDamage());
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
            --counter;
        }

        ++counter;
    }
}

void Game::updateCombat()
{
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool enemy_deleted = false;
        for (int k = 0; k < this->bullets.size() && !enemy_deleted; k++)
        {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {

                this->points += this->enemies[i]->getPoints();

                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                enemy_deleted = true;
            }
        }
    }
}

void Game::update()
{

    this->updateInput();

    this->player->update();

    this->updateCollision();

    this->updateBullets();

    this->updateEnemies();

    this->updateCombat();

    this->updateGUI();

    this->updateWorld();
}

void Game::renderGUI()
{

    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBarBase);
    this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}

void Game::render()
{

    this->window->clear(sf::Color(27, 0, 49));

    // Draw world bg
    this->renderWorld();

    for (int i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i]->render(this->window);
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i]->render(this->window);
    }

    this->player->render(*this->window);

    // Draw GUI
    this->renderGUI();

    // Game over screen
    if (this->player->getHp() <= 0)
        this->window->draw(this->gameOverText);

    this->window->display();
}