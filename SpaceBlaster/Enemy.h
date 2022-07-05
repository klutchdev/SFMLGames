#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
    unsigned int pointCount;
    sf::CircleShape shape;
    int type;
    int hp;
    int hpMax;
    int damage;
    int points;
    float speed;

    void initVariables();
    void initShape();

public:
    Enemy(float pos_x, float pos_y);
    virtual ~Enemy();

    const sf::FloatRect getBounds() const;
    const int &getPoints() const;
    const int &getDamage() const;

    void update();
    void render(sf::RenderTarget *target);
};
