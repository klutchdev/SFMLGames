#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;

public:
    Entity();
    virtual ~Entity();

    // Component functions
    void setTexture(sf::Texture &texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
    void createAnimationComponent(sf::Texture &texture_sheet);

    // Accessors
    virtual MovementComponent *getMovementComponent();
    virtual AnimationComponent *getAnimationComponent();

    virtual const sf::Vector2f &getPosition() const;
    virtual const sf::Vector2f &getSpritePosition() const;
    virtual const sf::Vector2f getCenter() const;
    virtual const sf::Vector2f getSpriteCenter() const;
    virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
    virtual const sf::FloatRect getGlobalBounds() const;
    virtual const sf::FloatRect getNextPositionBounds(const float &dt) const;

    // Modifiers
    virtual void setPosition(const float x, const float y);

    // Functions
    virtual void move(const float x, const float y, const float &dt);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    // Calculations
    virtual const float getDistance(const Entity &entity) const;
    virtual const float getSpriteDistance(const Entity &entity) const;

    virtual void update(const float &dt, sf::Vector2f &mouse_pos_view, const sf::View &view) = 0;
    virtual void render(sf::RenderTarget &target) = 0;
};
