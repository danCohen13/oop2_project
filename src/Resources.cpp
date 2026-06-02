#include "Resources.h"

Resources& Resources::getInstance() {
    static Resources instance;
    return instance;
}

void Resources::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture tex;
    if (tex.loadFromFile(filename)) {
        m_textures[name] = tex;
    }
}

void Resources::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filename)) {
        m_sounds[name] = buffer;
    }
}

void Resources::loadFont(const std::string& filename) {
    // SFML 3.0 uses openFromFile for fonts
    m_font.openFromFile(filename);
}

const sf::Texture& Resources::getTexture(const std::string& name) const {
    return m_textures.at(name);
}

const sf::SoundBuffer& Resources::getSound(const std::string& name) const {
    return m_sounds.at(name);
}

const sf::Font& Resources::getFont() const {
    return m_font;
}