#include "headers.h"
#include "Player.h"

// ============= PRIVATE ================= //
// Initializers
void Player::initVariables()
{
}

void Player::initComponents()
{
}

void Player::initAnimations()
{
}

// ============= CONSTRUCTOR =============//
Player::Player(float x, float y, sf::Texture &texture_sheet)
{
    this->initVariables();

    this->createHitboxComponent(this->sprite, 86.f, 74.f, 86.f, 111.f);
    this->createMovementComponent(300.f, 15.f, 15.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 13, 0, 192, 192);
    this->animationComponent->addAnimation("WALK", 6.f, 0, 1, 11, 1, 192, 192);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
    // this->animationComponent->addAnimation("WALK_LEFT", 8.f, 0, 1, 11, 1, 192, 192);
    // this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
    // this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
    // this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);

    this->setPosition(x, y);
    this->initAnimations();
}

// ============= DESTRUCTOR ==============//
Player::~Player()
{
}

// ============= PUBLIC ==================//

void Player::update(const float &dt)
{
    this->movementComponent->update(dt);

    if (this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", dt);
    }

    else if (this->movementComponent->getState(MOVING_LEFT))
    {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }

    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        this->sprite.setOrigin(258.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }

    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }

    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }

    this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}