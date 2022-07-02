#include "Enemy.h"

//============= PRIVATE =================//
void Enemy::initShape()
{
    this->shape.setRadius(rand() % 20 + 20);
    this->shape.setPointCount(rand() % 10 + 3);
    this->shape.setFillColor(
        sf::Color(
            rand() % 255 + 1,
            rand() % 255 + 1,
            rand() % 255 + 1));
}

void Enemy::initVariables()
{
    this->type = 0;
    this->hp = 10;
    this->hpMax = 0;
    this->damage = 1;
    this->points = 5;
    this->speed = 5.f;
}

//============= CONSTRUCTOR =============//
Enemy::Enemy(float pos_x, float pos_y)
{
    this->initShape();
    this->initVariables();

    this->shape.setPosition(pos_x, pos_y);
}

//============= DESTRUCTOR ==============//
Enemy::~Enemy()
{
}

//============= PUBLIC ==================//
const sf::FloatRect Enemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}

void Enemy::update()
{
    this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}