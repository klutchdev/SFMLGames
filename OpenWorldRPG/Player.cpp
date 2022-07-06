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
    this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
    this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
}

// ============= CONSTRUCTOR =============//
Player::Player(float x, float y, sf::Texture &texture_sheet)
{
    this->initVariables();

    this->createMovementComponent(140.f, 1400.f, 1000.f);
    this->createAnimationComponent(texture_sheet);

    this->setPosition(x, y);
    this->initAnimations();
}

// ============= DESTRUCTOR ==============//
Player::~Player()
{
}

// ============= PUBLIC ==================//
// Accessors
// AttributeComponent *Player::getAttributeComponent()
// {
//     return this->attributeComponent;
// }

void Player::updateAnimation(const float &dt)
{

    if (this->movementComponent->getState(IDLE))
        this->animationComponent->play("IDLE", dt);

    else if (this->movementComponent->getState(MOVING_DOWN))
        this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    else if (this->movementComponent->getState(MOVING_LEFT))
        this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    else if (this->movementComponent->getState(MOVING_RIGHT))
        this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    else if (this->movementComponent->getState(MOVING_UP))
        this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
}

void Player::update(const float &dt)
{
    this->movementComponent->update(dt);
    this->updateAnimation(dt);
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}