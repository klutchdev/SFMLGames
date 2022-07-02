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

void Game::initPlayer()
{
    this->player = new Player();
}

//============= CONSTRUCTOR =============//
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initPlayer();
}

//============= DESTRUCTOR ==============//
Game::~Game()
{
    delete this->window;
    delete this->player;

    // Delete textures
    for (auto &i : this->textures)
    {
        delete i.second;
    }

    // Delete bullets
    for (auto *i : this->bullets)
    {
        delete i;
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
    {
        this->bullets.push_back(
            new Bullet(
                this->textures["BULLET"],
                this->player->getPos().x,
                this->player->getPos().y,
                0.f,
                -1.f,
                15.f));
    }
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
}

void Game::render()
{
    /**
        @return void

        - Clears the frame
        - Displays the new frame
    */

    this->window->clear();

    for (auto *bullet : this->bullets)
    {
        bullet->render(this->window);
    }
    this->player->render(*this->window);

    this->window->display();
}