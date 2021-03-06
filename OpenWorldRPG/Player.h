#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
    bool attacking;

    // Initializers
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture &texture_sheet);
    virtual ~Player();

    // Accessors
    void updateAttack();
    void updateAnimation(const float &dt);
    virtual void update(const float &dt);

    void render(sf::RenderTarget &target);
};

#endif