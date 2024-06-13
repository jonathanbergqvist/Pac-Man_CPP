#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"

Ghost::Ghost(Colour colour) : ghostColour(colour) {
	// Constructor implementation for colored ghost
	currentMode = Mode::Scatter;

	switch (ghostColour) {
	case Colour::Orange:
		ghostX = ORANGE_GHOST_CORNER_X;
		ghostY = ORANGE_GHOST_CORNER_Y;
		break;
	case Colour::Red:
		ghostX = RED_GHOST_CORNER_X;
		ghostY = RED_GHOST_CORNER_Y;
		break;
	case Colour::Pink:
		ghostX = PINK_GHOST_CORNER_X;
		ghostY = PINK_GHOST_CORNER_Y;
		break;
	case Colour::Cyan:
		ghostX = CYAN_GHOST_CORNER_X;
		ghostY = CYAN_GHOST_CORNER_Y;
		break;
	default:
		break;
	}
}

void Ghost::changeMode(Mode newMode) {
	currentMode = newMode;
}

void Ghost::moveGhost(int pacmanX, int pacmanY, char grid[GRID_Y][GRID_X]) {
	// Move the ghost according to the colour of the ghost.
	updatePossibleMovesCoordinates();
	std::pair<int, int> bestMove = { ghostX, ghostY };

	switch (currentMode) {
	
		// CHASE
	case Mode::Chase:
		bestMove = chaseMove(pacmanX, pacmanY, grid);
		// Count down time for chasing ghost, once at 0 reset to scatter mode.
		chaseTimeLeft--;
		if (chaseTimeLeft <= 0) {
			changeMode(Mode::Scatter);
			chaseTimeLeft = 0;
		}
		break;
		
		// FRIGHTENED
	case Mode::Frightened:
		// Move as frightened blue ghost
		bestMove = frightenedMove(grid);

		// Count down time for frightened ghost, once at 0 reset to scatter mode.
		blueGhostTimeLeft--;
		if (blueGhostTimeLeft <= 0) {
			changeMode(Mode::Scatter);
			blueGhostTimeLeft = 0;
		}
		break;

		// SCATTER
	case Mode::Scatter:
		bestMove = scatterMove(grid);
		break;
	default:
		break;
	}

	// Restore the ghost's previous position
	if (currentPositionChar == PacMan::PACMAN_CHAR) {
		currentPositionChar = PacMan::EMPTY;
	}
	grid[ghostY][ghostX] = currentPositionChar;

	// Set the new ghost coordinates
	ghostX = bestMove.first;
	ghostY = bestMove.second;

	// Get the char of the position the ghost will move to.
	currentPositionChar = grid[ghostY][ghostX];
	// Update ghost's position
	grid[ghostY][ghostX] = GHOST_CHAR;

}

// Calculate Manhattan distance between two points
int Ghost::manhattanDistance(int x1, int y1, int x2, int y2) {
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void Ghost::updatePossibleMovesCoordinates() {
	possibleMoves = {
		{ghostX + 1, ghostY}, // Right
		{ghostX - 1, ghostY}, // Left
		{ghostX, ghostY + 1}, // Down
		{ghostX, ghostY - 1}  // Up

	};
}

std::pair<int, int> Ghost::scatterMove(char grid[GRID_Y][GRID_X]) {
	bool validMove = false;
	int randomIndex;
	while (!validMove) {
		randomIndex = rand() % possibleMoves.size(); // Get a random index
		std::pair<int, int> move = possibleMoves[randomIndex];
		validMove = Game::checkValidGhostMovement(grid[move.second][move.first]);
	}
	return possibleMoves[randomIndex]; // Return the random move
}


std::pair<int, int> Ghost::frightenedMove(char grid[GRID_Y][GRID_X]) {
	std::pair<int, int> bestMove = { ghostX, ghostY }; // Default best move is to stay.

	std::pair<int, int> corner = { ghostX, ghostY };

	switch (ghostColour) {
	case Colour::Orange:
		corner = { ORANGE_GHOST_CORNER_X, ORANGE_GHOST_CORNER_Y };
		break;
	case Colour::Red:
		corner = { RED_GHOST_CORNER_X, RED_GHOST_CORNER_Y };
		break;
	case Colour::Pink:
		corner = { PINK_GHOST_CORNER_X, PINK_GHOST_CORNER_Y };
		break;
	case Colour::Cyan:
		corner = { CYAN_GHOST_CORNER_X, CYAN_GHOST_CORNER_Y };
		break;
	default:
		break;
	}

	bestMove = chaseMove(corner.first, corner.second, grid);

	return bestMove;
}

// Find best way to target, e.g. best way to PacMan or a designated corner.
std::pair<int, int> Ghost::chaseMove(int targetX, int targetY, char grid[GRID_Y][GRID_X]) {
	// Calculate heuristic for each possible move
	int min_heuristic = INT_MAX;
	std::pair<int, int> bestMove = { ghostX, ghostY }; // Default best move is to stay.

	for (const auto& move : possibleMoves) {
		int heuristic = manhattanDistance(move.first, move.second, targetX, targetY);
		if (heuristic < min_heuristic) {
			bool validMove = Game::checkValidGhostMovement(grid[move.second][move.first]);
			if (validMove) {
				min_heuristic = heuristic;
				bestMove = move;
			}
		}
	}
	return bestMove;
}