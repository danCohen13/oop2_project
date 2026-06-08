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
        int formationType = rand() % 5;

        float formationWidth = 0.0f;
        float spawnY = 0.0f;

        // CORRECTION GLOBALE : Les sprites ont leur origine centrée (setOrigin au milieu).
        // Toutes les bornes minY/maxY doivent donc inclure une marge de COIN_SPACING/2
        // pour éviter que les pièces dépassent le plafond ou le sol.
        const float HALF = COIN_SPACING / 2.0f;

        switch (formationType) {
        case 0: { // LIGNE
            int length = 8 + rand() % 6;
            int thickness = 1 + rand() % 3;

            // La rangée la plus basse est à spawnY + (thickness-1)*spacing
            // => sa pièce la plus basse touche spawnY + (thickness-1)*spacing + HALF
            float minY = CEILING_LIMIT + HALF;
            float maxY = FLOOR_LIMIT - ((thickness - 1) * COIN_SPACING) - HALF;

            if (maxY < minY) maxY = minY; // Sécurité si l'écran est trop petit
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

            CoinFormation::createLine(objects, spawnX, spawnY, COIN_SPACING, length, thickness);
            formationWidth = length * COIN_SPACING;
            break;
        }
        case 1: { // DIAGONALE
            int length = 4 + rand() % 3;

            // La pièce la plus basse est à spawnY + (length-1)*spacing
            float minY = CEILING_LIMIT + HALF;
            float maxY = FLOOR_LIMIT - ((length - 1) * COIN_SPACING) - HALF;

            if (maxY < minY) maxY = minY;
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

            CoinFormation::createDiagonal(objects, spawnX, spawnY, COIN_SPACING, length);
            formationWidth = length * COIN_SPACING;
            break;
        }
        case 2: { // VAGUE (SERPENT)
            int length = 12 + rand() % 6;
            float amplitude = COIN_SPACING * 1.4f;

            // spawnY est le centre de la vague; les pièces s'écartent de +/- amplitude
            float minY = CEILING_LIMIT + amplitude + HALF;
            float maxY = FLOOR_LIMIT - amplitude - HALF;

            if (maxY < minY) maxY = minY;
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

            CoinFormation::createWave(objects, spawnX, spawnY, COIN_SPACING, length);
            formationWidth = length * (COIN_SPACING * 1.7f); // Mis à jour avec l'espacement de 1.7f
            break;
        }
        case 3: { // TRIANGLE
            int size = 3 + rand() % 3;

            // La rangée la plus basse est à spawnY + (size-1)*spacing
            float minY = CEILING_LIMIT + HALF;
            float maxY = FLOOR_LIMIT - ((size - 1) * COIN_SPACING) - HALF;

            if (maxY < minY) maxY = minY;
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

            CoinFormation::createTriangle(objects, spawnX, spawnY, COIN_SPACING, size);
            formationWidth = size * COIN_SPACING;
            break;
        }
        case 4: { // CERCLE
            int radiusFactor = 2;
            float radius = COIN_SPACING * 3.0f; // Aligné sur le rayon mis à jour de 3.0f

            // Le centre du cercle est à spawnY; les pièces s'écartent de +/- radius
            float minY = CEILING_LIMIT + radius + HALF;
            float maxY = FLOOR_LIMIT - radius - HALF;

            if (maxY < minY) maxY = minY;
            spawnY = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY + 1));

            CoinFormation::createCircle(objects, spawnX, spawnY, COIN_SPACING, radiusFactor);
            formationWidth = radius * 2.0f;
            break;
        }
        }

        // Spawn laser indépendant des formations de pièces
        if (rand() % 3 == 0) { // 1 chance sur 3
            float laserX = spawnX + formationWidth + 400.0f;

            // Le laser mesurant 350px, son rayon de rotation depuis son centre est de 175px
            const float LASER_RADIUS = 175.0f;

            // Bornes de sécurité pour éviter que les extrémités du laser ne sortent de l'écran en tournant
            float minLaserY = CEILING_LIMIT + LASER_RADIUS;
            float maxLaserY = FLOOR_LIMIT - LASER_RADIUS;

            if (maxLaserY < minLaserY) maxLaserY = minLaserY;
            float laserY = minLaserY + static_cast<float>(rand() % static_cast<int>(maxLaserY - minLaserY + 1));

            objects.push_back(GameObjectFactory::createObject("Laser", { laserX, laserY }));
        }

        float separationPadding = 1800.0f + static_cast<float>(rand() % 1200);
        m_nextSpawnX = spawnX + formationWidth + separationPadding;
    }
}