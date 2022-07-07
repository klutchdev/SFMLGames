#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "headers.h"
#include "Button.h"

class PauseMenu
{
private:
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, Button *> buttons;

public:
    PauseMenu(sf::RenderWindow &window);
    virtual ~PauseMenu();

    void update();
    void render(sf::RenderTarget &target);
};

#endif