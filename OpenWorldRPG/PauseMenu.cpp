#include "PauseMenu.h"

// ============= PRIVATE =================//

// ============= CONSTRUCTOR =================//
PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font)
    : font(font)
{
    // Init background
    this->background.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)));
    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    // Init container
    this->container.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / 4.f,
            static_cast<float>(window.getSize().y) - 100.f));
    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(
        static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
        30.f);

    // Init text
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(30);
    this->menuText.setString("Paused");
    this->menuText.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 40.f);
}

// ============= DESTRUCTOR =================//
PauseMenu::~PauseMenu()
{
    auto it = this->buttons.begin();
    for (it; it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

// ============= PUBLIC ==================//

std::map<std::string, Button *> &PauseMenu::getButtons()
{
    return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
    float width = 250.f;
    float height = 50.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new Button(x, y,                          // Position x, y
                                    width, height,                 // Width, height
                                    &this->font,                   // font
                                    text, 30,                      // Label, font size
                                    sf::Color(200, 200, 200, 200), // Text idle color
                                    sf::Color::Magenta,            // Text hover color
                                    sf::Color(13, 13, 13, 250),    // Text active color
                                    sf::Color(40, 40, 40, 0),      // Button idle color
                                    sf::Color(20, 20, 20, 0),      // Button hover color
                                    sf::Color(244, 0, 255, 150));  // Button active color
}

void PauseMenu::update(const sf::Vector2f &mousePos)
{
    for (auto &i : this->buttons)
    {
        i.second->update(mousePos);
    }
}

void PauseMenu::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);

    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }
}