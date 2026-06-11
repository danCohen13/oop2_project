#include "GameSession.h"

GameSession::GameSession()
    : m_score(0), m_lives(1), m_gameSpeed(140.0f)
{
}

void GameSession::update(float deltaTime, bool isThrusting) {
    if (m_gameSpeed < 900.0f) {
        m_gameSpeed += 3.5f * deltaTime;
    }

    m_board.play(deltaTime, m_gameSpeed, isThrusting);

    int coins = m_board.getCoinsCollectedThisFrame();
    if (coins > 0) {
        addScore(1); 
    }

    if (m_board.hasPlayerHitHazard()) {
        removeLife();
    }
}

void GameSession::drawWorld(sf::RenderWindow& window) const {
    m_board.draw(window); 
}

int GameSession::getScore() const { return m_score; }
int GameSession::getLives() const { return m_lives; }
bool GameSession::isGameOver() const { return m_lives <= 0 || !m_board.isPlayerAlive(); }
sf::Vector2f GameSession::getPlayerPosition() const { return m_board.getPlayerPosition(); }

void GameSession::addScore(int points) { m_score += points; }
void GameSession::removeLife() { m_lives--; }