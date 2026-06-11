#include "LevelGenerator.h"
#include "CoinFormation.h"
#include "GameObjectFactory.h"
#include <cstdlib>

LevelGenerator::LevelGenerator()
    : m_nextSpawnX(0.0f) {
}

void LevelGenerator::generate(float deltaTime, std::vector<std::unique_ptr<Object>>& objects, float playerX) {
    (void)deltaTime;

    float currentSpawnZoneX = playerX + 1400.0f;

    if (m_nextSpawnX == 0.0f) {
        m_nextSpawnX = currentSpawnZoneX;
    }

    if (currentSpawnZoneX >= m_nextSpawnX) {
        float spawnX = m_nextSpawnX;
        float generationWidth = 0.0f;

        // 60% coins / 40% lasers
        int eventChoice = rand() % 10;

        if (eventChoice < 6) {
            
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
            case 2: { // WAVE
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
            case 4: { // CIRCLE
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
            
            float laserX = spawnX + 200.0f;
            const float LASER_RADIUS = 175.0f;

            float minLaserY = CEILING_LIMIT + LASER_RADIUS;
            float maxLaserY = FLOOR_LIMIT - LASER_RADIUS;

            if (maxLaserY < minLaserY) maxLaserY = minLaserY;
            float laserY = minLaserY + static_cast<float>(rand() % static_cast<int>(maxLaserY - minLaserY + 1));

            objects.push_back(GameObjectFactory::createObject("Laser", { laserX, laserY }));

            generationWidth = 400.0f;
        }

        //space between every objects
        float separationPadding = 500.0f + static_cast<float>(rand() % 600);
        m_nextSpawnX = spawnX + generationWidth + separationPadding;
    }
}