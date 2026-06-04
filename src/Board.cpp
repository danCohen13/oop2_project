#include "Board.h"
#include <algorithm>
#include <cstdlib>

Board::Board()
    : m_player(std::make_unique<Player>()),
    m_coinTimer(2.0f),
    m_laserTimer(4.0f) {
}

// CORRECTION : Implémentation sans sf::RenderWindow
void Board::play(float deltaTime, bool isThrusting) {
    m_player->update(deltaTime, isThrusting);

    for (auto& obj : m_movings) obj->update(deltaTime);
    for (auto& obj : m_statics) obj->update(deltaTime);

    checkCollisions();
    generateLevel(deltaTime); // Appel mis à jour

    // CORRECTION ARCHITECTURALE :
    // Puisque la caméra suit le joueur avec un tiers d'écran de décalage,
    // la limite gauche de l'écran visible se trouve exactement à : position du joueur - 400 pixels.
    float cullX = m_player->getPosition().x - 400.0f;

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

// CORRECTION : Nettoyage du paramètre window inutile
void Board::generateLevel(float deltaTime) {
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