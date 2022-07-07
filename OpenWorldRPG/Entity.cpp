#include "headers.h"
#include "Entity.h"

// ============= PRIVATE =================//
void Entity::initVariables()
{
    this->hitboxComponent = NULL;
    this->movementComponent = NULL;
    this->animationComponent = NULL;
}

// ============= CONSTRUCTOR =============//
Entity::Entity()
{
    this->initVariables();
}

// ============= CONSTRUCTOR =============//
Entity::~Entity()
{
    delete this->hitboxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
}

// ============= PUBLIC ==================//
// Component functions
void Entity::setTexture(sf::Texture &texture)
{
    this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height)
{
    this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

MovementComponent *Entity::getMovementComponent()
{
    return this->movementComponent;
}

AnimationComponent *Entity::getAnimationComponent()
{
    return this->animationComponent;
}

// Accessors
const sf::Vector2f &Entity::getPosition() const
{
    return this->sprite.getPosition();
}

const sf::Vector2f &Entity::getSpritePosition() const
{
    return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
    return this->sprite.getPosition() +
           sf::Vector2f(
               this->sprite.getGlobalBounds().width / 2.f,
               this->sprite.getGlobalBounds().height / 2.f);
}

const sf::Vector2f Entity::getSpriteCenter() const
{
    return this->sprite.getPosition() +
           sf::Vector2f(
               this->sprite.getGlobalBounds().width / 2.f,
               this->sprite.getGlobalBounds().height / 2.f);
    ;
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
    return sf::Vector2i(
        static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
        static_cast<int>(this->sprite.getPosition().y) / gridSizeI);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float &dt) const
{
    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

// Functions
void Entity::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float &dt)
{
    if (this->movementComponent)
        this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
}

void Entity::stopVelocity()
{
    if (this->movementComponent)
        this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
    if (this->movementComponent)
        this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
    if (this->movementComponent)
        this->movementComponent->stopVelocityY();
}

void Entity::update(const float &dt, sf::Vector2f &mouse_pos_view, const sf::View &view)
{
}

void Entity::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);

    if (this->hitboxComponent)
        this->hitboxComponent->render(target);
}

const float Entity::getDistance(const Entity &entity) const
{
    return sqrt(pow(this->getCenter().x - entity.getCenter().x, 2) + pow(this->getCenter().y - entity.getCenter().y, 2));
}

const float Entity::getSpriteDistance(const Entity &entity) const
{
    return sqrt(pow(this->getSpriteCenter().x - entity.getSpriteCenter().x, 2) + pow(this->getSpriteCenter().y - entity.getSpriteCenter().y, 2));
}