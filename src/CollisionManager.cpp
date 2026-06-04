#include "CollisionManager.h"
#include <algorithm>

void CollisionManager::handleCollisions(Player& player, std::vector<std::unique_ptr<Object>>& objects) {
    sf::FloatRect playerBounds = player.getGlobalBounds();

    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [&player, playerBounds](const std::unique_ptr<Object>& obj) {
                // Détection SFML 3.0 via findIntersection
                if (playerBounds.findIntersection(obj->getGlobalBounds()).has_value()) {
                    player.collide(*obj); // Double Dispatch
                    return obj->isDisposed(); // Supprime l'objet s'il a été ramassé/détruit
                }
                return false;
            }),
        objects.end()
    );
}