#pragma once
#include "Screen.h"
#include "Board.h"
#include <vector>

class GameplayScreen : public Screen {
public:
    GameplayScreen(ScreenStack& stack);

    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(float deltaTime) override;
    virtual void draw(sf::RenderWindow& window) override;

private:
    Board m_board;
    std::vector<sf::Sprite> m_backgrounds;

    const float SCREEN_WIDTH = 1200.0f;
    const float SCREEN_HEIGHT = 600.0f; // <-- AJOUTEZ CETTE LIGNE ICI
};