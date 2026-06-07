#include "LaserState.h"
#include "Laser.h"
#include "LaserStaticState.h"

class LaserRotatingState : public LaserState {
public:
    virtual void update(Laser& laser, float deltaTime) override {
        // 1. Rotation continue pendant l'alerte
        laser.getSprite().rotate(sf::degrees(90.0f * deltaTime));

        // 2. Clignotement de couleur (Alerte visuelle)
        m_timer += deltaTime;
        if (m_timer >= 0.15f) {
            m_timer = 0.0f;
            m_flash = !m_flash;
            laser.getSprite().setColor(m_flash ? sf::Color::Red : sf::Color(255, 255, 255, 100));
        }

        // 3. Transition automatique après 2 secondes d'alerte
        m_lifetime += deltaTime;
        if (m_lifetime >= 2.0f) {
            laser.changeState(std::make_unique<LaserStaticState>());
        }
    }

    virtual void collide(Player&) override {
        // VIDE : Le joueur ne meurt pas pendant la phase d'alerte !
    }

private:
    float m_timer = 0.0f;
    float m_lifetime = 0.0f;
    bool m_flash = false;
};