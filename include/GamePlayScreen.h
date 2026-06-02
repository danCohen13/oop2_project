#pragma once
#include "Screen.h"
#include "Board.h"

class GameplayScreen : public Screen {
public:
    GameplayScreen(ScreenStack& stack);

    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(float deltaTime) override;
    virtual void draw(sf::RenderWindow& window) override;

private:
    Board m_board;
    sf::Sprite m_backgrounds[2];

    const float SCREEN_WIDTH = 1200.0f;
};