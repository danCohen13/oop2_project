#include "StaticGameObject.h"

StaticGameObject::StaticGameObject(const sf::Texture& texture,
    const sf::Vector2f& position,
    int frameCount)
    : Object(texture),
    m_animator(texture, frameCount)   // ← délègue à SpriteAnimator
{
    // Centrage de l'origine + première frame
    auto size = m_animator.getFrameSize();
    m_sprite.setOrigin({ size.x / 2.0f, size.y / 2.0f });
    m_animator.applyTo(m_sprite);
    m_sprite.setPosition(position);
    m_sprite.setScale({ 1.0f, 1.0f });
}

void StaticGameObject::update(float deltaTime) {
    if (m_animator.update(deltaTime))
        m_animator.applyTo(m_sprite);
}