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

    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(16);
    this->pointText.setFillColor(sf::Color::White);
    this->pointText.setString("Points: ");
}

void Game::initPlayer()
{
    this->player = new Player();
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
    /**
        @return void

        - Runs the game
    */

    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}

void Game::updatePollEvents()
{
    /**
        @return void

        - Handles events
    */

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
    /**
        @return void

        - Update player input
    */

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
                       this->player->getPos().x - 2.f,
                       this->player->getPos().y,
                       0.f,
                       -1.f,
                       15.f));
        // Doubles shots
        this->bullets.push_back(
            new Bullet(this->textures["BULLET"],
                       this->player->getPos().x + 20.f,
                       this->player->getPos().y,
                       0.f,
                       -1.f,
                       15.f));
    }
}

void Game::updateGUI()
{
    /**
        @return void

        - Updates the GUI
    */
}

void Game::updateBullets()
{
    /**
        @return void

        - Update bullets
    */

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
    /**
        @return void

        - Update enemies
    */

    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
        this->spawnTimer = 0.0f;
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool enemyRemoved = false;
        this->enemies[i]->update();

        for (int k = 0; k < this->bullets.size() && !enemyRemoved; k++)
        {
            if (this->bullets[i]->getBounds().intersects(this->enemies[i]->getBounds()))
            {
                this->bullets.erase(this->bullets.begin() + k);
                this->enemies.erase(this->enemies.begin() + i);
                enemyRemoved = true;
            }
        }

        // Remove enemy at the bottom of the screen
        if (!enemyRemoved)
            if (this->enemies[i]->getBounds().top > this->window->getSize().y)
            {
                this->enemies.erase(this->enemies.begin() + i);
                enemyRemoved = true;
            }
    }
}

void Game::updateCombat()
{
}

void Game::update()
{
    /**
        @return void

        - Updates the game
    */

    this->updatePollEvents();

    this->updateInput();

    this->player->update();

    this->updateBullets();

    this->updateEnemiesAndCombat();

    this->updateGUI();
}

void Game::renderGUI()
{
    /**
        @return void

        - Renders the GUI
    */

    this->window->draw(this->pointText);
}

void Game::render()
{
    /**
        @return void

        - Clears the frame
        - Displays the new frame
    */

    this->window->clear();

    for (int i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i]->render(this->window);
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i]->render(this->window);
    }

    this->player->render(*this->window);

    this->window->display();
}