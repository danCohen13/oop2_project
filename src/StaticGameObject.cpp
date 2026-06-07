#include "StaticGameObject.h"

StaticGameObject::StaticGameObject(const sf::Texture& texture, const sf::Vector2f& position, int frameCount)
    : Object(texture), m_currentFrame(0), m_frameTimer(0.0f)
{
    // 1. Calcul de la taille d'une frame individuelle
    float frameWidth = static_cast<float>(texture.getSize().x) / frameCount;
    float frameHeight = static_cast<float>(texture.getSize().y);

    // 2. PRÉ-CALCUL ET STOCKAGE : On remplit le vecteur hérité
    for (int i = 0; i < frameCount; ++i) {
        m_frames.push_back(sf::IntRect(
            { static_cast<int>(i * frameWidth), 0 },
            { static_cast<int>(frameWidth), static_cast<int>(frameHeight) }
        ));
    }

    // 3. Application de la première frame de départ pour sécuriser la Hitbox
    if (!m_frames.empty()) {
        m_sprite.setTextureRect(m_frames[0]);
    }

    // 4. Centrage de l'origine et positionnement initial
    m_sprite.setOrigin({ frameWidth / 2.0f, frameHeight / 2.0f });
    m_sprite.setPosition(position);
    m_sprite.setScale({ 1.0f, 1.0f });
}

void StaticGameObject::animate(float deltaTime) {
    // S'il n'y a qu'une seule frame (ex: un décor fixe), pas besoin d'animer
    if (m_frames.size() <= 1) return;

    m_frameTimer += deltaTime;
    if (m_frameTimer >= FRAME_DURATION) {
        m_frameTimer = 0.0f;

        // Progression circulaire dans le vecteur pré-calculé
        m_currentFrame = (m_currentFrame + 1) % m_frames.size();

        // Application instantanée sans calcul mathématique lourd
        m_sprite.setTextureRect(m_frames[m_currentFrame]);
    }
}

void StaticGameObject::update(float deltaTime) {
    // Par défaut, l'infrastructure anime l'objet statique en boucle
    animate(deltaTime);
}