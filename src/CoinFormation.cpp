#include "CoinFormation.h"
#include "GameObjectFactory.h"
#include <cmath>
#include <cstdlib>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// NE PAS TOUCHER - PARFAIT
void CoinFormation::createLine(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int length, int thickness) {
    for (int r = 0; r < thickness; ++r) {
        for (int c = 0; c < length; ++c) {
            float x = startX + (c * spacing);
            float y = startY + (r * spacing);
            objects.push_back(GameObjectFactory::createObject("Coin", { x, y }));
        }
    }
}

// NE PAS TOUCHER - PARFAIT
void CoinFormation::createDiagonal(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int length) {
    for (int i = 0; i < length; ++i) {
        objects.push_back(GameObjectFactory::createObject("Coin", { startX + (i * spacing), startY + (i * spacing) }));
    }
}

// MODIFIÉ : Forme du Serpent (Vague) aérée
void CoinFormation::createWave(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int length) {
    float frequency = 0.35f;
    float amplitude = spacing * 1.4f;
    float horizontalSpacing = spacing * 1.3f; // Plus d'espace horizontal pour étirer le serpent

    for (int i = 0; i < length; ++i) {
        float x = startX + (i * horizontalSpacing);
        float y = startY + (amplitude * std::sin(i * frequency));
        objects.push_back(GameObjectFactory::createObject("Coin", { x, y }));
    }
}

// NE PAS TOUCHER - PARFAIT
void CoinFormation::createTriangle(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int size) {
    for (int r = 0; r < size; ++r) {
        float y = startY + (r * spacing);
        float levelStartX = startX - (r * spacing / 2.0f);
        int coinsInRow = r + 1;

        for (int c = 0; c < coinsInRow; ++c) {
            objects.push_back(GameObjectFactory::createObject("Coin", { levelStartX + (c * spacing), y }));
        }
    }
}

// MODIFIÉ : Forme du Cercle désengorgée
void CoinFormation::createCircle(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int radiusFactor) {
    // On augmente légèrement le rayon pour donner du souffle aux pièces
    float radius = spacing * (static_cast<float>(radiusFactor) + 0.4f);

    // 8 pièces forment un anneau circulaire parfait à l'écran sans chevauchement
    int steps = 8;

    for (int i = 0; i < steps; ++i) {
        float radians = (i * 2.0f * static_cast<float>(M_PI)) / steps;
        float x = startX + radius * std::cos(radians);
        float y = startY + radius * std::sin(radians);
        objects.push_back(GameObjectFactory::createObject("Coin", { x, y }));
    }
}