#pragma once
#include <SFML/Graphics.hpp>

#include "Main.h"
#include "TextureHandler.h"

class PacMan {
public:
	int pacmanX;
	int pacmanY;

	TextureHandler::ASSETS PAC_MAN_TEXTURE = TextureHandler::ASSETS::PACMAN_RIGHT;

	void changePacManDirection(char grid[GRID_Y][GRID_X]);
	bool movePacMan(char grid[GRID_Y][GRID_X], double deltaTime);

	PacMan();
    double moveAccumulator = 0.0;
};