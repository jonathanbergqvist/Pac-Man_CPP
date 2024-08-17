#pragma once

#include <iostream>
#include "Main.h"

class PacMan {
public:
	int pacmanX = 14;
	int pacmanY = 20;

	bool movePacMan(char grid[GRID_Y][GRID_X]);
};