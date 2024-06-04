#pragma once

#include <iostream>
#include "Main.h"

class PacMan {
public:
    static const char PACMAN_CHAR = 'C';
    static const char PACMAN_COLOUR = 'y';
    static const char EMPTY = ' ';

    int pacmanX = 1;
    int pacmanY = 1;

    void movePacMan(char grid[GRID_Y][GRID_X]);

private:
    bool checkIfHitByGhost();
    bool checkIfHittingBlueGhost();
};