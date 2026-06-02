#include "Board.h"
#include <algorithm>
#include <cstdlib>

Board::Board()
    : m_player(std::make_unique<Player>()),
    m_coinTimer(2.0f),
    m_laserTimer(4.0f) {
}

void Board::play(sf::RenderWindow& window, float deltaTime) {
    // 1. Update player physics
    m_player->update(deltaTime);

    // 2. Update all linear moving entities (e.g., Lasers)
    for (auto& obj : m_movings) {
        obj->update(deltaTime);
    }

    // 3. Update all static entities (e.g., Coin animations)
    for (auto& obj : m_statics) {
        obj->update(deltaTime);
    }

    // 4. Resolve interactions polymorphically
    checkCollisions();

    // 5. Generate upcoming obstacles ahead of viewport
    generateLevel(window, deltaTime);

    // 6. Memory culling: clean up entities that completely left the screen view
    float cullX = window.getView().getCenter().x - window.getView().getSize().x / 2.0f;

    m_statics.erase(
        std::remove_if(m_statics.begin(), m_statics.end(),
            [cullX](const std::unique_ptr<StaticGameObject>& obj) {
                return (obj->getPosition().x + obj->getGlobalBounds().width) < cullX;
            }),
        m_statics.end()
    );

    m_movings.erase(
        std::remove_if(m_movings.begin(), m_movings.end(),
            [cullX](const std::unique_ptr<MovingGameObject>& obj) {
                return (obj->getPosition().x + obj->getGlobalBounds().width) < cullX;
            }),
        m_movings.end()
    );
}

void Board::draw(sf::RenderWindow& window) const {
    for (const auto& obj : m_statics) {
        obj->draw(window);
    }

    for (const auto& obj : m_movings) {
        obj->draw(window);
    }

    m_player->draw(window);
}

void Board::generateLevel(sf::RenderWindow& window, float deltaTime) {
    m_coinTimer -= deltaTime;
    m_laserTimer -= deltaTime;

    float spawnX = window.getView().getCenter().x + window.getView().getSize().x / 2.0f;

    if (m_coinTimer <= 0.0f) {
        // Spawning logic / Factory hooks go here
        m_coinTimer = static_cast<float>(2 + rand() % 4);
    }

    if (m_laserTimer <= 0.0f) {
        // Spawning logic / Factory hooks go here
        m_laserTimer = static_cast<float>(4 + rand() % 6);
    }
}

void Board::checkCollisions() {
    sf::FloatRect playerBounds = m_player->getGlobalBounds();

    // Check collisions with static environmental objects via Double Dispatch
    m_statics.erase(
        std::remove_if(m_statics.begin(), m_statics.end(),
            [this, playerBounds](const std::unique_ptr<StaticGameObject>& obj) {
                if (playerBounds.intersects(obj->getGlobalBounds())) {
                    // Triggers Double Dispatch chain: m_player passes itself to the object
                    m_player->collide(*obj);

                    // Returns true if the object was flagged as collected/disposed inside Player overloads
                    return obj->isDisposed();
                }
                return false;
            }),
        m_statics.end()
    );

    // Check collisions with moving hazards via Double Dispatch
    for (auto& obj : m_movings) {
        if (playerBounds.intersects(obj->getGlobalBounds())) {
            // Triggers Double Dispatch chain (e.g., will execute Player::collide(Laser&))
            m_player->collide(*obj);
        }
    }
}

bool Board::isPlayerAlive() const {
    return !m_player->isDead();
}

sf::Vector2f Board::getPlayerPosition() const {
    return m_player->getPosition();
}