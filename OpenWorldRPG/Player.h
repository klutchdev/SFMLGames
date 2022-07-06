#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
    void initVariables();
    void initComponents();
    void initAnimations();

public:
    Player(float x, float y, sf::Texture &texture);
    virtual ~Player();

    void updateAnimation(const float &dt);

    void update(const float &dt);
};
