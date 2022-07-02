#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
    sf::CircleShape shape;
    int type;
    int hp;
    int hpMax;
    int damage;
    int points;
    float speed;

    void initShape();
    void initVariables();

public:
    Enemy(float pos_x, float pos_y);
    virtual ~Enemy();

    const sf::FloatRect getBounds() const;
    void update();
    void render(sf::RenderTarget *target);
};
