#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Responsabilité unique : découper une spritesheet et animer frame par frame.
// Utilisé PAR COMPOSITION dans Player et StaticGameObject.
class SpriteAnimator {
public:
    // texture     : la spritesheet chargée
    // frameCount  : nombre de frames côte à côte horizontalement
    // frameDuration : secondes par frame (0.1 par défaut)
    SpriteAnimator(const sf::Texture& texture, int frameCount, float frameDuration = 0.1f);

    // Avance le timer et met à jour textureRect si besoin
    // Retourne true si la frame a changé (utile pour synchroniser la flamme du joueur)
    bool update(float deltaTime);

    // Applique la frame courante sur le sprite donné
    void applyTo(sf::Sprite& sprite) const;

    // Accès direct à la frame courante (pour synchroniser la flamme)
    int getCurrentFrame() const { return static_cast<int>(m_currentFrame); }

    // Largeur/hauteur d'une frame individuelle (utile pour setOrigin)
    sf::Vector2i getFrameSize() const;

private:
    std::vector<sf::IntRect> m_frames;
    size_t   m_currentFrame = 0;
    float    m_frameTimer = 0.0f;
    float    m_frameDuration;
};