#include "Player.h"
#include "Resources.h"

Player::Player()
    : MovingGameObject(Resources::getInstance().getTexture("player"), 300.0f),
    m_verticalVelocity(0.0f),
    m_isDead(false) {
    m_sprite.setPosition({ 100.0f, 300.0f });
}

void Player::update(float deltaTime, bool isThrusting) {
    if (m_isDead) return;

    move(deltaTime);
    m_verticalVelocity += GRAVITY * deltaTime;

    if (isThrusting) {
        m_verticalVelocity = JETPACK_FORCE;
    }

    m_sprite.move({ 0.0f, m_verticalVelocity * deltaTime });

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

void Player::collide(Object& other) {
    other.collide(*this);
}

bool Player::isDead() const { return m_isDead; }
void Player::setDead(bool dead) { m_isDead = dead; }