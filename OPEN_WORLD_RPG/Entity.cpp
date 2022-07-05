#include "Entity.h"

void Entity::initVariables()
{
    this->texture = NULL;
    this->sprite = NULL;
    this->movementSpeed = 5.f;
}

Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->sprite;
}

void Entity::createSprite(sf::Texture *texture)
{
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture);
    this->sprite->setTexture(*this->texture);
}

void Entity::setPosition(const float x, const float y)
{
    if (this->sprite)
        this->sprite->setPosition(x, y);
}

void Entity::setScale(const float x, const float y)
{
    this->sprite->setScale(x, y);
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
    if (this->sprite)
        this->sprite->move(dir_x * this->movementSpeed, dir_y * this->movementSpeed);
}

void Entity::update(const float &dt)
{
}

void Entity::render(sf::RenderTarget *target)
{
    if (this->sprite)
        target->draw(*this->sprite);
}