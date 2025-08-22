#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureHandler {
public:
    enum class ASSETS { 
        MAP, PACMAN_RIGHT, GHOST_BLUE_SCARED, GHOST_PINK, GHOST_RED, GHOST_CYAN, GHOST_ORANGE, 
        EYES_UP, EYES_DOWN, EYES_LEFT, EYES_RIGHT, DOT_SMALL, DOT_BIG
    };


    TextureHandler(); // Constructor

    // Load a texture and create a sprite
    bool loadTexture(const ASSETS name, const std::string& filename);
    std::optional<sf::Sprite> getSprite(const ASSETS name) const;
    const sf::Texture& getTexture(const ASSETS name) const;
    sf::Vector2u gridSize;

private:
    std::map<ASSETS, sf::Texture> textures;

};