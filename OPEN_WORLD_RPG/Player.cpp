#include "Player.h"

void Player::initVariables()
{
}
void Player::initComponents()
{
}

Player::Player(float x, float y, sf::Texture *texture)
{
    this->initVariables();
    this->initComponents();
    this->createSprite(texture);
    this->setPosition(x, y);
    this->setScale(2.f, 2.f);
}

Player::~Player()
{
}