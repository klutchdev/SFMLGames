#include "Player.h"

void Player::initVariables()
{
}
void Player::initComponents()
{
    this->createMovementComponent(50.f, 5.f, 3.f);
}

Player::Player(float x, float y, sf::Texture &texture)
{
    this->initVariables();
    this->initComponents();
    this->setTexture(texture);
    this->setPosition(x, y);

    this->setScale(1.5f, 1.5f);
}

Player::~Player()
{
}