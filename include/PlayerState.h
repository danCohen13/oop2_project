#pragma once
#include <SFML/Graphics.hpp>

class Player;

class PlayerState {
public:
    virtual ~PlayerState() = default;

    // Modification de l'animation (demande un accès non-const au Player)
    virtual void update(Player& player, float deltaTime) = 0;

    // Rendu graphique (respecte la const-correctness pure de SFML)
    virtual void draw(sf::RenderWindow& window,
        const sf::Sprite& playerSprite,
        const sf::Sprite& flameSprite,
        bool isThrusting) const = 0;
};