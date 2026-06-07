#pragma once
#include "LaserState.h"
#include "Laser.h"
#include "Player.h"

class LaserStaticState : public LaserState {
public:
    virtual void update(Laser& laser, float deltaTime) override {
        // 1. On remet la couleur normale (opaque)
        laser.getSprite().setColor(sf::Color::White);

        // 2. Animation rapide du plasma (Toutes les 0.05s) via ton vecteur m_laserFrames
        laser.animatePlasma(deltaTime);

        // La méthode rotate() est absente ici : l'angle du laser reste figé !
    }

    virtual void collide(Player& player) override {
        player.setDead(true); // Mort instantanée !
    }
};