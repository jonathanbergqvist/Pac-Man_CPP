#pragma once

#include "Main.h"

class PacMan {
public:
	int pacmanX = 14;
	int pacmanY = 20;

	void changePacManDirection(char grid[GRID_Y][GRID_X]);
	bool movePacMan(char grid[GRID_Y][GRID_X]);
};