#pragma once
#include "StaticGameObject.h"
#include "LaserState.h"
#include <memory>
#include <vector>

enum class LaserOrientation { Horizontal, Vertical };

class Laser : public StaticGameObject {
public:
    Laser(const sf::Vector2f& position, LaserOrientation orientation = LaserOrientation::Horizontal);
    virtual ~Laser() override = default;

    // Fonctions héritées de Object (Orchestration légère)
    virtual void draw(sf::RenderWindow& window) const override;
    virtual void update(float deltaTime) override;
    virtual void collide(Object& other) override;
    virtual void collide(Player& player) override;
    virtual bool isDisposed() const override;

    // Outils offerts aux classes d'États pour manipuler le Laser
    void changeState(std::unique_ptr<LaserState> newState);
    void animatePlasma(float deltaTime);
    sf::Sprite& getSprite() { return m_sprite; }

private:
    bool m_isDisposed;
    std::unique_ptr<LaserState> m_currentState;

    // Stockage local des coordonnées de texture pour l'effet pulsing du plasma
    std::vector<sf::IntRect> m_laserFrames;
    size_t m_currentFrameIndex = 0;
    float m_animationTimer = 0.0f;
};