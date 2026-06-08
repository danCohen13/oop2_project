#include "Laser.h"
#include "Resources.h"
#include "Player.h"
#include "LaserStaticState.h"
#include "LaserRotatingState.h"
#include <cstdlib>
#include <cmath> // Requis pour std::sin

Laser::Laser(const sf::Vector2f& position)
    : StaticGameObject(Resources::getInstance().getTexture("Laser"), position, 4) // On charge la feuille de 4 frames
{
    // Configuration de la hitbox (ajustée à 30.f pour l'écartement désiré)
    m_hitbox.setSize({ 30.f, 350.f });
    m_hitbox.setOrigin({ 15.f, 175.f });
    m_hitbox.setPosition(position);

    // EFFET : On centre l'origine du sprite pour que la vibration se fasse par le milieu
    auto textureSize = m_sprite.getTexture().getSize();
    float frameWidth = static_cast<float>(textureSize.x) / 4.f;
    float frameHeight = static_cast<float>(textureSize.y);
    m_sprite.setOrigin({ frameWidth / 2.f, frameHeight / 2.f });

    // Initialisation de la première découpe de texture
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { static_cast<int>(frameWidth), static_cast<int>(frameHeight) }));

    // Angle de départ aléatoire
    float angle = static_cast<float>((rand() % 18) * 10);
    rotate(angle);

    if (rand() % 2 == 0)
        m_currState = std::make_unique<LaserStaticState>();
    else
        m_currState = std::make_unique<LaserRotatingState>();
}

void Laser::rotate(float angle) {
    m_sprite.rotate(sf::degrees(angle));
    m_hitbox.rotate(sf::degrees(angle));
}

void Laser::update(float deltaTime) {
    m_currState->rotate(this, deltaTime);

    m_animationTimer += deltaTime;
    m_vibrationTimer += deltaTime;

    // 1. Ralentissement de l'animation (Changement de frame plus doux)
    // On passe à 0.09 seconde pour que le mouvement du fluide soit naturel
    if (m_animationTimer >= 0.09f) {
        m_animationTimer = 0.0f;
        m_currentFrame = (m_currentFrame + 1) % 4;

        auto textureSize = m_sprite.getTexture().getSize();
        int frameWidth = textureSize.x / 4;
        int frameHeight = textureSize.y;

        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * frameWidth, 0 }, { frameWidth, frameHeight }));
    }

    // 2. Vibration adoucie et organique de la largeur
    // On réduit la fréquence (de 65.0f à 12.0f) pour créer une pulsation d'énergie fluide
    float wave = std::sin(m_vibrationTimer * 12.0f);

    // On restreint les variations de taille entre 92% et 108% de la largeur d'origine
    float targetScaleX = 1.0f + (wave * 0.08f);

    // On ajoute un micro-bruit très léger (seulement 2% d'instabilité) pour le grésillement
    float subtleNoise = 0.99f + static_cast<float>(rand() % 3) / 100.0f;

    // Application de l'échelle finale
    m_sprite.setScale({ targetScaleX * subtleNoise, 1.0f });
}

void Laser::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void Laser::collide(Object& other) {
    other.collide(*this);
}

void Laser::collide(Player& player) {
    sf::FloatRect playerBounds = player.getGlobalBounds();

    sf::Vector2f pointsToTest[5] = {
        playerBounds.position,
        { playerBounds.position.x + playerBounds.size.x, playerBounds.position.y },
        { playerBounds.position.x, playerBounds.position.y + playerBounds.size.y },
        playerBounds.position + playerBounds.size,
        playerBounds.position + playerBounds.size / 2.0f
    };

    sf::Transform inverseTransform = m_hitbox.getInverseTransform();
    sf::FloatRect localBounds = m_hitbox.getLocalBounds();

    bool realCollision = false;
    for (const auto& point : pointsToTest) {
        sf::Vector2f localPoint = inverseTransform.transformPoint(point);
        if (localBounds.contains(localPoint)) {
            realCollision = true;
            break;
        }
    }

    if (realCollision) {
        player.setDead(true);
    }
}

bool Laser::isDisposed() const {
    return m_isDisposed;
}