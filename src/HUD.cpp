#include "HUD.h"
#include <iostream>

HUD::HUD()
    : m_font(),
    m_scoreText(m_font, ""),
    m_livesText(m_font, "")
{
    if (!m_font.openFromFile("resources/New Athletic M54.ttf")) {
        std::cerr << "Error: Impossible to charge the police for the HUD.\n";
    }

    m_scoreText.setCharacterSize(30);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition({ 20.f, 20.f });

    m_livesText.setCharacterSize(30);
    m_livesText.setFillColor(sf::Color::Red);
    m_livesText.setPosition({ 20.f, 60.f });

    updateTexts(0, 3);
}

void HUD::updateTexts(int score, int lives) {
    m_scoreText.setString("Score: " + std::to_string(score));
    m_livesText.setString("Vies: " + std::to_string(lives));
}

void HUD::draw(sf::RenderWindow& window) const {
    window.draw(m_scoreText);
    window.draw(m_livesText);
}