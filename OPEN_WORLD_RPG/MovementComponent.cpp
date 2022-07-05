#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite &sprite,
                                     float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f &MovementComponent::getVelocity() const
{
    return this->velocity;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->deceleration * dir_y;
}

void MovementComponent::update(const float &dt)
{
    this->sprite.move(this->velocity * dt); // Uses velocity
}