#pragma once

#include "MovementComponent.h"

class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    MovementComponent *movementComponent;

public:
    Entity();
    virtual ~Entity();

    void setTexture(sf::Texture &texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

    virtual void setPosition(const float x, const float y);
    virtual void setScale(const float x, const float y);
    virtual void move(const float x, const float y, const float &dt);

    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target);
};
