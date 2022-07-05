#include "Enemy.h"

//============= PRIVATE =================//
void Enemy::initVariables()
{
    this->pointCount = rand() % 8 + 3; // min = 3 | max = 10
    this->type = 0;
    this->hp = this->hpMax;
    this->hpMax = static_cast<int>(this->pointCount);
    this->damage = this->pointCount;
    this->points = this->pointCount;
    this->speed = static_cast<float>(this->pointCount / 3);
}

void Enemy::initShape()
{
    this->shape.setRadius(this->pointCount * 5);
    this->shape.setPointCount(this->pointCount);
    this->shape.setFillColor(
        sf::Color(
            rand() % 255 + 1,
            rand() % 255 + 1,
            rand() % 255 + 1,
            255));
}

//============= CONSTRUCTOR =============//
Enemy::Enemy(float pos_x, float pos_y)
{
    this->initVariables();
    this->initShape();

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

const int &Enemy::getPoints() const
{
    return this->points;
}

const int &Enemy::getDamage() const
{
    return this->damage;
}

void Enemy::update()
{
    this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}