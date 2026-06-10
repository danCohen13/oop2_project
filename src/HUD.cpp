#include "HUD.h"
#include <iostream>

// CORRECTION SFML 3 : L'ordre exact est (m_font, "") et non pas ("", m_font) !
HUD::HUD()
    : m_font(),
    m_scoreText(m_font, ""),
    m_livesText(m_font, "")
{
    // Chargement de la police depuis ton dossier resources
    if (!m_font.openFromFile("resources/New Athletic M54.ttf")) {
        std::cerr << "Erreur: Impossible de charger la police pour le HUD.\n";
    }

    // Configuration du texte du Score
    m_scoreText.setCharacterSize(30);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition({ 20.f, 20.f });

    // Configuration du texte des Vies
    m_livesText.setCharacterSize(30);
    m_livesText.setFillColor(sf::Color::Red);
    m_livesText.setPosition({ 20.f, 60.f });

    // Remplissage initial des chaînes
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