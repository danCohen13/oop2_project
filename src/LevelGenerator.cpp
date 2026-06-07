#include "LevelGenerator.h"
#include "GameObjectFactory.h" // Nécessaire pour instancier les objets polymorphiques
#include <cstdlib>

LevelGenerator::LevelGenerator()
    : m_coinTimer(2.0f), m_laserTimer(4.0f) {
}

void LevelGenerator::generate(float deltaTime, std::vector<std::unique_ptr<Object>>& objects, float playerX) {
    m_coinTimer -= deltaTime;
    m_laserTimer -= deltaTime;

    // ========================================================================
    // 1. GESTION DES GROUPES DE PIÈCES (LOGIQUE DE PATTERNS)
    // ========================================================================
    if (m_coinTimer <= 0.0f) {
        // Point d'ancrage initial (Ancrage X hors-écran à droite, Y aléatoire encadré)
        float spawnX = playerX + 1300.0f;
        float spawnY = static_cast<float>(100 + rand() % 350); // Reste entre le sol et le plafond

        // Choisir une forme au hasard (0 = Ligne horizontale, 1 = Bloc carré 3x3)
        int patternType = rand() % 2;

        if (patternType == 0) {
            // Pattern A : Créer une ligne horizontale de 5 pièces individuelles espacées
            for (int i = 0; i < 5; ++i) {
                float coinX = spawnX + (static_cast<float>(i) * 40.0f);

                // On passe la coordonnée calculée directement à l'usine générique
                objects.push_back(GameObjectFactory::createObject("Coin", { coinX, spawnY }));
            }
        }
        else if (patternType == 1) {
            // Pattern B : Créer un bloc carré de 3x3 pièces individuelles espacées
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    float coinX = spawnX + (static_cast<float>(col) * 40.0f);
                    float coinY = spawnY + (static_cast<float>(row) * 40.0f);

                    objects.push_back(GameObjectFactory::createObject("Coin", { coinX, coinY }));
                }
            }
        }

        // Relancer le timer pour le prochain groupe de pièces (entre 3 et 7 secondes)
        m_coinTimer = static_cast<float>(3 + rand() % 5);
    }

    // ========================================================================
    // 2. GESTION DES LASERS (CONSERVÉE ACTIVE)
    // ========================================================================
    if (m_laserTimer <= 0.0f) {
        float laserX = playerX + 1500.0f;
        float laserY = static_cast<float>(100 + rand() % 400);

        objects.push_back(GameObjectFactory::createObject("Laser", { laserX, laserY }));

        m_laserTimer = static_cast<float>(4 + rand() % 6);
    }
}