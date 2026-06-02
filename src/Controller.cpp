#include "Controller.h"
#include <string>

Controller::Controller()
    : m_window(sf::VideoMode(1200, 600), "Jetpack Joyride"),
    m_board(),
    m_deltaTime(0.0f),
    m_gameTime(0.0f) {

    // Hardware and resources asset binding goes here (e.g., loading textures)

    // Set up consecutive initial background positions
    m_backgrounds[0].setPosition({ 0.0f, 0.0f });
    m_backgrounds[1].setPosition({ SCREEN_SIZE.x, 0.0f });
}

void Controller::run() {
    m_clock.restart();

    while (m_window.isOpen() && m_board.isPlayerAlive()) {
        m_window.clear(sf::Color::Black);

        // Extract slice delta-time between frames
        m_deltaTime = m_clock.restart().asSeconds();
        m_gameTime += m_deltaTime;

        // Advance simulation mechanics and resolve double dispatch collisions
        m_board.play(m_window, m_deltaTime);

        // Adjust camera viewport to follow player position with a 1/3 screen offset offset anchor
        auto currentView = m_window.getView();
        sf::Vector2f viewCenter = currentView.getCenter();
        viewCenter.x = m_board.getPlayerPosition().x + SCREEN_SIZE.x / 3.0f;
        m_window.setView(sf::View(viewCenter, currentView.getSize()));

        // Process infinite layout parallax backdrop updates
        moveBackground(m_deltaTime);

        // Render operational game entities
        m_board.draw(m_window);

        // Apply GUI layers over base frames
        drawData();

        // Handle operating system base event message pooling
        if (auto event = sf::Event(); m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }

        m_window.display();
    }
}

void Controller::moveBackground(float deltaTime) {
    float viewLeftBound = m_window.getView().getCenter().x - SCREEN_SIZE.x / 2.0f;

    for (int i = 0; i < 2; ++i) {
        m_window.draw(m_backgrounds[i]);

        float backgroundRightEdge = m_backgrounds[i].getGlobalBounds().left + m_backgrounds[i].getGlobalBounds().width;

        // Shift graphic backdrop slice forward once fully cleared from left visibility window
        if (viewLeftBound >= backgroundRightEdge) {
            m_backgrounds[i].move({ 2.0f * SCREEN_SIZE.x, 0.0f });
        }
    }
}

void Controller::drawData() {
    auto currentView = m_window.getView();

    // Freeze rendering view back to window default to draw static un-scrolled elements
    m_window.setView(m_window.getDefaultView());

    // Render strings counters details
    m_uiText.setString("TIME: " + std::to_string(static_cast<int>(m_gameTime)));
    m_window.draw(m_uiText);

    // Swap active context back to original moving camera matrix coordinates
    m_window.setView(currentView);
}