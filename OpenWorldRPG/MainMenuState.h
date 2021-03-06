#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Button.h"

class MainMenuState : public State
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
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~MainMenuState();

    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);

    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = NULL);
};

#endif