#pragma once
#include <SFML/Graphics.hpp>

class Player;
class Coin;
class Laser;

class Object {
public:
    // Requires a texture reference explicitly in SFML 3.0
    Object(const sf::Texture& texture);
    virtual ~Object() = default;

    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void update(float deltaTime) = 0;

    virtual void collide(Object& other) = 0;
    virtual void collide(Player& player) {}
    virtual void collide(Coin& coin) {}
    virtual void collide(Laser& laser) {}

    virtual bool isDisposed() const { return false; }

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

protected:
    sf::Sprite m_sprite;
};