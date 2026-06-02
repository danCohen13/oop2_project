#pragma once
#include "Object.h"

class StaticGameObject : public Object {
public:
    StaticGameObject() = default;
    virtual ~StaticGameObject() = default;

    // Open for passive animations (e.g., rotating coins)
    virtual void update(float deltaTime) = 0;
};