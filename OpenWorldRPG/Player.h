#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
    void initVariables();
    void initComponents();
    void initAnimations();

public:
    Player(float x, float y, sf::Texture &texture_sheet);
    virtual ~Player();

    // Accessors
    void updateAnimation(const float &dt);
    void update(const float &dt);

    void render(sf::RenderTarget &target);
};

#endif