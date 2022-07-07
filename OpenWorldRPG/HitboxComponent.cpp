#include "headers.h"
#include "HitboxComponent.h"

// ============= CONSTRUCTOR =================//
HitboxComponent::HitboxComponent(
    sf::Sprite &sprite,
    float offset_x, float offset_y,
    float width, float height)
    : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    this->hitbox.setPosition(
        this->sprite.getPosition().x + offset_x,
        this->sprite.getPosition().y + offset_y);
    this->hitbox.setSize(sf::Vector2f(width, height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Yellow);
}

// ============= DESTRUCTOR =================//
HitboxComponent::~HitboxComponent()
{
}

// ============= PUBLIC =================//
// Accessors
bool HitboxComponent::checkIntersect(const sf::FloatRect &fRect)
{
    return this->hitbox.getGlobalBounds().intersects(fRect);
}

void HitboxComponent::update()
{
    this->hitbox.setPosition(
        this->sprite.getPosition().x + this->offsetX,
        this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget &target)
{
    target.draw(this->hitbox);
}
