#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture *texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
    this->shape.setTexture(*texture);
    this->shape.setPosition(pos_x, pos_y);
    // this->shape.setScale(0.9f, 0.9f);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
    return this->shape.getGlobalBounds();
}

void Bullet::update()
{
    this->shape.move(this->movementSpeed * this->direction); // Movement
}

void Bullet::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}