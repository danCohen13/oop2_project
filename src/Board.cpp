#include "Board.h"
#include "CollisionManager.h"
#include "LevelGenerator.h"
#include "ObjectCleaner.h"

Board::Board()
    : m_player(std::make_unique<Player>()),
    m_collisionManager(std::make_unique<CollisionManager>()),
    m_levelGenerator(std::make_unique<LevelGenerator>()),
    m_objectCleaner(std::make_unique<ObjectCleaner>()) {
}

Board::~Board() = default;

void Board::play(float deltaTime, bool isThrusting) {
    // 1. Mise à jour physique autonome du joueur
    m_player->update(deltaTime, isThrusting);

    // 2. Mise à jour polymorphique de chaque obstacle
    for (auto& obj : m_objects) {
        obj->update(deltaTime);
    }

    // 3. Délégation des responsabilités aux sous-fichiers
    m_collisionManager->handleCollisions(*m_player, m_objects);
    m_levelGenerator->generate(deltaTime, m_objects, m_player->getPosition().x);
    m_objectCleaner->cleanup(m_objects, m_player->getPosition().x);
}

void Board::draw(sf::RenderWindow& window) const {
    // Rendu en une seule passe propre de tous les obstacles du vecteur unique
    for (const auto& obj : m_objects) {
        obj->draw(window);
    }
    m_player->draw(window);
}

bool Board::isPlayerAlive() const { return !m_player->isDead(); }
sf::Vector2f Board::getPlayerPosition() const { return m_player->getPosition(); }