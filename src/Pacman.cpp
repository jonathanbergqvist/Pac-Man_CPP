#include <conio.h> // For _getch()

#include "Game.h"
#include "Pacman.h"

Game::DIRECTION currentPacManDirection;
Game::DIRECTION wantedPacManDirection;

// Member function definitions
void PacMan::changePacManDirection(char grid[GRID_Y][GRID_X]) {
	char input;

	// Get user input
	input = _getch();

	// Update Pac-Man's position based on input
	switch(input) {
	case 'w':
		wantedPacManDirection = Game::DIRECTION::Up;
		break;
	case 's':
		wantedPacManDirection = Game::DIRECTION::Left;
		break;
	case 'a':
		wantedPacManDirection = Game::DIRECTION::Down;
		break;
	case 'd':
		wantedPacManDirection = Game::DIRECTION::Right;
		break;
	case 'q':
		exit(0); // Quit the game
	default:
		break;
	}

	//movePacMan(grid);
}

bool PacMan::movePacMan(char grid[GRID_Y][GRID_X]) {
	bool powerPelletHit = false;

	char currentPositionX = pacmanX;
	char currentPositionY = pacmanY;

	// Check the direction of the movement.
	if (wantedPacManDirection == Game::DIRECTION::Up) {
		pacmanY--;
	}
	else if (wantedPacManDirection == Game::DIRECTION::Left) {
		pacmanY++;
	}
	else if (wantedPacManDirection == Game::DIRECTION::Down) {
		pacmanX--;
	}
	else if (wantedPacManDirection == Game::DIRECTION::Right) {
		pacmanX++;
	}

	// Update Pac-Man's position in the grid only if a valid input, i.e. not into a wall.
	if (Game::checkValidPacManMovement(grid[pacmanY][pacmanX])) {
		currentPacManDirection = wantedPacManDirection;

		// Check if PacMan shall switch side on the game board.
		pacmanX = Game::checkIfChangeInSideX(pacmanX);


		if (grid[pacmanY][pacmanX] == '.' || grid[pacmanY][pacmanX] == '*') {
			Game::numberOfPelletsRemaining -= 1;
			Game::score += Game::DOT_SCORE; // Score per regular pellet.
		}
		if (grid[pacmanY][pacmanX] == '*') {
			powerPelletHit = true;
			Game::score += Game::BIG_DOT_EXTRA_SCORE; // An additional score per power pellet.
		}

		// Change current position first, in case current position and the new position is the same through e.g. pressing a non-allowed button (i.e. not wasdq).
		grid[currentPositionY][currentPositionX] = Game::EMPTY;
		grid[pacmanY][pacmanX] = Game::PACMAN_CHAR;
	}
	else {
		// Reset the position of Pac-Man to the position before used selected direction.
		pacmanX = currentPositionX;
		pacmanY = currentPositionY;
		wantedPacManDirection = currentPacManDirection;
	}
	return powerPelletHit;
}