#include "TextureHandler.h"
#include <optional>

TextureHandler::TextureHandler() {
    // Preload textures
    loadTexture(ASSETS::MAP, "Images/MapGrid.png");
    loadTexture(ASSETS::PACMAN_RIGHT, "Images/PacMan_Right.png");
    loadTexture(ASSETS::GHOST_BLUE_SCARED, "Images/Ghost_Blue_Scared.png");
    loadTexture(ASSETS::GHOST_CYAN, "Images/Ghost_Cyan.png");
    loadTexture(ASSETS::GHOST_ORANGE, "Images/Ghost_Orange.png");
    loadTexture(ASSETS::GHOST_ORANGE, "Images/Ghost_Pink.png");
    loadTexture(ASSETS::GHOST_RED, "Images/Ghost_Red.png");
    loadTexture(ASSETS::EYES_DOWN, "Images/Ghost_Eyes_Down.png");
    loadTexture(ASSETS::EYES_LEFT, "Images/Ghost_Eyes_Left.png");
    loadTexture(ASSETS::EYES_RIGHT, "Images/Ghost_Eyes_Right.png");
    loadTexture(ASSETS::EYES_UP, "Images/Ghost_Eyes_Up.png");
    loadTexture(ASSETS::DOT_BIG, "Images/Dot_Large.png");
    loadTexture(ASSETS::DOT_SMALL, "Images/Dot_Small.png");

    gridSize = getTexture(ASSETS::MAP).getSize();

}

bool TextureHandler::loadTexture(const ASSETS name, const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        return false;
    }
    textures[name] = std::move(texture);
    return true;
}

std::optional<sf::Sprite> TextureHandler::getSprite(const ASSETS name) const {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return sf::Sprite(it->second);
    }
    return std::nullopt; // Return null if not found
}

const sf::Texture& TextureHandler::getTexture(const ASSETS name) const {
    return textures.at(name); // Throws std::out_of_range if not found
}
