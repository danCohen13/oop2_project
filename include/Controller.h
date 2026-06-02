#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Controller {
public:
    Controller();
    ~Controller() = default;

    // Main application game loop execution
    void run();

private:
    // Handles infinite loop parallax backdrop translation
    void moveBackground(float deltaTime);

    // Renders static interface elements text overlay
    void drawData();

    sf::RenderWindow m_window;
    Board m_board;
    sf::Clock m_clock;

    float m_deltaTime;
    float m_gameTime;

    sf::Sprite m_backgrounds[2];
    sf::Text m_uiText;
    sf::Font m_font;

    // View boundaries configuration constants
    const sf::Vector2f SCREEN_SIZE = { 1200.0f, 600.0f };
};