#pragma once

#include <iostream>
#include <vector>
#include "Main.h"

class Ghost {
public:
    const char GHOST_COLOUR_CHASED = 'b'; // Blue
    const char GHOST_CHAR = 'G';

    char GHOST_COLOUR;
    char currentPositionChar = '.';

    int ghostX = 4;
    int ghostY = 1;

    Ghost(char colour);

    void moveGhost(int pacmanX, int pacmanY, char grid[GRID_Y][GRID_X]);
    void escapePacMan();

    static int manhattanDistance(int x1, int y1, int x2, int y2);
};