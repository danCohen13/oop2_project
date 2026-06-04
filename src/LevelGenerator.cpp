#include "LevelGenerator.h"
#include <cstdlib>

LevelGenerator::LevelGenerator()
    : m_coinTimer(2.0f), m_laserTimer(4.0f) {
}

void LevelGenerator::generate(float deltaTime, std::vector<std::unique_ptr<Object>>& objects, float playerX) {
    m_coinTimer -= deltaTime;
    m_laserTimer -= deltaTime;

    if (m_coinTimer <= 0.0f) {
        // TODO : Appeler votre GameObjectFactory ici plus tard !
        // objects.push_back(GameObjectFactory::createObject("Coin", playerX + 1200.0f));
        m_coinTimer = static_cast<float>(2 + rand() % 4);
    }

    if (m_laserTimer <= 0.0f) {
        // TODO : Appeler votre GameObjectFactory ici plus tard !
        // objects.push_back(GameObjectFactory::createObject("Laser", playerX + 1200.0f));
        m_laserTimer = static_cast<float>(4 + rand() % 6);
    }
}