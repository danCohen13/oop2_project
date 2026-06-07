#pragma once

class Laser;
class Player;

class LaserState {
public:
    virtual ~LaserState() = default;
    virtual void update(Laser& laser, float deltaTime) = 0;
    virtual void collide(Player& player) = 0;
};