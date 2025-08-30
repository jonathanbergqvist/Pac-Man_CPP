#pragma once
#include <SFML/Graphics.hpp>

#include "TextureHandler.h"
#include "Pacman.h"
#include "Ghost.h"

class GUI {

public:

	GUI(TextureHandler& textureHandler);

	TextureHandler& getTextures();

	void drawBackground();
	void drawPelletSmall(int positionX, int positionY);
	void drawPelletLarge(int positionX, int positionY);
	void drawPacMan(PacMan pacman);
	void drawSingleGhost(Ghost& ghost);
	sf::RenderWindow window;

};
