#include "GameplayScreen.h"
#include <cmath>

GameplayScreen::GameplayScreen(ScreenStack& stack)
    : Screen(stack),
    m_session(),
    m_hud(),
    m_backgroundSystem(SCREEN_WIDTH, SCREEN_HEIGHT)
{
}

void GameplayScreen::handleEvent(const sf::Event& event) {
    if (m_inputHandler.isEscapePressed(event)) {
        m_stack.pop();
    }
}

void GameplayScreen::update(float deltaTime) {
    if (m_session.isGameOver()) return;

    bool isThrusting = m_inputHandler.isThrustingActive();

    m_session.update(deltaTime, isThrusting);

    m_hud.updateTexts(m_session.getScore(), m_session.getLives());

    m_backgroundSystem.update(deltaTime, m_session.getPlayerPosition().x);
}

void GameplayScreen::draw(sf::RenderWindow& window) {
    sf::View camera = window.getDefaultView();
    float cameraX = m_session.getPlayerPosition().x + (SCREEN_WIDTH / 3.0f);

    if (cameraX < SCREEN_WIDTH / 2.0f) {
        cameraX = SCREEN_WIDTH / 2.0f;
    }

    camera.setCenter({ std::round(cameraX), std::round(SCREEN_HEIGHT / 2.0f) });
    window.setView(camera);

    m_backgroundSystem.draw(window);
    m_session.drawWorld(window);

    
    window.setView(window.getDefaultView());
    m_hud.draw(window);
}