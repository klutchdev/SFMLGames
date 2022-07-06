#include "headers.h"
#include "Player.h"

// ============= PRIVATE ================= //
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

    this->createHitboxComponent(this->sprite, 0.f, 0.f, 192.f, 192.f);
    this->createMovementComponent(140.f, 1400.f, 1000.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);
    this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 11, 1, 64, 64);
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

void Player::updateAnimation(const float &dt)
{

    // if (this->movementComponent->getState(IDLE))
    //     this->animationComponent->play("IDLE", dt);
    // else if (this->movementComponent->getState(MOVING_LEFT))
    //     this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    // else if (this->movementComponent->getState(MOVING_DOWN))
    //     this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    // else if (this->movementComponent->getState(MOVING_RIGHT))
    //     this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    // else if (this->movementComponent->getState(MOVING_UP))
    //     this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
}

void Player::update(const float &dt)
{
    this->movementComponent->update(dt);

    if (this->movementComponent->getState(IDLE))
        this->animationComponent->play("IDLE", dt);

    else if (this->movementComponent->getState(MOVING_LEFT))
        this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    // this->updateAnimation(dt);
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}