#include "Coin.h"
#include "Resources.h"

// Si ton image Coin.png a 4 frames d'animation, tu passes 4. Si elle est fixe, tu passes 1.
Coin::Coin(const sf::Vector2f& position)
    : StaticGameObject(Resources::getInstance().getTexture("Coin"), position, 4),
    m_isDisposed(false)
{
    // C'EST TOUT ! Le parent a déjà tout découpé, centré et positionné !
}

void Coin::draw(sf::RenderWindow& window) const { window.draw(m_sprite); }
void Coin::update(float deltaTime) { StaticGameObject::update(deltaTime); } // Anime la pièce automatiquement !
void Coin::collide(Object& other) { other.collide(*this); }
void Coin::collide(Player& player) { m_isDisposed = true; }
bool Coin::isDisposed() const { return m_isDisposed; }