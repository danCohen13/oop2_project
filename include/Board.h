#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "Object.h"

// Forward declarations des sous-systèmes
class CollisionManager;
class LevelGenerator;
class ObjectCleaner;

class Board {
public:
    Board();
    ~Board();

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    void play(float deltaTime, bool isThrusting);
    void draw(sf::RenderWindow& window) const;

    bool isPlayerAlive() const;
    sf::Vector2f getPlayerPosition() const;

private:
    std::unique_ptr<Player> m_player;
    std::vector<std::unique_ptr<Object>> m_objects; // Vecteur unique unifié

    // Sous-composants d'architecture séparés
    std::unique_ptr<CollisionManager> m_collisionManager;
    std::unique_ptr<LevelGenerator> m_levelGenerator;
    std::unique_ptr<ObjectCleaner> m_objectCleaner;
};