#include "Object.h"

void Object::setPosition(const sf::Vector2f& position) {
    m_sprite.setPosition(position);
}

sf::Vector2f Object::getPosition() const {
    return m_sprite.getPosition();
}

sf::FloatRect Object::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

sf::FloatRect Object::getLocalBounds() const {
    return m_sprite.getLocalBounds();
}

void Player::collide(Object& other) {
    other.collide(*this); // Pass Player& to the other object
}

void Player::collide(Player& player) {} // No-op: players don't collide with players

void Player::collide(Coin& coin) {
    // Logic: Player collects the coin
    coin.setCollected(true);
}

void Player::collide(Laser& laser) {
    // Logic: Player hits a hazard and dies
    this->setDead(true);
}