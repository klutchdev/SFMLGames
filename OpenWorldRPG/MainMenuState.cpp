#include "headers.h"
#include "MainMenuState.h"

// ============= PRIVATE =================//
// Initializers
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
    this->background.setSize(
        sf::Vector2f(
            static_cast<float>(this->window->getSize().x),
            static_cast<float>(this->window->getSize().y)));

    if (!this->backgroundTexture.loadFromFile("Textures/BG_2.png"))
    {
        throw("Failed to load BG texture");
    };

    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/press-start.ttf"))
        std::cout << "Error loading font!" << std::endl;
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{

    this->buttons["GAME_STATE"] = new Button(275.f, 225.f,                  // Position x, y
                                             250.f, 75.f,                   // Width, height
                                             &this->font,                   // font
                                             "NEW GAME", 30,                // Label, font size
                                             sf::Color(200, 200, 200, 200), // Text idle color
                                             sf::Color::Magenta,            // Text hover color
                                             sf::Color(13, 13, 13, 250),    // Text active color
                                             sf::Color(40, 40, 40, 0),      // Button idle color
                                             sf::Color(20, 20, 20, 0),      // Button hover color
                                             sf::Color(244, 0, 255, 150));  // Button active color

    this->buttons["SETTINGS_STATE"] = new Button(275.f, 300.f,                  // Position x, y
                                                 250.f, 75.f,                   // Width, height
                                                 &this->font,                   // Font
                                                 "SETTINGS", 28,                // Label, font size
                                                 sf::Color(200, 200, 200, 200), // Text idle color
                                                 sf::Color::Magenta,            // Text hover color
                                                 sf::Color(13, 13, 13, 250),    // Text active color
                                                 sf::Color(40, 40, 40, 0),      // Button idle color
                                                 sf::Color(20, 20, 20, 0),      // Button hover color
                                                 sf::Color(244, 0, 255, 150));  // Button active color

    this->buttons["EDITOR_STATE"] = new Button(275.f, 375.f,                  // Position x, y
                                               250.f, 75.f,                   // Width, height
                                               &this->font,                   // Font
                                               "EDITOR", 28,                  // Label, font size
                                               sf::Color(200, 200, 200, 200), // Text idle color
                                               sf::Color::Magenta,            // Text hover color
                                               sf::Color(13, 13, 13, 250),    // Text active color
                                               sf::Color(40, 40, 40, 0),      // Button idle color
                                               sf::Color(20, 20, 20, 0),      // Button hover color
                                               sf::Color(244, 0, 255, 150));  // Button active color

    this->buttons["EXIT_STATE"] = new Button(275.f, 450.f,                  // Position x, y
                                             250.f, 75.f,                   // Width, height
                                             &this->font,                   // Font
                                             "QUIT", 28,                    // Label, font size
                                             sf::Color(200, 200, 200, 200), // Text idle color
                                             sf::Color::Magenta,            // Text hover color
                                             sf::Color(13, 13, 13, 250),    // Text active color
                                             sf::Color(40, 40, 40, 0),      // Button idle color
                                             sf::Color(20, 20, 20, 0),      // Button hover color
                                             sf::Color(244, 0, 255, 150));  // Button active color
}

// ============= CONSTRUCTOR =============//
MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

// ============= DESTRUCTOR ==============//
MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it; it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

// ============= PUBLIC ==================//
void MainMenuState::updateInput(const float &dt)
{
}

void MainMenuState::updateButtons()
{
    for (auto &it : this->buttons)
        it.second->update(this->mousePosView);

    if (this->buttons["GAME_STATE"]->isPressed())
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));

    // if (this->buttons["SETTINGS_STATE"]->isPressed())
    // this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    // std::cout << "Settings" << std::endl;

    if (this->buttons["EDITOR_STATE"]->isPressed())
        this->states->push(new EditorState(this->window, this->supportedKeys, this->states));

    if (this->buttons["EXIT_STATE"]->isPressed())
        this->endState();
}

void MainMenuState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget &target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderButtons(*target);
}