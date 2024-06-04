#include <conio.h> // For _getch()

#include "Game.h"
#include "Pacman.h"

// Member function definitions
void PacMan::movePacMan(char grid[GRID_Y][GRID_X]) {
	char input;

	// Get user input
	input = _getch();

	char currentPositionX = pacmanX;
	char currentPositionY = pacmanY;

	// Update Pac-Man's position based on input
	switch(input) {
	case 'w':
		pacmanY--;
		break;
	case 's':
		pacmanY++;
		break;
	case 'a':
		pacmanX--;
		break;
	case 'd':
		pacmanX++;
		break;
	case 'q':
		exit(0); // Quit the game
	}

	// Update Pac-Man's position in the grid only if a valid input, i.e. not into a wall.
	if (Game::checkValidMovement(grid[pacmanY][pacmanX])) {
		grid[pacmanY][pacmanX] = PACMAN_CHAR;
		grid[currentPositionY][currentPositionX] = EMPTY;
	}
	else {
		// Reset the position of Pac-Man to the position before used selected direction.
		pacmanX = currentPositionX;
		pacmanY = currentPositionY;
	}

}

bool PacMan::checkIfHitByGhost() {
    return false;
}

bool PacMan::checkIfHittingBlueGhost() {
    return false;
}