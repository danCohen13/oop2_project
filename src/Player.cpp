#include "Player.h"

Player::Player()
    : MovingGameObject(300.0f), // Standard horizontal speed configuration
    m_verticalVelocity(0.0f),
    m_isDead(false) {
    // Sprite and texture loading bindings will be handled here via Resources management
}

void Player::update(float deltaTime) {
    if (m_isDead) return;

    // Constant autonomous forward movement along the X axis
    move(deltaTime);

    // Apply continuous gravitational pull
    m_verticalVelocity += GRAVITY * deltaTime;

    // Read hardware input directly (Hybrid architecture)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_verticalVelocity = JETPACK_FORCE;
    }

    // Apply computed vertical velocity translation to the SFML sprite
    m_sprite.move({ 0.0f, m_verticalVelocity * deltaTime });

    // Mathematical window boundary clamping
    sf::Vector2f position = m_sprite.getPosition();
    if (position.y >= FLOOR_Y) {
        m_sprite.setPosition({ position.x, FLOOR_Y });
        m_verticalVelocity = 0.0f;
    }
    else if (position.y <= CEILING_Y) {
        m_sprite.setPosition({ position.x, CEILING_Y });
        m_verticalVelocity = 0.0f;
    }
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

bool Player::isDead() const {
    return m_isDead;
}

void Player::setDead(bool dead) {
    m_isDead = dead;
}