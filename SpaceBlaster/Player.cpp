#include "Player.h"

//============= PRIVATE =================//
void Player::initVariables()
{
    this->movementSpeed = 5.f;
    this->attackCooldownMax = 5.f;
    this->attackCooldown = this->attackCooldownMax;

    this->hpMax = 100;
    this->hp = this->hpMax;
}

void Player::initTexture()
{
    if (!this->texture.loadFromFile("Sprites/Player/ship.png"))
        std::cout << "Could not load texture file" << std::endl;
}

void Player::initSprite()
{
    this->sprite.setTexture(this->texture); // Set the texture to the sprite
    this->sprite.setScale(0.25f, 0.25f);    // Resize the sprite
}

//============= CONSTRUCTOR =============//
Player::Player()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

//============= DESTRUCTOR ==============//
Player::~Player()
{
}

//============= PUBLIC ==================//
const sf::Vector2f &Player::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int &Player::getHp() const
{
    return this->hp;
}

const int &Player::getHpMax() const
{
    return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Player::setHp(const int hp)
{
    this->hp = hp;
}

void Player::loseHp(const int value)
{
    this->hp -= value;
}

void Player::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
    if (this->attackCooldown >= this->attackCooldownMax)
    {
        this->attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack()
{
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}

void Player::update()
{
    this->updateAttack();
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}