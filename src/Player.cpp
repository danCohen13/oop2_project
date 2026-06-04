#include "Player.h"
#include "Resources.h"

Player::Player()
    : MovingGameObject(Resources::getInstance().getTexture("player"), 300.0f),
    m_verticalVelocity(0.0f),
    m_isDead(false),
    m_flameSprite(Resources::getInstance().getTexture("Exhaust")),
    m_floorY(550.0f)
{
    m_sprite.setPosition({ 100.0f, 300.0f });

    // Découpage fixe du joueur (Lui possède bien 4 frames)
    const sf::Texture& playerTex = Resources::getInstance().getTexture("player");
    int playerWidth = playerTex.getSize().x / 4;
    int playerHeight = playerTex.getSize().y;
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { playerWidth, playerHeight }));

    m_floorY = 600.0f - static_cast<float>(playerHeight) - 20.0f;

    // ====================================================================
    // LA SOLUTION : Exhaust.png contient 6 flammes ! On divise donc par 6.
    // ====================================================================
    const sf::Texture& flameTex = Resources::getInstance().getTexture("Exhaust");
    int flameWidth = flameTex.getSize().x / 6; // <-- DIVISION PAR 6 ICI
    int flameHeight = flameTex.getSize().y;

    // Application du rectangle de texture de départ
    m_flameSprite.setTextureRect(sf::IntRect({ 0, 0 }, { flameWidth, flameHeight }));

    // ANCRE RIGIDE : On place l'origine au milieu du bord supérieur de la flamme
    m_flameSprite.setOrigin({ static_cast<float>(flameWidth) / 2.0f, 0.0f });
}

void Player::update(float deltaTime, bool isThrusting) {
    if (m_isDead) {
        m_drawFlame = false;
        return;
    }

    move(deltaTime);
    m_verticalVelocity += GRAVITY * deltaTime;

    if (isThrusting) {
        m_verticalVelocity = JETPACK_FORCE;
        m_drawFlame = true;
    }
    else {
        m_drawFlame = false;
    }

    m_sprite.move({ 0.0f, m_verticalVelocity * deltaTime });

    // Gestion des limites d'écran
    sf::Vector2f position = m_sprite.getPosition();
    if (position.y >= m_floorY) {
        m_sprite.setPosition({ position.x, m_floorY });
        m_verticalVelocity = 0.0f;
    }
    else if (position.y <= CEILING_Y) {
        m_sprite.setPosition({ position.x, CEILING_Y });
        m_verticalVelocity = 0.0f;
    }

    // ====================================================================
    // GESTION DES OFFSETS RIGIDES (Décalages manuels)
    // ====================================================================
    if (m_drawFlame) {
        // position.x et position.y correspondent au coin supérieur gauche du joueur.
        float offsetX = 20.0f;  // Éloigne la flamme vers la droite pour s'aligner au dos
        float offsetY = 80.0f;  // Descend la flamme tout en bas (sous les pieds du joueur)

        // Si la flamme est encore trop haute, passez offsetY à 90.0f ou 100.0f.
        m_flameSprite.setPosition({ position.x + offsetX, position.y + offsetY });
    }

    // Animation de course et de flamme
    m_frameTimer += deltaTime;
    if (m_frameTimer >= FRAME_DURATION) {
        m_frameTimer = 0.0f;
        m_currentFrame = (m_currentFrame + 1) % 4; // On boucle sur les 4 premières frames

        // 1. Découpage dynamique du joueur
        const sf::Texture& playerTex = Resources::getInstance().getTexture("player");
        int playerWidth = playerTex.getSize().x / 4;
        int playerHeight = playerTex.getSize().y;
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * playerWidth, 0 }, { playerWidth, playerHeight }));

        // 2. Découpage dynamique de la flamme
        if (m_drawFlame) {
            const sf::Texture& flameTex = Resources::getInstance().getTexture("Exhaust");
            int flameWidth = flameTex.getSize().x / 6; // <-- DIVISION PAR 6 ICI AUSSI
            int flameHeight = flameTex.getSize().y;

            // La flamme s'animera sur ses 4 premières frames, en rythme parfait avec le joueur
            m_flameSprite.setTextureRect(sf::IntRect({ m_currentFrame * flameWidth, 0 }, { flameWidth, flameHeight }));
        }
    }
}

void Player::draw(sf::RenderWindow& window) const {
    if (m_drawFlame) {
        window.draw(m_flameSprite);
    }
    window.draw(m_sprite);
}

void Player::collide(Object& other) {
    other.collide(*this);
}

bool Player::isDead() const { return m_isDead; }
void Player::setDead(bool dead) { m_isDead = dead; }