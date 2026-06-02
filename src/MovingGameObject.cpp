#include "MovingGameObject.h"

MovingGameObject::MovingGameObject(float speed)
    : m_speed(speed) {
}

void MovingGameObject::move(float deltaTime) {
    // Moves the entity forward along the X axis
    m_sprite.move({ m_speed * deltaTime, 0.0f });
}

float MovingGameObject::getSpeed() const {
    return m_speed;
}

void MovingGameObject::setSpeed(float speed) {
    m_speed = speed;
}