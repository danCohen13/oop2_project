#pragma once
#include "MovingGameObject.h"

class Player : public MovingGameObject {
public:
    Player();
    virtual ~Player() = default;

    // Handles the fixed 2-argument call passed by the board loop
    void update(float deltaTime, bool isThrusting);
    virtual void update(float deltaTime) override { update(deltaTime, false); }

    virtual void draw(sf::RenderWindow& window) const override;
    virtual void collide(Object& other) override;
    virtual void collide(Player& player) override {}

    bool isDead() const;
    void setDead(bool dead);

private:
    float m_verticalVelocity;
    bool m_isDead;

    const float GRAVITY = 980.0f;
    const float JETPACK_FORCE = -600.0f;
    const float FLOOR_Y = 550.0f;
    const float CEILING_Y = 50.0f;
};