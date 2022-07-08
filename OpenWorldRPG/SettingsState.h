#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Button.h"

class SettingsState : public State
{
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button *> buttons;

    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~SettingsState();

    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);

    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = NULL);
};

#endif