#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{
private:
protected:
    std::stack<State *> *states;
    sf::RenderWindow *window;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keybinds;

    bool quit;
    bool paused;

    float keytime;
    float keytimeMax;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Resources
    std::map<std::string, sf::Texture> textures;

    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~State();

    // Accessors
    const bool &getQuit() const;
    const bool getKeytime();

    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePositions();
    virtual void updateKeytime(const float &dt);
    virtual void updateInput(const float &dt) = 0;
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = NULL) = 0;
};

#endif