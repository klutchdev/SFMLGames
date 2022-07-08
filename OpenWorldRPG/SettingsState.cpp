#include "SettingsState.h"

// ============= PRIVATE =================//
void SettingsState::initVariables()
{
}

void SettingsState::initBackground()
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

void SettingsState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/press-start.ttf"))
        std::cout << "Error loading font!" << std::endl;
}

void SettingsState::initKeybinds()
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

void SettingsState::initButtons()
{

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

// ============= CONSTRUCTOR =================//
SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
}

// ============= DESTRUCTOR =================//
SettingsState::~SettingsState()
{
}

// ============= PUBLIC =================//

// Accessors

// Functions
void SettingsState::updateInput(const float &dt)
{
}

void SettingsState::updateButtons()
{
    for (auto &it : this->buttons)
        it.second->update(this->mousePosView);

    if (this->buttons["EXIT_STATE"]->isPressed())
        this->endState();
}

void SettingsState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget &target)
{
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderButtons(*target);
}