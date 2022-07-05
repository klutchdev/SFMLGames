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

enum movement_states
{
    IDLE = 0,
    MOVING,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

class MovementComponent
{
private:
    sf::Sprite &sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    // Initializer functions

public:
    MovementComponent(sf::Sprite &sprite,
                      float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    // Accessors
    const float &getMaxVelocity() const;
    const sf::Vector2f &getVelocity() const;

    // Functions
    const bool getState(const short unsigned state) const;
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();

    void move(const float x, const float y, const float &dt);
    void update(const float &dt);
};
