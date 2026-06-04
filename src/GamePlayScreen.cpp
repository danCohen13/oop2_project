#include "GameplayScreen.h"
#include "Resources.h"
#include <cmath>

GameplayScreen::GameplayScreen(ScreenStack& stack)
    : Screen(stack), m_board()
{
    const sf::Texture& bgTex = Resources::getInstance().getTexture("background");

    float scaleFactor = SCREEN_HEIGHT / static_cast<float>(bgTex.getSize().y);
    float bgWidth = static_cast<float>(bgTex.getSize().x) * scaleFactor;

    int tilesNeeded = static_cast<int>(std::ceil(SCREEN_WIDTH / bgWidth)) + 1;
    if (tilesNeeded < 2) tilesNeeded = 2;

    for (int i = 0; i < tilesNeeded; ++i) {
        m_backgrounds.emplace_back(bgTex);
        m_backgrounds[i].setScale({ scaleFactor, scaleFactor });
    }
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

    // CORRECTION : Appel harmonisé à 2 paramètres
    m_board.play(deltaTime, isThrusting);

    const sf::Texture& bgTex = Resources::getInstance().getTexture("background");
    float scaleFactor = SCREEN_HEIGHT / static_cast<float>(bgTex.getSize().y);
    float bgWidth = static_cast<float>(bgTex.getSize().x) * scaleFactor;

    float viewLeft = m_board.getPlayerPosition().x - SCREEN_WIDTH / 3.0f;
    float startX = std::floor(viewLeft / bgWidth) * bgWidth;

    for (size_t i = 0; i < m_backgrounds.size(); ++i) {
        m_backgrounds[i].setPosition({ startX + static_cast<float>(i) * bgWidth, 0.0f });
    }
}

void GameplayScreen::draw(sf::RenderWindow& window) {
    sf::View camera = window.getDefaultView();
    float cameraX = m_board.getPlayerPosition().x + (SCREEN_WIDTH / 6.0f);
    camera.setCenter({ cameraX, SCREEN_HEIGHT / 2.0f });
    window.setView(camera);

    for (const auto& bg : m_backgrounds) {
        window.draw(bg);
    }

    m_board.draw(window);

    window.setView(window.getDefaultView());
}