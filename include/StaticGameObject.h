#pragma once
#include "Object.h"

class StaticGameObject : public Object {
public:
    using Object::Object;
    virtual ~StaticGameObject() = default;
    virtual void update(float deltaTime) override = 0;
};