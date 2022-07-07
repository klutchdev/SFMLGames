#include "headers.h"
#include "GameState.h"

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

void GameState::initTextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile("Sprites/Player/PLAYER_SHEET.png"))
        std::cout << "Error loading player idle texture" << std::endl;
}

//! TODO: Fix this
void GameState::initPlayers()
{
    // this->player = new Player(220.f, 220.f, this->textures["PLAYER_SHEET"]);
}

// ============= CONSTRUCTOR =============//
GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}

// ============= DESTRUCTOR ==============//
GameState::~GameState()
{
    delete this->player;
}

// ============= PUBLIC ==================//
void GameState::updateInput(const float &dt)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.0f, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->endState();
}

void GameState::update(const float &dt)
{
    this->updateMousePositions();

    this->updateInput(dt);

    this->player->update(dt);
}

void GameState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;

    this->player->render(*target);
}