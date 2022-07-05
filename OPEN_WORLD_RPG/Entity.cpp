#include "Entity.h"

void Entity::initVariables()
{

    this->movementComponent = NULL;
}

Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
}

void Entity::setTexture(sf::Texture &texture)
{
    this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity);
}

void Entity::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Entity::setScale(const float x, const float y)
{
    this->sprite.setScale(x, y);
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
    if (this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
    }
}

void Entity::update(const float &dt)
{
}

void Entity::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}