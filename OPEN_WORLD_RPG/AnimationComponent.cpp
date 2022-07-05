#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet)
{
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::update(const float &dt)
{
}