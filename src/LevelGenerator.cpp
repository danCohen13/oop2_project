#include "LevelGenerator.h"
#include "GameObjectFactory.h"
#include <cstdlib>
#include <cmath> // Pour std::sin

LevelGenerator::LevelGenerator()
    : m_coinTimer(1.0f) {
}

void LevelGenerator::generate(float deltaTime, std::vector<std::unique_ptr<Object>>& objects, float playerX) {
    m_coinTimer -= deltaTime;

    if (m_coinTimer <= 0.0f) {
        // Apparition loin devant le joueur pour éviter le pop visuel
        float spawnX = playerX + 1400.0f;
        // Hauteur de base aléatoire et centrée
        float spawnY = static_cast<float>(200 + rand() % 150);

        // Choix de la figure (0 à 3)
        int formationType = rand() % 4;

        switch (formationType) {
        case 0:
            // Ligne droite de 6 pièces
            spawnHorizontalLine(objects, spawnX, spawnY, 6);
            m_coinTimer = 3.5f;
            break;

        case 1:
            // Un bloc parfait de 3x3 pièces bien alignées
            spawnBlock(objects, spawnX, spawnY, 3, 3);
            m_coinTimer = 4.0f;
            break;

        case 2:
            // Une belle ondulation sinusoïdale de 8 pièces
            spawnWave(objects, spawnX, spawnY, 8);
            m_coinTimer = 4.5f;
            break;

        case 3:
            // Une flèche indicative pointant vers la droite
            spawnArrow(objects, spawnX, spawnY);
            m_coinTimer = 5.0f;
            break;

        default:
            break;
        }
    }
}

// FORMATION A : Ligne horizontale
void LevelGenerator::spawnHorizontalLine(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, int count) {
    for (int i = 0; i < count; ++i) {
        float x = startX + (i * COIN_SPACING);
        objects.push_back(GameObjectFactory::createObject("Coin", { x, startY }));
    }
}

// FORMATION B : Bloc rectangulaire (Matrice)
void LevelGenerator::spawnBlock(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            float x = startX + (c * COIN_SPACING);
            float y = startY + (r * COIN_SPACING);
            objects.push_back(GameObjectFactory::createObject("Coin", { x, y }));
        }
    }
}

// FORMATION C : Vague sinusoïdale
void LevelGenerator::spawnWave(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, int count) {
    float amplitude = 60.0f; // Hauteur de la courbe
    float frequency = 0.6f;  // Courbure de la vague

    for (int i = 0; i < count; ++i) {
        float x = startX + (i * COIN_SPACING);
        float y = startY + std::sin(i * frequency) * amplitude;
        objects.push_back(GameObjectFactory::createObject("Coin", { x, y }));
    }
}

// FORMATION D : Flèche directionnelle propre (>)
void LevelGenerator::spawnArrow(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY) {
    // La pointe droite de la flèche (le sommet du triangle)
    float peakX = startX + (2 * COIN_SPACING);
    float peakY = startY;

    // 1. La pointe (Peak)
    objects.push_back(GameObjectFactory::createObject("Coin", { peakX, peakY }));

    // 2. L'aile supérieure (va vers le haut et la gauche)
    objects.push_back(GameObjectFactory::createObject("Coin", { peakX - COIN_SPACING, peakY - COIN_SPACING }));
    objects.push_back(GameObjectFactory::createObject("Coin", { peakX - (2 * COIN_SPACING), peakY - (2 * COIN_SPACING) }));

    // 3. L'aile inférieure (va vers le bas et la gauche)
    objects.push_back(GameObjectFactory::createObject("Coin", { peakX - COIN_SPACING, peakY + COIN_SPACING }));
    objects.push_back(GameObjectFactory::createObject("Coin", { peakX - (2 * COIN_SPACING), peakY + (2 * COIN_SPACING) }));

    // 4. La queue centrale de la flèche (part du peak vers la gauche)
    objects.push_back(GameObjectFactory::createObject("Coin", { peakX - COIN_SPACING, peakY }));
    objects.push_back(GameObjectFactory::createObject("Coin", { peakX - (2 * COIN_SPACING), peakY }));
}