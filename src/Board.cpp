#include "Board.h"
#include "CollisionManager.h"
#include "LevelGenerator.h"
#include "ObjectCleaner.h"
#include "GameObjectFactory.h" 
#include "Coin.h"
//#include "Laser.h" 

Board::Board()
    : m_player(std::make_unique<Player>()),
    m_collisionManager(std::make_unique<CollisionManager>()),
    m_levelGenerator(std::make_unique<LevelGenerator>()),
    m_objectCleaner(std::make_unique<ObjectCleaner>())
{
    GameObjectFactory::registerType<Coin>("Coin");
    //GameObjectFactory::registerType<Laser>("Laser"); 
}

Board::~Board() = default;

void Board::play(float deltaTime, bool isThrusting) {
    m_player->update(deltaTime, isThrusting);

    for (auto& obj : m_objects) {
        obj->update(deltaTime);
    }

    m_collisionManager->handleCollisions(*m_player, m_objects);

    // 4. Génération procédurale de nouveaux obstacles en amont du joueur
    m_levelGenerator->generate(deltaTime, m_objects, m_player->getPosition().x);

    m_objectCleaner->cleanup(m_objects, m_player->getPosition().x);
}

void Board::draw(sf::RenderWindow& window) const {
    for (const auto& obj : m_objects) {
        obj->draw(window);
    }
    m_player->draw(window);
}

bool Board::isPlayerAlive() const { return !m_player->isDead(); }

sf::Vector2f Board::getPlayerPosition() const { return m_player->getPosition(); }