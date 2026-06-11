#pragma once
#include "PlayerState.h"

class WalkState : public PlayerState {
public:
    WalkState();
    void update(Player& player, float deltaTime) override;
    void draw(sf::RenderWindow& window,
        const sf::Sprite& playerSprite,
        const sf::Sprite& flameSprite,
        bool isThrusting) const override;

private:
    int m_currentFrame;
    float m_frameTimer;
    const float FRAME_DURATION = 0.1f;
};