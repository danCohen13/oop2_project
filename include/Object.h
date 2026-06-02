#pragma once

#include <SFML/Graphics.hpp>

// Forward declarations for Double Dispatch
class Player;
class Coin;
class Laser;

class Object {
public:
    Object() = default;
    virtual ~Object() = default;

    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void update(float deltaTime) = 0;

    // First dispatch: resolves the dynamic type of the object itself
    virtual void collide(Object& other) = 0;

    // Second dispatch: overloads to resolve the target concrete type
    virtual void collide(Player& player) = 0;
    virtual void collide(Coin& coin) = 0;
    virtual void collide(Laser& laser) = 0;

    // Lifecycle management to flag objects for disposal (e.g., collected coins)
    virtual bool isDisposed() const { return false; }

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

protected:
    sf::Sprite m_sprite;
};