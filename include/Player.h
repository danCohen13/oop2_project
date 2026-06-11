#pragma once
#include "MovingGameObject.h"
#include "SpriteAnimator.h"   // ← nouveau

class Player : public MovingGameObject {
public:
    Player();
    virtual ~Player() = default;

    void update(float deltaTime, bool isThrusting);
    virtual void update(float deltaTime) override { update(deltaTime, false); }
    virtual void draw(sf::RenderWindow& window) const override;
    virtual void collide(Object& other) override;
    virtual void collide(Player&) override {}

    bool isDead() const;
    void setDead(bool dead);

private:
    float m_verticalVelocity;
    bool  m_isDead;

    sf::Sprite      m_flameSprite;
    bool            m_drawFlame = false;

    SpriteAnimator  m_playerAnimator;  // ← remplace m_currentFrame/m_frameTimer/FRAME_DURATION
    SpriteAnimator  m_flameAnimator;   // ← idem pour la flamme

    const float GRAVITY = 980.0f;
    const float JETPACK_FORCE = -600.0f;
    const float CEILING_Y = 50.0f;
    float       m_floorY;
};