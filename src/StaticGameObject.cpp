#include "StaticGameObject.h"

StaticGameObject::StaticGameObject(const sf::Texture& texture, const sf::Vector2f& position, int frameCount)
    : Object(texture), m_frameCount(frameCount), m_currentFrame(0), m_frameTimer(0.0f)
{
    // 1. Calcul de la taille d'une seule frame
    float frameWidth = static_cast<float>(texture.getSize().x) / m_frameCount;
    float frameHeight = static_cast<float>(texture.getSize().y);

    // 2. Découpage chirurgical de la première frame (Hitbox parfaite)
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { static_cast<int>(frameWidth), static_cast<int>(frameHeight) }));

    // 3. Centrage de l'origine au milieu de cette frame unique
    m_sprite.setOrigin({ frameWidth / 2.0f, frameHeight / 2.0f });
    m_sprite.setPosition(position);
    m_sprite.setScale({ 1.0f, 1.0f });
}

void StaticGameObject::update(float deltaTime) {
    if (m_frameCount <= 1) return; // Pas d'animation si c'est une image fixe

    m_frameTimer += deltaTime;
    if (m_frameTimer >= FRAME_DURATION) {
        m_frameTimer = 0.0f;
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;

        float frameWidth = static_cast<float>(m_sprite.getTexture().getSize().x) / m_frameCount;
        int frameHeight = m_sprite.getTexture().getSize().y;

        // Déplacement du rectangle de lecture sur la frame suivante
        m_sprite.setTextureRect(sf::IntRect({ static_cast<int>(m_currentFrame * frameWidth), 0 },
            { static_cast<int>(frameWidth), frameHeight }));
    }
}