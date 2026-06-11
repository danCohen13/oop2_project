#include "JumpState.h"
#include "Player.h"
#include "Resources.h"

JumpState::JumpState() : m_currentFrame(0), m_frameTimer(0.0f) {}

void JumpState::update(Player& player, float deltaTime) {
    // 1. CORRECTION : On force le rectangle sur la DERNIÈRE frame (index 3)
    const sf::Texture& playerTex = Resources::getInstance().getTexture("player");
    int playerWidth = playerTex.getSize().x / 4;
    int playerHeight = playerTex.getSize().y;

    // En mettant 3 * playerWidth, SFML découpe exactement la 4ème image de la spritesheet
    player.getSprite().setTextureRect(sf::IntRect({ 3 * playerWidth, 0 }, { playerWidth, playerHeight }));

    // 2. Animation de la flamme uniquement si le Jetpack est actif
    if (player.isThrusting()) {
        m_frameTimer += deltaTime;
        if (m_frameTimer >= FRAME_DURATION) {
            m_frameTimer = 0.0f;
            m_currentFrame = (m_currentFrame + 1) % 4; // Animation cyclique de la flamme

            const sf::Texture& flameTex = Resources::getInstance().getTexture("Exhaust");
            int flameWidth = flameTex.getSize().x / 6; // Coupe sur les 6 flammes disponibles
            int flameHeight = flameTex.getSize().y;

            player.getFlameSprite().setTextureRect(sf::IntRect({ m_currentFrame * flameWidth, 0 }, { flameWidth, flameHeight }));
        }

        // Place of the exhaust under the jetpack 
        sf::Vector2f position = player.getPosition();
        player.getFlameSprite().setPosition({ position.x + 22.0f, position.y + 80.0f });
    }
}

void JumpState::draw(sf::RenderWindow& window, const sf::Sprite& playerSprite, const sf::Sprite& flameSprite, bool isThrusting) const {
    if (isThrusting) {
        window.draw(flameSprite); // Dessiné en premier pour passer à l'arrière-plan du joueur
    }
    window.draw(playerSprite);
}