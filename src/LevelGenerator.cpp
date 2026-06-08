#include "LevelGenerator.h"
#include "CoinFormation.h"
#include <cstdlib>

LevelGenerator::LevelGenerator()
    : m_nextSpawnX(0.0f) {
}

void LevelGenerator::generate(float deltaTime, std::vector<std::unique_ptr<Object>>& objects, float playerX) {
    (void)deltaTime; // Évite le warning de paramètre non utilisé

    // Zone d'apparition hors-champ à droite (1200 de largeur + marge de 200px)
    float currentSpawnZoneX = playerX + 1400.0f;

    if (m_nextSpawnX == 0.0f) {
        m_nextSpawnX = currentSpawnZoneX;
    }

    if (currentSpawnZoneX >= m_nextSpawnX) {
        float spawnX = m_nextSpawnX;
        int formationType = rand() % 5;

        float formationWidth = 0.0f;
        float spawnY = 0.0f;

        switch (formationType) {
        case 0: { // LIGNE
            int length = 8 + rand() % 6;
            int thickness = 1 + rand() % 3;
            float minY = CEILING_LIMIT;
            float maxY = FLOOR_LIMIT - ((thickness - 1) * COIN_SPACING);
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));
            CoinFormation::createLine(objects, spawnX, spawnY, COIN_SPACING, length, thickness);
            formationWidth = length * COIN_SPACING;
            break;
        }
        case 1: { // DIAGONALE
            int length = 4 + rand() % 3;
            float minY = CEILING_LIMIT;
            float maxY = FLOOR_LIMIT - ((length - 1) * COIN_SPACING);
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));
            CoinFormation::createDiagonal(objects, spawnX, spawnY, COIN_SPACING, length);
            formationWidth = length * COIN_SPACING;
            break;
        }
        case 2: { // VAGUE (SERPENT)
            int length = 12 + rand() % 6;
            float amplitude = COIN_SPACING * 1.4f;
            float minY = CEILING_LIMIT + amplitude;
            float maxY = FLOOR_LIMIT - amplitude;
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

            CoinFormation::createWave(objects, spawnX, spawnY, COIN_SPACING, length);
            // AJUSTEMENT : Prise en compte du nouvel espacement horizontal du serpent
            formationWidth = length * (COIN_SPACING * 1.3f);
            break;
        }
        case 3: { // TRIANGLE
            int size = 3 + rand() % 3;
            float minY = CEILING_LIMIT;
            float maxY = FLOOR_LIMIT - ((size - 1) * COIN_SPACING);
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));
            CoinFormation::createTriangle(objects, spawnX, spawnY, COIN_SPACING, size);
            formationWidth = size * COIN_SPACING;
            break;
        }
        case 4: { // CERCLE
            int radiusFactor = 2;
            float radius = COIN_SPACING * (static_cast<float>(radiusFactor) + 0.4f);
            float minY = CEILING_LIMIT + radius;
            float maxY = FLOOR_LIMIT - radius;
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

            CoinFormation::createCircle(objects, spawnX, spawnY, COIN_SPACING, radiusFactor);
            // AJUSTEMENT : Prise en compte du diamètre total mis à jour
            formationWidth = radius * 2.0f;
            break;
        }
        }

        // Raréfaction des formes : grand espace vide aléatoire avant la prochaine forme
        float separationPadding = 1800.0f + static_cast<float>(rand() % 1200);
        m_nextSpawnX = spawnX + formationWidth + separationPadding;
    }
}