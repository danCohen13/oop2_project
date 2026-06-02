#pragma once
#include "MovingGameObject.h"

class Player : public MovingGameObject {
public:
    Player();
    virtual ~Player() = default;

    // Updates player physics, handling gravity, inputs, and boundaries
    virtual void update(float deltaTime) override;

    // Renders the player sprite to the screen
    virtual void draw(sf::RenderWindow& window) const override;

    bool isDead() const;
    void setDead(bool dead);

private:
    float m_verticalVelocity;
    bool m_isDead;

    // Gameplay physics constants
    const float GRAVITY = 980.0f;
    const float JETPACK_FORCE = -600.0f;
    const float FLOOR_Y = 550.0f;
    const float CEILING_Y = 50.0f;
};