#include "MainMenuState.h"

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

    if (!this->backgroundTexture.loadFromFile("BG.jpg"))
    {
        throw("Failed to load BG texture");
    };

    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("press-start.ttf"))
        throw("Error loading font!");
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("mainmenustate_keybinds.ini");

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

    this->buttons["GAME_STATE"] = new Button(275, 150, 250, 75,
                                             &this->font,
                                             "NEW GAME",
                                             sf::Color(70, 70, 70, 200),
                                             sf::Color::Red,
                                             sf::Color(20, 20, 20, 200));

    this->buttons["SETTINGS_STATE"] = new Button(275, 250, 250, 75,
                                                 &this->font,
                                                 "SETTINGS",
                                                 sf::Color(100, 100, 100, 200),
                                                 sf::Color::Red,
                                                 sf::Color(20, 20, 20, 200));

    this->buttons["EXIT_STATE"] = new Button(275, 350, 250, 75,
                                             &this->font,
                                             "QUIT",
                                             sf::Color(100, 100, 100, 200),
                                             sf::Color::Red,
                                             sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    // this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    // this->background.setFillColor(sf::Color(21, 21, 21));
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it; it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MainMenuState::updateInput(const float &dt)
{
}

void MainMenuState::updateButtons()
{
    for (auto &it : this->buttons)
        it.second->update(this->mousePosView);

    if (this->buttons["GAME_STATE"]->isPressed())
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));

    if (this->buttons["EXIT_STATE"]->isPressed())
        this->endState();
}

void MainMenuState::update(const float &dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget *target)
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

    this->renderButtons(target);

    // sf::Text mouseText;
    // mouseText.setPosition(this->mousePosView);
    // mouseText.setFont(this->font);
    // mouseText.setCharacterSize(12);

    // std::stringstream ss;
    // ss << this->mousePosView.x << " " << this->mousePosView.y - 50;
    // mouseText.setString(ss.str());

    // target->draw(mouseText);
}