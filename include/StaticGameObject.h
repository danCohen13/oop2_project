#pragma once
#include "Object.h"
#include "SpriteAnimator.h"   // ← nouveau

class StaticGameObject : public Object {
public:
    StaticGameObject(const sf::Texture& texture, const sf::Vector2f& position, int frameCount = 1);
    virtual ~StaticGameObject() override = default;
    virtual void update(float deltaTime) override;

protected:
    SpriteAnimator m_animator;   // ← remplace les 4 variables dupliquées
};