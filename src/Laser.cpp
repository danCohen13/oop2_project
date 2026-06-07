#include "Laser.h"
#include "Resources.h"

// Si ton Laser.png est une image fixe unique, le paramètre par défaut (1) s'en occupe
Laser::Laser(const sf::Vector2f& position)
    : StaticGameObject(Resources::getInstance().getTexture("Laser"), position, 1),
    m_isDisposed(false)
{
    // C'EST TOUT ! Rien à découper manuellement
}

void Laser::draw(sf::RenderWindow& window) const { window.draw(m_sprite); }
void Laser::update(float deltaTime) { StaticGameObject::update(deltaTime); }
void Laser::collide(Object& other) { other.collide(*this); }
void Laser::collide(Player& player) { /* player.kill(); */ }
bool Laser::isDisposed() const { return m_isDisposed; }