#pragma once
#include "StaticGameObject.h"

class Player; // Forward declaration pour la collision

class Laser : public StaticGameObject {
public:
    // Le constructeur requis par GameObjectFactory
    explicit Laser(const sf::Vector2f& position);
    virtual ~Laser() override = default;

    // Implémentation des fonctions virtuelles pures de la classe de base
    virtual void draw(sf::RenderWindow& window) const override;
    virtual void update(float deltaTime) override;
    virtual void collide(Object& other) override;

    // Surcharges de gameplay (Double Dispatch & Cycle de vie)
    virtual void collide(Player& player) override;
    virtual bool isDisposed() const override;

private:
    bool m_isDisposed = false;
};