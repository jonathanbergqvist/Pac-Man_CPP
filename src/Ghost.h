#pragma once
#include <string>
#include <vector>
#include "Main.h"

// Enum to represent ghost modes
enum class MODE { Chase, Scatter, Frightened, Start };
enum class COLOUR { Orange, Red, Pink, Cyan };
static std::pair<int, int> START_POSITION = { 13, 9 };

class Ghost {
    std::pair<int, int> scatterMove(char grid[GRID_Y][GRID_X]); // Move randomly
    std::pair<int, int> frightenedMove(char grid[GRID_Y][GRID_X]); // Escape PacMan
    std::pair<int, int> chaseMove(int pacmanX, int pacmanY, char grid[GRID_Y][GRID_X]); // Chase after PacMan
    std::pair<int, int> startMove(int targetX, int targetY, char grid[GRID_Y][GRID_X]); // To get outside the ghost box.

    std::vector<std::pair<int, int>> POSSIBLE_MOVES = {
        {ghostX + 1, ghostY},	// Right
        {ghostX - 1, ghostY},	// Left
        {ghostX, ghostY + 1},	// Down
        {ghostX, ghostY - 1}	// Up
    };

    void updatePossibleMovesCoordinates();
    double moveAccumulator = 0.0;

public:
    COLOUR ghostColour;
    MODE currentMode;
    char currentPositionChar;
    TextureHandler::ASSETS DEFAULT_GHOST_TEXTURE;
    TextureHandler::ASSETS CURRENT_GHOST_TEXTURE;

    std::string colourEnumToString(COLOUR value);
    std::string modeEnumToString(MODE value);

    int ghostX = 4;
    int ghostY = 1;

    int blueGhostTimeLeft = 0;
    int chaseTimeLeft = 0;

    Ghost(COLOUR colour); // Constructor assigning a colour and colour properties to the ghost.

    void changeMode(MODE mode);

    void moveGhost(int pacmanX, int pacmanY, char grid[GRID_Y][GRID_X], double deltaTime);

    static int manhattanDistance(int x1, int y1, int x2, int y2);
};