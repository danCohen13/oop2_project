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
    float m_laserTimer;
};