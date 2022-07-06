#include "Game.h"

//============= PRIVATE =================//
// Initializers
void Game::initVariables()
{
    std::cout << "Initializing values..." << std::endl;

    this->window = NULL;
    this->fullscreen = false;
    this->dt = 0.f;
    
    std::cout << "√ Success" << std::endl;
}

void Game::initWindow()
{

    std::cout << "Initializing window..." << std::endl;
    // Get SFML window options from window.ini file
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds(800, 600);
    bool fullscreen = false;
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
    std::cout << "√ Success" << std::endl;
}

void ::Game::initKeys()
{
    std::cout << "Initializing keys..." << std::endl;
    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
    std::cout << "√ Success" << std::endl;
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
    // this->states.push(new GameState(this->window, &this->supportedKeys));
}

//============= CONSTRUCTOR =============//
Game::Game()
{
    system("clear");
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

//============= DESTRUCTOR ==============//
Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//============= PUBLIC ==================//
void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(sfEvent))
    {
        switch (sfEvent.type)
        {
        case sf::Event::Closed:
            std::cout << "Quitting game..." << std::endl;
            this->window->close();
            break;

        default:
            break;
        }
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
        this->window->close();
}

void Game::render()
{
    this->window->clear();

    // Render
    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}