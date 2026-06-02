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

    // Non-copyable due to unique_ptr tracking
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    // Main physics, lifecycle and collision update loop
    void play(sf::RenderWindow& window, float deltaTime);

    // Render loop orchestration
    void draw(sf::RenderWindow& window) const;

    bool isPlayerAlive() const;
    sf::Vector2f getPlayerPosition() const;

private:
    // Triggers procedural element spawning
    void generateLevel(sf::RenderWindow& window, float deltaTime);

    // Processes all entities interactions via Double Dispatch
    void checkCollisions();

    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr<StaticGameObject>> m_statics;
    std::vector<std::unique_ptr<MovingGameObject>> m_movings;

    float m_coinTimer;
    float m_laserTimer;
};