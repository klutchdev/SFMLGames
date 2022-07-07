#include "GameState.h"
#include "headers.h"

// ============= PRIVATE =================//

// Initializers
void GameState::initKeybinds()
{
    std::ifstream ifs("Config/gamestate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void GameState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/press-start.ttf"))
        std::cout << "Error loading font!" << std::endl;
}

void GameState::initTextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile("Sprites/Player/PLAYER_SHEET.png"))
        std::cout << "Error loading player idle texture" << std::endl;
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 800.f, "Quit");
}

//! Fix this
void GameState::initPlayers()
{
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

// ============= CONSTRUCTOR =============//
GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayers();
}

// ============= DESTRUCTOR ==============//
GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
}

// ============= PUBLIC ==================//
void GameState::updateInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
    {
        if (this->paused)
        {
            this->pauseState();
        }
        else
        {
            this->unpauseState();
        }
    }
}

void GameState::updatePlayerInput(const float &dt)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.0f, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);
}

void GameState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    if (!this->paused) // Unpaused update
    {
        this->updatePlayerInput(dt);

        this->player->update(dt);
    }
    else // Paused update
    {
        this->pmenu->update(this->mousePosView);
    }
}

void GameState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;

    this->player->render(*target);

    if (this->paused) // Pause menu render
    {
        this->pmenu->render(*target);
    }
}