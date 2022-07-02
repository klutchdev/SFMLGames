#include "Player.h"

//============= PRIVATE =================//
void Player::initTexture()
{
  if (!this->texture.loadFromFile("src/ship.png"))
    std::cout << "Could not load texture file" << std::endl;
}

void Player::initSprite()
{
  this->sprite.setTexture(this->texture); // Set the texture to the sprite
  this->sprite.setScale(0.125f, 0.125f);  // Resize the sprite
}

//============= CONSTRUCTOR =============//
Player::Player()
{
  this->movementSpeed = 2.5f;

  this->initTexture();
  this->initSprite();
}

//============= DESTRUCTOR ==============//
Player::~Player()
{
}

//============= PUBLIC ==================//
void Player::move(const float dirX, const float dirY)
{
  this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget &target)
{
  target.draw(this->sprite);
}