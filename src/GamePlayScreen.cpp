#include "GameplayScreen.h"
#include "Resources.h"

GameplayScreen::GameplayScreen(ScreenStack& stack)
    : Screen(stack),
    m_board(),
    // Explicitly initialize sprites with the required background texture reference
    m_backgrounds{ sf::Sprite(Resources::getInstance().getTexture("background")),
                  sf::Sprite(Resources::getInstance().getTexture("background")) } {
    m_backgrounds[0].setPosition({ 0.0f, 0.0f });
    m_backgrounds[1].setPosition({ SCREEN_WIDTH, 0.0f });
}

void GameplayScreen::handleEvent(const sf::Event& event) {
    // Safe extraction of key pressed properties in SFML 3.0
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            m_stack.pop();
        }
    }
}

void GameplayScreen::update(float deltaTime) {
    if (!m_board.isPlayerAlive()) return;

    // SFML 3.0 scoped key extraction hierarchy
    bool isThrusting = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    m_board.play(m_window, deltaTime, isThrusting);

    float viewLeft = m_board.getPlayerPosition().x - SCREEN_WIDTH / 3.0f;
    for (int i = 0; i < 2; ++i) {
        float bgRight = m_backgrounds[i].getPosition().x + m_backgrounds[i].getGlobalBounds().size.x;
        if (viewLeft >= bgRight) {
            m_backgrounds[i].move({ 2.0f * SCREEN_WIDTH, 0.0f });
        }
    }
}

void GameplayScreen::draw(sf::RenderWindow& window) {
    window.draw(m_backgrounds[0]);
    window.draw(m_backgrounds[1]);
    m_board.draw(window);
}