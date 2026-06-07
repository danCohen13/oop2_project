#include "LevelGenerator.h"
#include "GameObjectFactory.h"

#include <cstdlib>

LevelGenerator::LevelGenerator()
    : m_coinTimer(2.0f), m_laserTimer(4.0f) {
}

void LevelGenerator::generate(float deltaTime, std::vector<std::unique_ptr<Object>>& objects, float playerX) {
    m_coinTimer -= deltaTime;
    m_laserTimer -= deltaTime;

    // 1. Génération des pièces régulières (Remets bien l'image Coin.png pour elles !)
    if (m_coinTimer <= 0.0f) {
        float spawnX = playerX + 1300.0f;
        float spawnY = static_cast<float>(150 + rand() % 300);

        objects.push_back(GameObjectFactory::createObject("Coin", { spawnX, spawnY }));
        m_coinTimer = static_cast<float>(3 + rand() % 4);
    }

    // 2. LOGIQUE CORRIGÉE : Génération des vrais Lasers à états
    if (m_laserTimer <= 0.0f) {
        float spawnX = playerX + 1500.0f;
        float spawnY = static_cast<float>(150 + rand() % 300);

        // On alterne aléatoirement entre Laser Horizontal et Vertical
        LaserOrientation orientation = (rand() % 2 == 0) ? LaserOrientation::Horizontal : LaserOrientation::Vertical;

        // On injecte un vrai Laser dans le vecteur de jeu
        objects.push_back(std::make_unique<Laser>(sf::Vector2f{ spawnX, spawnY }, orientation));

        m_laserTimer = static_cast<float>(5 + rand() % 5);
    }
}