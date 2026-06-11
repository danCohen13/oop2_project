#include "Player.h"
#include "Resources.h"

Player::Player()
    : MovingGameObject(Resources::getInstance().getTexture("player"), 300.0f),
    m_verticalVelocity(0.0f),
    m_isDead(false),
    m_flameSprite(Resources::getInstance().getTexture("Exhaust")),
    m_floorY(550.0f),
    m_playerAnimator(Resources::getInstance().getTexture("player"), 4),   // 4 frames
    m_flameAnimator(Resources::getInstance().getTexture("Exhaust"), 6)   // 6 frames
{
    m_sprite.setPosition({ 100.0f, 300.0f });

    // Première frame du joueur
    m_playerAnimator.applyTo(m_sprite);
    auto pSize = m_playerAnimator.getFrameSize();
    m_floorY = 600.0f - static_cast<float>(pSize.y) - 20.0f;

    // Première frame de la flamme + origine
    m_flameAnimator.applyTo(m_flameSprite);
    auto fSize = m_flameAnimator.getFrameSize();
    m_flameSprite.setOrigin({ fSize.x / 2.0f, 0.0f });
}

void Player::update(float deltaTime, bool isThrusting) {
    if (m_isDead) { m_drawFlame = false; return; }

    move(deltaTime);
    m_verticalVelocity += GRAVITY * deltaTime;

    m_drawFlame = isThrusting;
    if (isThrusting) m_verticalVelocity = JETPACK_FORCE;

    m_sprite.move({ 0.0f, m_verticalVelocity * deltaTime });

    // Limites écran
    sf::Vector2f pos = m_sprite.getPosition();
    if (pos.y >= m_floorY) {
        m_sprite.setPosition({ pos.x, m_floorY });
        m_verticalVelocity = 0.0f;
    }
    else if (pos.y <= CEILING_Y) {
        m_sprite.setPosition({ pos.x, CEILING_Y });
        m_verticalVelocity = 0.0f;
    }

    // Positionnement flamme
    if (m_drawFlame)
        m_flameSprite.setPosition({ pos.x + 20.0f, pos.y + 80.0f });

    // Animation — les deux animateurs tournent en synchrone
    bool frameChanged = m_playerAnimator.update(deltaTime);
    if (frameChanged) {
        m_playerAnimator.applyTo(m_sprite);
        if (m_drawFlame)
            m_flameAnimator.update(deltaTime); // avance aussi la flamme
    }
    if (m_drawFlame)
        m_flameAnimator.applyTo(m_flameSprite);
}

void Player::draw(sf::RenderWindow& window) const {
    if (m_drawFlame) {
        window.draw(m_flameSprite);
    }
    window.draw(m_sprite);
}

void Player::collide(Object& other) {
    other.collide(*this);
}

bool Player::isDead() const { return m_isDead; }
void Player::setDead(bool dead) { m_isDead = dead; }