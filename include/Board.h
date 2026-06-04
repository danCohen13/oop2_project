#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "StaticGameObject.h"
#include "MovingGameObject.h"

class Board {
public:
    Board();
    ~Board() = default;

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    // CORRECTION : Signature simplifiée à 2 arguments
    void play(float deltaTime, bool isThrusting);
    void draw(sf::RenderWindow& window) const;

    bool isPlayerAlive() const;
    sf::Vector2f getPlayerPosition() const;

private:
    // CORRECTION : Plus besoin de fenêtre ici
    void generateLevel(float deltaTime);
    void checkCollisions();

    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr<StaticGameObject>> m_statics;
    std::vector<std::unique_ptr<MovingGameObject>> m_movings;

    float m_coinTimer;
    float m_laserTimer;
};