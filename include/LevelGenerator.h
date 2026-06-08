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
    float m_nextSpawnX;

    // Espacement idéal pour un écran de 600px de haut
    const float COIN_SPACING = 65.0f;

    // ÉCRAN 1200 x 600 : Ajustement strict des limites visibles
    const float CEILING_LIMIT = 50.0f;  // Plafond du niveau
    const float FLOOR_LIMIT = 530.0f;   // Sol du niveau (ajuste à 540 ou 550 si ton sol est plus bas)
};