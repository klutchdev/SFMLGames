#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Entity
{
private:
    void initVariables();

protected:
    sf::Texture *texture;
    sf::Sprite *sprite;

    float movementSpeed;

public:
    Entity();
    virtual ~Entity();

    void createSprite(sf::Texture *texture);

    virtual void setPosition(const float x, const float y);
    virtual void setScale(const float x, const float y);
    virtual void move(const float &dt, const float x, const float y);

    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);
};
