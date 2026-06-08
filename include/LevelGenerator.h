#pragma once
#include <vector>
#include <memory>
#include "Object.h"

class LevelGenerator {
public:
    LevelGenerator();
    ~LevelGenerator() = default;

    void generate(float deltaTime, std::vector<std::unique_ptr<Object>>& objects, float playerX);

private:
    float m_coinTimer;

    // Constante d'espacement entre deux pièces (en pixels)
    const float COIN_SPACING = 65.0f;

    // Générateurs de formes géométriques
    void spawnHorizontalLine(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, int count);
    void spawnBlock(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, int rows, int cols);
    void spawnWave(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY, int count);
    void spawnArrow(std::vector<std::unique_ptr<Object>>& objects, float startX, float startY);
};