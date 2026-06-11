#pragma once
#include "MovingGameObject.h"
#include <memory>

class PlayerState; // Forward declaration

class Player : public MovingGameObject {
public:
    enum class MovementType { Walking, Jumping };

    Player();
    virtual ~Player() = default;

    void update(float deltaTime, bool isThrusting);
    virtual void update(float deltaTime) override { update(deltaTime, false); }

    virtual void draw(sf::RenderWindow& window) const override;
    virtual void collide(Object& other) override;
    virtual void collide(Player&) override {}

    bool isDead() const;
    void setDead(bool dead);
    bool isThrusting() const;

    // Getters publics pour permettre aux États de modifier les composants graphiques
    sf::Sprite& getSprite() { return m_sprite; }
    sf::Sprite& getFlameSprite() { return m_flameSprite; }

private:
    float m_verticalVelocity;
    bool m_isDead;
    bool m_isThrusting;

    sf::Sprite m_flameSprite;

    // Infrastructure de la Machine d'États Aplatie
    std::unique_ptr<PlayerState> m_state;
    MovementType m_currentMovement;

    const float GRAVITY = 980.0f;
    const float JETPACK_FORCE = -600.0f;
    const float CEILING_Y = 50.0f;
    float m_floorY;
};