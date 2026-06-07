#include "Laser.h"
#include "Resources.h"
#include "Player.h"
#include "LaserRotatingState.h"
#include "LaserStaticState.h"

Laser::Laser(const sf::Vector2f& position, LaserOrientation orientation)
// On appelle le parent avec frameCount=1 pour bloquer le découpage horizontal des pièces
    : StaticGameObject(Resources::getInstance().getTexture("Laser"), position, 1),
    m_isDisposed(false),
    m_animationTimer(0.0f),
    m_currentFrameIndex(0)
{
    // 1. DÉCOUPAGE VERTICAL DU LASER
    const sf::Texture& texture = m_sprite.getTexture();
    int frameCount = 4; // L'image a 4 orbes empilés

    float frameWidth = static_cast<float>(texture.getSize().x);
    // On divise la HAUTEUR par 4, pas la largeur !
    float frameHeight = static_cast<float>(texture.getSize().y) / frameCount;

    for (int i = 0; i < frameCount; ++i) {
        m_laserFrames.push_back(sf::IntRect(
            { 0, static_cast<int>(i * frameHeight) },
            { static_cast<int>(frameWidth), static_cast<int>(frameHeight) }
        ));
    }

    // On applique le premier rectangle (Cela n'affichera qu'un seul orbe)
    if (!m_laserFrames.empty()) {
        m_sprite.setTextureRect(m_laserFrames[0]);
    }

    // 2. CENTRAGE DE L'ORIGINE
    m_sprite.setOrigin({ frameWidth / 2.0f, frameHeight / 2.0f });

    // 3. ORIENTATION (Coucher le laser si horizontal)
    if (orientation == LaserOrientation::Horizontal) {
        m_sprite.setRotation(sf::degrees(90.0f));
    }
    else {
        m_sprite.setRotation(sf::degrees(0.0f));
    }

    // 4. POINT DE DÉPART : Le laser naît en mode Alerte
    m_currentState = std::make_unique<LaserRotatingState>();
}

void Laser::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void Laser::update(float deltaTime) {
    if (m_currentState) {
        m_currentState->update(*this, deltaTime);
    }
}

void Laser::collide(Object& other) {
    other.collide(*this);
}

void Laser::collide(Player& player) {
    if (m_isDisposed || !m_currentState) return;
    m_currentState->collide(player); // Délégation à l'état !
}

void Laser::changeState(std::unique_ptr<LaserState> newState) {
    if (newState) {
        m_currentState = std::move(newState);
    }
}

void Laser::animatePlasma(float deltaTime) {
    if (m_laserFrames.empty()) return;

    // Animation rapide du plasma actif
    m_animationTimer += deltaTime;
    if (m_animationTimer >= 0.05f) {
        m_animationTimer = 0.0f;
        m_currentFrameIndex = (m_currentFrameIndex + 1) % m_laserFrames.size();
        m_sprite.setTextureRect(m_laserFrames[m_currentFrameIndex]);
    }
}

bool Laser::isDisposed() const {
    return m_isDisposed;
}