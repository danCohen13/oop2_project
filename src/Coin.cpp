#include "Coin.h"
#include "Resources.h"

Coin::Coin(const sf::Vector2f& position)
// On passe '4' au parent : il va automatiquement générer 4 sf::IntRect dans m_frames !
    : StaticGameObject(Resources::getInstance().getTexture("Coin"), position, 4),
    m_isDisposed(false)
{
    // C'EST TOUT ! Le vecteur m_frames est déjà prêt et exploitable.
}

void Coin::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void Coin::update(float deltaTime) {
    // On appelle directement la mise à jour parente qui gère la rotation infinie
    StaticGameObject::update(deltaTime);
}

void Coin::collide(Object& other) { other.collide(*this); }
void Coin::collide(Player& player) { m_isDisposed = true; }
bool Coin::isDisposed() const { return m_isDisposed; }