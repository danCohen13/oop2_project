#include "LevelGenerator.h"
#include "CoinFormation.h"
#include "GameObjectFactory.h"
#include <cstdlib>

LevelGenerator::LevelGenerator()
    : m_nextSpawnX(0.0f) {
}

void LevelGenerator::generate(float deltaTime, std::vector<std::unique_ptr<Object>>& objects, float playerX) {
    (void)deltaTime;

    // On anticipe la zone d'apparition en amont de l'écran du joueur
    float currentSpawnZoneX = playerX + 1400.0f;

    if (m_nextSpawnX == 0.0f) {
        m_nextSpawnX = currentSpawnZoneX;
    }

    if (currentSpawnZoneX >= m_nextSpawnX) {
        float spawnX = m_nextSpawnX;
        float generationWidth = 0.0f;

        // =====================================================================
        // LA SOLUTION : Sélection exclusive du type d'événement (Ratio 60% Pièces / 40% Laser)
        // =====================================================================
        int eventChoice = rand() % 10;

        if (eventChoice < 6) {
            // -----------------------------------------------------------------
            // ÉVÉNEMENT A : GÉNÉRATION DES PIÈCES (60% de chance)
            // -----------------------------------------------------------------
            int formationType = rand() % 5;
            float spawnY = 0.0f;
            const float HALF = COIN_SPACING / 2.0f;

            switch (formationType) {
            case 0: { // LIGNE
                int length = 8 + rand() % 6;
                int thickness = 1 + rand() % 3;
                float minY = CEILING_LIMIT + HALF;
                float maxY = FLOOR_LIMIT - ((thickness - 1) * COIN_SPACING) - HALF;

                if (maxY < minY) maxY = minY;
                spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

                CoinFormation::createLine(objects, spawnX, spawnY, COIN_SPACING, length, thickness);
                generationWidth = length * COIN_SPACING;
                break;
            }
            case 1: { // DIAGONALE
                int length = 4 + rand() % 3;
                float minY = CEILING_LIMIT + HALF;
                float maxY = FLOOR_LIMIT - ((length - 1) * COIN_SPACING) - HALF;

                if (maxY < minY) maxY = minY;
                spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

                CoinFormation::createDiagonal(objects, spawnX, spawnY, COIN_SPACING, length);
                generationWidth = length * COIN_SPACING;
                break;
            }
            case 2: { // VAGUE (SERPENT)
                int length = 12 + rand() % 6;
                float amplitude = COIN_SPACING * 1.4f;
                float minY = CEILING_LIMIT + amplitude + HALF;
                float maxY = FLOOR_LIMIT - amplitude - HALF;

                if (maxY < minY) maxY = minY;
                spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

                CoinFormation::createWave(objects, spawnX, spawnY, COIN_SPACING, length);
                generationWidth = length * (COIN_SPACING * 1.7f);
                break;
            }
            case 3: { // TRIANGLE
                int size = 3 + rand() % 3;
                float minY = CEILING_LIMIT + HALF;
                float maxY = FLOOR_LIMIT - ((size - 1) * COIN_SPACING) - HALF;

                if (maxY < minY) maxY = minY;
                spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

                CoinFormation::createTriangle(objects, spawnX, spawnY, COIN_SPACING, size);
                generationWidth = size * COIN_SPACING;
                break;
            }
            case 4: { // CERCLE
                int radiusFactor = 2;
                float radius = COIN_SPACING * 3.0f;
                float minY = CEILING_LIMIT + radius + HALF;
                float maxY = FLOOR_LIMIT - radius - HALF;

                if (maxY < minY) maxY = minY;
                spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

                CoinFormation::createCircle(objects, spawnX, spawnY, COIN_SPACING, radiusFactor);
                generationWidth = radius * 2.0f;
                break;
            }
            }
        }
        else {
            // -----------------------------------------------------------------
            // ÉVÉNEMENT B : GÉNÉRATION D'UN LASER ANCRÉ (40% de chance)
            // -----------------------------------------------------------------
            float laserX = spawnX + 200.0f;
            const float LASER_RADIUS = 175.0f;
            float laserY = 0.0f;

            // Une chance sur deux : Ancré au Plafond OU Ancré au Sol
            if (rand() % 2 == 0) {
                // ANCRE PLAFOND : Le sommet du laser touchera exactement Y = 50
                laserY = CEILING_LIMIT + LASER_RADIUS; // 50 + 175 = 225
            }
            else {
                // ANCRE SOL : La base du laser touchera exactement Y = 530
                laserY = FLOOR_LIMIT - LASER_RADIUS; // 530 - 175 = 355
            }

            objects.push_back(GameObjectFactory::createObject("Laser", { laserX, laserY }));

            generationWidth = 400.0f;
        }

        // =====================================================================
        // CALCUL DU PROCHAIN SPAWN (Espacement garanti entre chaque événement)
        // =====================================================================
        float separationPadding = 900.0f + static_cast<float>(rand() % 600);
        m_nextSpawnX = spawnX + generationWidth + separationPadding;
    }
}