#include "Player.h"

//============= PRIVATE =================//
void Player::initVariables()
{
}

void Player::initComponents()
{
}

//============= CONSTRUCTOR =============//
Player::Player(float x, float y, sf::Texture &texture_sheet)
{
    this->initVariables();

    this->setPosition(x, y);
    // this->setScale(1.25f, 1.25f); // Scales the player

    this->createMovementComponent(300.f, 1400.f, 1000.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE",
                                           //    this->sprite, texture_sheet,
                                           10.f,    // Animation timer
                                           0, 0,    // Start frame x, y
                                           8, 0,    // Frames x, y
                                           64, 64); // Width, height
}

//============= DESTRUCTOR ==============//
Player::~Player()
{
}

//============= PUBLIC ==================//
void Player::update(const float &dt)
{
    this->movementComponent->update(dt);

    this->animationComponent->play("IDLE", dt);
}