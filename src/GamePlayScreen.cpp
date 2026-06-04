#include "GameplayScreen.h"
#include <cmath>
#include <algorithm>

GameplayScreen::GameplayScreen(ScreenStack& stack)
    : Screen(stack),
    m_board(),
    m_backgroundSystem(SCREEN_WIDTH, SCREEN_HEIGHT)
{
}

void GameplayScreen::handleEvent(const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            m_stack.pop();
        }
    }
}

void GameplayScreen::update(float deltaTime) {
    if (!m_board.isPlayerAlive()) return;

    bool isThrusting = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    m_board.play(deltaTime, isThrusting);

    // Transmission de la position X du joueur au gestionnaire de décor
    m_backgroundSystem.update(deltaTime, m_board.getPlayerPosition().x);
}

void GameplayScreen::draw(sf::RenderWindow& window) {
    sf::View camera = window.getDefaultView();

    // Positionnement de la caméra (le joueur reste calé sur la gauche)
    float cameraX = m_board.getPlayerPosition().x + (SCREEN_WIDTH / 3.0f);

    // SÉCURITÉ DE DÉMARRAGE : Empêche la caméra de voir à gauche de la coordonnée 0 au tout début
    if (cameraX < SCREEN_WIDTH / 2.0f) {
        cameraX = SCREEN_WIDTH / 2.0f;
    }

    camera.setCenter({ std::round(cameraX), std::round(SCREEN_HEIGHT / 2.0f) });
    window.setView(camera);

    // 1. Rendu du décor géré par son système dédié
    m_backgroundSystem.draw(window);

    // 2. Rendu des obstacles et du joueur
    m_board.draw(window);

    window.setView(window.getDefaultView());
}