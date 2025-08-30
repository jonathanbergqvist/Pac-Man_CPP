#include "GUI.h"
#include "TextureHandler.h"

TextureHandler textures = TextureHandler();

GUI::GUI(TextureHandler& fetchedTextures) {
    textures = fetchedTextures;
    // Create the game window.
    window.create(sf::VideoMode(textures.getTexture(TextureHandler::ASSETS::MAP).getSize()), "PacMan from RizeCookie");
	window.setFramerateLimit(60); // Limit to 60 FPS
};

TextureHandler& GUI::getTextures() {
    return textures;
}

void GUI::drawBackground() {
    std::optional<sf::Sprite> backgroundSprite = textures.getSprite(TextureHandler::ASSETS::MAP);
    if (backgroundSprite.has_value()) {
        window.draw(*backgroundSprite); // Dereferencing std::optional, to get the sprite.
    }
}

void GUI::drawPacMan(PacMan pacman) {
    std::optional<sf::Sprite> pacmanSprite = textures.getSprite(pacman.PAC_MAN_TEXTURE);
    if (pacmanSprite.has_value()) {
        (*pacmanSprite).setPosition({ (pacman.pacmanX * 20.f), (pacman.pacmanY * 20.f) });
        window.draw(*pacmanSprite); // Dereferencing std::optional, to get the sprite.
    }
}

void GUI::drawSingleGhost(Ghost& ghost) {
    std::optional<sf::Sprite> ghostSprite = textures.getSprite(ghost.CURRENT_GHOST_TEXTURE);
    if (ghostSprite.has_value()) {
        (*ghostSprite).setPosition({ (ghost.ghostX * 20.f), (ghost.ghostY * 20.f) });
        window.draw(*ghostSprite); // Dereferencing std::optional, to get the sprite.
    }
}

void GUI::drawPelletSmall(int positionX, int positionY) {
    std::optional<sf::Sprite> smallPelletSprite = textures.getSprite(TextureHandler::ASSETS::DOT_SMALL);
    if (smallPelletSprite.has_value()) {
        (*smallPelletSprite).setPosition({ (positionX * 20.f), (positionY * 20.f) });
        window.draw(*smallPelletSprite); // Dereferencing std::optional, to get the sprite.
    }
}

void GUI::drawPelletLarge(int positionX, int positionY) {
    std::optional<sf::Sprite> largePelletSprite = textures.getSprite(TextureHandler::ASSETS::DOT_BIG);
    if (largePelletSprite.has_value()) {
        (*largePelletSprite).setPosition({ (positionX * 20.f), (positionY * 20.f) });
        window.draw(*largePelletSprite); // Dereferencing std::optional, to get the sprite.
    }
}