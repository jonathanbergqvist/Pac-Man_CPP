#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"

Ghost::Ghost(char colour) : GHOST_COLOUR(colour) {
	// Constructor implementation for colored ghost
}

void Ghost::moveGhost(int pacmanX, int pacmanY, char grid[GRID_Y][GRID_X]) {
	// Move the ghost according to the colour of the ghost.

	// Calculate heuristic for each possible move
	std::vector<std::pair<int, int>> possibleMoves = {
		{ghostX + 1, ghostY},	// Right
		{ghostX - 1, ghostY},	// Left
		{ghostX, ghostY + 1},	// Down
		{ghostX, ghostY - 1},	// Up
		{ghostX, ghostY}		// Stay
	};

	int min_heuristic = INT_MAX;
	std::pair<int, int> bestMove = {ghostX, ghostY}; // Default best move is to stay.

	for (const auto& move : possibleMoves) {
		int heuristic = manhattanDistance(move.first, move.second, pacmanX, pacmanY);
		if (heuristic < min_heuristic) {
			bool validMove = Game::checkValidMovement(grid[move.second][move.first]);
			if (validMove) {
				min_heuristic = heuristic;
				bestMove = move;
			}
		}
	}

	// Restore the ghost's previous position
	grid[ghostY][ghostX] = currentPositionChar;

	// Set the new ghost coordinates
	ghostX = bestMove.first;
	ghostY = bestMove.second;

	// Get the char of the position the ghost will move to.
	currentPositionChar = grid[ghostY][ghostX];
	// Update ghost's position
	grid[ghostY][ghostX] = GHOST_CHAR;

}

void Ghost::escapePacMan() {
	// When blue, try to run away from Pac-Man.
}

// Calculate Manhattan distance between two points
int Ghost::manhattanDistance(int x1, int y1, int x2, int y2) {
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}