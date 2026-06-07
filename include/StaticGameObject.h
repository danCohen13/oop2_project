#pragma once
#include "Object.h"
#include <vector> // Pour stocker les rectangles pré-calculés

class StaticGameObject : public Object {
public:
    // Le constructeur reçoit toujours le nombre de frames (4 par défaut pour la pièce)
    StaticGameObject(const sf::Texture& texture, const sf::Vector2f& position, int frameCount = 1);
    virtual ~StaticGameObject() override = default;

    virtual void update(float deltaTime) override;

protected:
    // LA PLOMBERIE TECHNIQUE COMMUNE
    void animate(float deltaTime); // Méthode centralisée d'animation

    std::vector<sf::IntRect> m_frames; // Le catalogue de rectangles de cet objet
    size_t m_currentFrame;             // Frame active
    float m_frameTimer;                // Chronomètre accumulation deltaTime
    const float FRAME_DURATION = 0.1f; // Vitesse d'animation commune
};