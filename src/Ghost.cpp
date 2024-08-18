#include "Game.h"
#include "Pacman.h"
#include "Ghost.h"

Ghost::Ghost(COLOUR colour) : ghostColour(colour) {
	// Constructor implementation for colored ghost
	currentMode = MODE::Start;
	currentPositionChar = Game::EMPTY;

	switch (ghostColour) {
	case COLOUR::Orange:
		ghostX = 16;
		ghostY = 12;
		break;
	case COLOUR::Red:
		ghostX = 14;
		ghostY = 9;
		break;
	case COLOUR::Pink:
		ghostX = 14;
		ghostY = 12;
		break;
	case COLOUR::Cyan:
		ghostX = 12;
		ghostY = 12;
		break;
	default:
		break;
	}
}

void Ghost::changeMode(MODE newMode) {
	currentMode = newMode;
}

void Ghost::moveGhost(int pacmanX, int pacmanY, char grid[GRID_Y][GRID_X]) {
	// Move the ghost according to the colour of the ghost.
	updatePossibleMovesCoordinates();
	std::pair<int, int> bestMove = { ghostX, ghostY };
	switch (currentMode) {

		// CHASE
	case MODE::Chase:
		bestMove = chaseMove(pacmanX, pacmanY, grid);
		// Count down time for chasing ghost, once at 0 reset to scatter mode.
		chaseTimeLeft--;
		if (chaseTimeLeft <= 0) {
			changeMode(MODE::Scatter);
			chaseTimeLeft = 0;
		}
		break;

		// FRIGHTENED
	case MODE::Frightened:
		// Move as frightened blue ghost
		bestMove = frightenedMove(grid);

		// Count down time for frightened ghost, once at 0 reset to scatter mode.
		blueGhostTimeLeft--;
		if (blueGhostTimeLeft <= 0) {
			changeMode(MODE::Scatter);
			blueGhostTimeLeft = 0;
		}
		break;

		// SCATTER
	case MODE::Scatter:
		bestMove = scatterMove(grid);
		break;

		// START MOVE TO OUTSIDE THE BOX
	case MODE::Start:
		bestMove = startMove(START_POSITION.first, START_POSITION.second, grid);
		break;
	default:
		break;
	}

	// Make sure that in case of hit with Pac-Man, that the position is left EMPTY.
	if (ghostX == pacmanX && ghostY == pacmanY) {
		currentPositionChar = Game::EMPTY;
	}

	// Replace the old position with the char before the ghost entered the position.
	grid[ghostY][ghostX] = currentPositionChar;

	// Set the new ghost coordinates
	ghostX = bestMove.first;
	ghostY = bestMove.second;

	ghostX = Game::checkIfChangeInSideX(ghostX);

	// Get the char of the position the ghost will move to.
	currentPositionChar = grid[ghostY][ghostX];
	// Update ghost's position
	grid[ghostY][ghostX] = Game::GHOST_CHAR;

}

// Calculate Manhattan distance between two points
int Ghost::manhattanDistance(int x1, int y1, int x2, int y2) {
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}

void Ghost::updatePossibleMovesCoordinates() {
	POSSIBLE_MOVES = {
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
		randomIndex = rand() % POSSIBLE_MOVES.size(); // Get a random index
		std::pair<int, int> move = POSSIBLE_MOVES[randomIndex];
		validMove = Game::checkValidNonStartGhostMovement(grid[move.second][move.first]);
	}
	return POSSIBLE_MOVES[randomIndex]; // Return the random move
}


std::pair<int, int> Ghost::frightenedMove(char grid[GRID_Y][GRID_X]) {
	std::pair<int, int> bestMove = { ghostX, ghostY }; // Default best move is to stay.

	std::pair<int, int> corner = { ghostX, ghostY };

	switch (ghostColour) {
	case COLOUR::Orange:
		corner = { ORANGE_GHOST_CORNER_X, ORANGE_GHOST_CORNER_Y };
		break;
	case COLOUR::Red:
		corner = { RED_GHOST_CORNER_X, RED_GHOST_CORNER_Y };
		break;
	case COLOUR::Pink:
		corner = { PINK_GHOST_CORNER_X, PINK_GHOST_CORNER_Y };
		break;
	case COLOUR::Cyan:
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

	for (const auto& move : POSSIBLE_MOVES) {
		int heuristic = manhattanDistance(move.first, move.second, targetX, targetY);
		if (heuristic < min_heuristic) {
			bool validMove = Game::checkValidNonStartGhostMovement(grid[move.second][move.first]);
			if (validMove) {
				min_heuristic = heuristic;
				bestMove = move;
			}
		}
	}
	return bestMove;
}

// Find best way to the outside of the starting box
std::pair<int, int> Ghost::startMove(int targetX, int targetY, char grid[GRID_Y][GRID_X]) {
	// Calculate heuristic for each possible move
	int min_heuristic = INT_MAX;
	std::pair<int, int> bestMove = { ghostX, ghostY }; // Default best move is to stay.

	for (const auto& move : POSSIBLE_MOVES) {
		int heuristic = manhattanDistance(move.first, move.second, targetX, targetY);
		if (heuristic < min_heuristic) {
			bool validMove = Game::checkValidStartGhostMovement(grid[move.second][move.first]);
			if (validMove) {
				min_heuristic = heuristic;
				bestMove = move;
			}
		}
	}
	return bestMove;
}

std::string Ghost::colourEnumToString(COLOUR value) {
	switch (value) {
	case COLOUR::Orange: return "Orange";
	case COLOUR::Red: return "Red";
	case COLOUR::Pink: return "Pink";
	case COLOUR::Cyan: return "Cyan";
	default: return "";
	}
}

std::string Ghost::modeEnumToString(MODE value) {
	switch (value) {
	case MODE::Chase: return "Chase";
	case MODE::Scatter: return "Scatter";
	case MODE::Frightened: return "Frightened";
	case MODE::Start: return "Start";
	default: return "";
	}
}