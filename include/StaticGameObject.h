#pragma once
#include "Object.h"

class StaticGameObject : public Object {
public:
    // Le constructeur magique : il prend la texture, la position, et le nombre de frames (1 par défaut si fixe)
    StaticGameObject(const sf::Texture& texture, const sf::Vector2f& position, int frameCount = 1);
    virtual ~StaticGameObject() override = default;

    void update(float deltaTime);

protected:
    int m_frameCount;
    int m_currentFrame;
    float m_frameTimer;
    const float FRAME_DURATION = 0.1f; // Vitesse de l'animation
};