#include <conio.h> // For _getch()

#include "Game.h"
#include "Pacman.h"

// Member function definitions
bool PacMan::movePacMan(char grid[GRID_Y][GRID_X]) {
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

	bool powerPelletHit = false;

	// Update Pac-Man's position in the grid only if a valid input, i.e. not into a wall.
	if (Game::checkValidPacManMovement(grid[pacmanY][pacmanX])) {
		if (grid[pacmanY][pacmanX] == '.' || grid[pacmanY][pacmanX] == '*') {
			Game::numberOfPelletsRemaining -= 1;
			Game::score += Game::DOT_SCORE; // Score per regular pellet.
		}
		if (grid[pacmanY][pacmanX] == '*') {
			powerPelletHit = true;
			Game::score += Game::BIG_DOT_EXTRA_SCORE; // An additional score per power pellet.
		}

		grid[pacmanY][pacmanX] = PACMAN_CHAR;
		grid[currentPositionY][currentPositionX] = EMPTY;
	}
	else {
		// Reset the position of Pac-Man to the position before used selected direction.
		pacmanX = currentPositionX;
		pacmanY = currentPositionY;
	}

	return powerPelletHit;

}