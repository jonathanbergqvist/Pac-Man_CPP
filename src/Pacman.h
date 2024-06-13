#pragma once

#include <iostream>
#include "Main.h"

class PacMan {
public:
	static const char PACMAN_CHAR = 'C';
	static const char PACMAN_COLOUR = 'y';
	static const char EMPTY = ' ';

	int pacmanX = GRID_X / 2 - 2;
	int pacmanY = GRID_Y / 2;

	bool movePacMan(char grid[GRID_Y][GRID_X]);

};