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

class MovementComponent
{
private:
    sf::Sprite &sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

public:
    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    const sf::Vector2f &getVelocity() const;

    void move(const float dir_x, const float dir_y, const float &dt);
    void update(const float &dt);
};
