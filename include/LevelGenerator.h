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

    const float COIN_SPACING = 48.0f;

    const float CEILING_LIMIT = 50.0f;  
    const float FLOOR_LIMIT = 530.0f;   
};