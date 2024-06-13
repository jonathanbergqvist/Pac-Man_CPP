#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "Main.h"

// Enum to represent ghost modes
enum class Mode { Chase, Scatter, Frightened };
enum class Colour {Orange, Red, Pink, Cyan};

class Ghost {
    Colour ghostColour;
    std::pair<int, int> scatterMove(char grid[GRID_Y][GRID_X]); // Move randomly
    std::pair<int, int> frightenedMove(char grid[GRID_Y][GRID_X]); // Escape PacMan
    std::pair<int, int> chaseMove(int pacmanX, int pacmanY, char grid[GRID_Y][GRID_X]); // Chase after PacMan

    std::vector<std::pair<int, int>> possibleMoves = {
        {ghostX + 1, ghostY},	// Right
        {ghostX - 1, ghostY},	// Left
        {ghostX, ghostY + 1},	// Down
        {ghostX, ghostY - 1}	// Up
    };

    void updatePossibleMovesCoordinates();

public:
    //const char GHOST_COLOUR_CHASED = 'b'; // Blue
    const char GHOST_CHAR = 'G';
    Mode currentMode;
    char currentPositionChar = '.';

    int ghostX = 4;
    int ghostY = 1;

    int blueGhostTimeLeft = 0;
    int chaseTimeLeft = 0;

    Ghost(Colour colour);

    void changeMode(Mode mode);

    void moveGhost(int pacmanX, int pacmanY, char grid[GRID_Y][GRID_X]);

    static int manhattanDistance(int x1, int y1, int x2, int y2);
};