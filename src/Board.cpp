#include "Board.h"
#include <algorithm>
#include <cstdlib>

Board::Board()
    : m_player(std::make_unique<Player>()),
    m_coinTimer(2.0f),
    m_laserTimer(4.0f) {
}

void Board::play(sf::RenderWindow& window, float deltaTime, bool isThrusting) {
    m_player->update(deltaTime, isThrusting);

    for (auto& obj : m_movings) obj->update(deltaTime);
    for (auto& obj : m_statics) obj->update(deltaTime);

    checkCollisions();
    generateLevel(window, deltaTime);

    float cullX = window.getView().getCenter().x - window.getView().getSize().x / 2.0f;

    // SFML 3.0 uses size.x instead of width
    m_statics.erase(
        std::remove_if(m_statics.begin(), m_statics.end(),
            [cullX](const std::unique_ptr<StaticGameObject>& obj) {
                return (obj->getPosition().x + obj->getGlobalBounds().size.x) < cullX;
            }),
        m_statics.end()
    );

    m_movings.erase(
        std::remove_if(m_movings.begin(), m_movings.end(),
            [cullX](const std::unique_ptr<MovingGameObject>& obj) {
                return (obj->getPosition().x + obj->getGlobalBounds().size.x) < cullX;
            }),
        m_movings.end()
    );
}

void Board::draw(sf::RenderWindow& window) const {
    for (const auto& obj : m_statics) obj->draw(window);
    for (const auto& obj : m_movings) obj->draw(window);
    m_player->draw(window);
}

void Board::generateLevel(sf::RenderWindow& window, float deltaTime) {
    m_coinTimer -= deltaTime;
    m_laserTimer -= deltaTime;

    if (m_coinTimer <= 0.0f) {
        m_coinTimer = static_cast<float>(2 + rand() % 4);
    }
    if (m_laserTimer <= 0.0f) {
        m_laserTimer = static_cast<float>(4 + rand() % 6);
    }
}

void Board::checkCollisions() {
    sf::FloatRect playerBounds = m_player->getGlobalBounds();

    // SFML 3.0 uses findIntersection().has_value() instead of intersects()
    m_statics.erase(
        std::remove_if(m_statics.begin(), m_statics.end(),
            [this, playerBounds](const std::unique_ptr<StaticGameObject>& obj) {
                if (playerBounds.findIntersection(obj->getGlobalBounds()).has_value()) {
                    m_player->collide(*obj);
                    return obj->isDisposed();
                }
                return false;
            }),
        m_statics.end()
    );

    for (auto& obj : m_movings) {
        if (playerBounds.findIntersection(obj->getGlobalBounds()).has_value()) {
            m_player->collide(*obj);
        }
    }
}

bool Board::isPlayerAlive() const { return !m_player->isDead(); }
sf::Vector2f Board::getPlayerPosition() const { return m_player->getPosition(); }