#include "GameplayScreen.h"
#include <cmath>

GameplayScreen::GameplayScreen(ScreenStack& stack)
    : Screen(stack),
    m_board(),
    m_backgroundSystem(SCREEN_WIDTH, SCREEN_HEIGHT)
{
}

void GameplayScreen::handleEvent(const sf::Event& event) {
    if (m_inputHandler.isEscapePressed(event)) {
        m_stack.pop();
    }
}

void GameplayScreen::update(float deltaTime) {
    if (!m_board.isPlayerAlive()) return;

    bool isThrusting = m_inputHandler.isThrustingActive();

    m_board.play(deltaTime, isThrusting);
    m_backgroundSystem.update(deltaTime, m_board.getPlayerPosition().x);
}

void GameplayScreen::draw(sf::RenderWindow& window) {
    sf::View camera = window.getDefaultView();
    float cameraX = m_board.getPlayerPosition().x + (SCREEN_WIDTH / 3.0f);

    if (cameraX < SCREEN_WIDTH / 2.0f) {
        cameraX = SCREEN_WIDTH / 2.0f;
    }

    camera.setCenter({ std::round(cameraX), std::round(SCREEN_HEIGHT / 2.0f) });
    window.setView(camera);

    m_backgroundSystem.draw(window);
    m_board.draw(window);

    window.setView(window.getDefaultView());
}