#include "ObjectCleaner.h"
#include <algorithm>

void ObjectCleaner::cleanup(std::vector<std::unique_ptr<Object>>& objects, float playerX) {
    // Calcul de la bordure gauche invisible de la caméra
    float cullX = playerX - 400.0f;

    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [cullX](const std::unique_ptr<Object>& obj) {
                return (obj->getPosition().x + obj->getGlobalBounds().size.x) < cullX;
            }),
        objects.end()
    );
}