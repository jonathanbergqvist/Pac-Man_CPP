#include "GUI.h"
#include "TextureHandler.h"

TextureHandler textures = TextureHandler();

GUI::GUI(TextureHandler& fetchedTextures) {
    textures = fetchedTextures;
    // Create the game window.
    window.create(sf::VideoMode(textures.getTexture(TextureHandler::ASSETS::MAP).getSize()), "PacMan from RizeCookie");
};

//void GUI::drawFrames(TextureHandler& textures) {
//    // Run the program as long as the window is open
//    while (window.isOpen())
//    {
//        // check all the window's events that were triggered since the last iteration of the loop
//        while (const std::optional event = window.pollEvent())
//        {
//            // "close requested" event: we close the window
//            if (event->is<sf::Event::Closed>())
//                window.close();
//        }
//
//        // Clear the window with black color
//        window.clear(sf::Color::Black);
//
//        // Draw base first, then overlay
//        std::optional<sf::Sprite> background = textures.getSprite(TextureHandler::ASSETS::MAP);
//        if (background.has_value()) {
//            window.draw(*background); // Dereferencing std::optional, to get the sprite.
//        }
//
//        std::optional<sf::Sprite> pacman = textures.getSprite(TextureHandler::ASSETS::PACMAN_RIGHT);
//        if (pacman.has_value()) {
//            (*pacman).setPosition({ 20, 20 });
//            window.draw(*pacman); // Dereferencing std::optional, to get the sprite.
//        }
//
//        // end the current frame
//        window.display();
//    }
//
//}

TextureHandler& GUI::getTextures() {
    return textures;
}

void GUI::drawBackground() {
    // Check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    window.display();
    window.clear(sf::Color::Black);
    // Draw base first, then overlay
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