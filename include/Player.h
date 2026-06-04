#pragma once
#include "MovingGameObject.h"

class Player : public MovingGameObject {
public:
    Player();
    virtual ~Player() = default;

    // Gestion des mises à jour
    void update(float deltaTime, bool isThrusting);
    virtual void update(float deltaTime) override { update(deltaTime, false); }

    virtual void draw(sf::RenderWindow& window) const override;
    virtual void collide(Object& other) override;
    virtual void collide(Player&) override {}

    bool isDead() const;
    void setDead(bool dead);

private:
    float m_verticalVelocity;
    bool m_isDead;

    // Variables pour l'animation du personnage
    int m_currentFrame = 0;
    float m_frameTimer = 0.0f;
    const float FRAME_DURATION = 0.1f;

    // Variables pour la flamme du jetpack (SFML 3.0 demande une initialisation immédiate ou dans le constructeur)
    sf::Sprite m_flameSprite;
    bool m_drawFlame = false;

    // Physiques et limites de l'écran
    const float GRAVITY = 980.0f;
    const float JETPACK_FORCE = -600.0f;
    const float CEILING_Y = 50.0f;
    float m_floorY; // Déclaration de la variable pour le sol calculé dynamiquement
};