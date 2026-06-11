#include "CoinFormation.h"
#include "GameObjectFactory.h"
#include <cmath>
#include <cstdlib>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void CoinFormation::createLine(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int length, int thickness) {
    for (int r = 0; r < thickness; ++r) {
        for (int c = 0; c < length; ++c) {
            float x = startX + (c * spacing);
            float y = startY + (r * spacing);
            objects.push_back(GameObjectFactory::createObject("Coin", { x, y }));
        }
    }
}

void CoinFormation::createDiagonal(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int length) {
    for (int i = 0; i < length; ++i) {
        objects.push_back(GameObjectFactory::createObject("Coin", { startX + (i * spacing), startY + (i * spacing) }));
    }
}

void CoinFormation::createWave(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int length) {
    float frequency = 0.35f;
    float amplitude = spacing * 1.4f;
    float horizontalSpacing = spacing * 1.3f;

    for (int i = 0; i < length; ++i) {
        float x = startX + (i * horizontalSpacing);
        float y = startY + (amplitude * std::sin(i * frequency));
        objects.push_back(GameObjectFactory::createObject("Coin", { x, y }));
    }
}

void CoinFormation::createTriangle(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int size) {
    for (int r = 0; r < size; ++r) {
        float y = startY + (r * spacing);

        int coinsInRow = r + 1;
        float rowWidth = (coinsInRow - 1) * spacing;
        float levelStartX = startX - (rowWidth / 2.0f);

        for (int c = 0; c < coinsInRow; ++c) {
            objects.push_back(GameObjectFactory::createObject("Coin", { levelStartX + (c * spacing), y }));
        }
    }
}

void CoinFormation::createCircle(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, float spacing, int radiusFactor) {
    float radius = spacing * (static_cast<float>(radiusFactor) + 0.4f);
    int steps = 8;

    for (int i = 0; i < steps; ++i) {
        float radians = (i * 2.0f * static_cast<float>(M_PI)) / steps;
        float x = startX + radius * std::cos(radians);
        float y = startY + radius * std::sin(radians);
        objects.push_back(GameObjectFactory::createObject("Coin", { x, y }));
    }
}