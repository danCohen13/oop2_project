#pragma once
#include "Object.h"

class MovingGameObject : public Object {
public:
    MovingGameObject(float speed);
    virtual ~MovingGameObject() = default;

    // Handles standard linear horizontal movement
    virtual void move(float deltaTime);

    // Main update loop for physics and logic changes
    virtual void update(float deltaTime) = 0;

    float getSpeed() const;
    void setSpeed(float speed);

protected:
    float m_speed;
};