#include <iostream>
#include <conio.h> // For _getch()
#include <windows.h> // For colouring the terminal characters

#include "Game.h"

using namespace std;

int Game::numberOfPelletsRemaining;

void Game::playGame() {

	bool gameOver = false;

	// Initial placement of Pac-Man
	grid[pacMan.pacmanY][pacMan.pacmanX] = pacMan.PACMAN_CHAR;

	// Count the total number of pellets on the game grid, including the ones covered by the ghosts. PacMan doesn't cover a pellet!
	Game::numberOfPelletsRemaining = countCharInGameGrid(grid);

	// Print the initial ghosts on the map.
	for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
		grid[ghost->ghostY][ghost->ghostX] = ghost->GHOST_CHAR;
	}

	while (!gameOver) {
		// Display the game grid
		displayGrid();
		bool powerPelletHit = pacMan.movePacMan(grid);

		if (powerPelletHit) {
			for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
				ghost->changeMode(Mode::Frightened);
				ghost->chaseTimeLeft = 0; // Remove eventual chase time.
				ghost->blueGhostTimeLeft = Game::BLUE_GHOST_TIME_LEFT; // Moves left for the ghost as blue.
			}
		}

		// Move the ghosts and check if they hit Pac-Man.
		for (std::shared_ptr<Ghost> ghost : ghostsPtr) {

			// PRE-GHOST MOVEMENT CHECK
			gameOver = checkCollisionAndSearchRange(ghost);
			if (gameOver) {
				break;
			}

			// MOVEMENT
			ghost->moveGhost(pacMan.pacmanX, pacMan.pacmanY, grid);

			// POST-GHOST MOVEMENT CHECK
			gameOver = checkCollisionAndSearchRange(ghost);
			if (gameOver) {
				break;
			}
			
		}

		// Check if the board is out of pellets.
		if (!gameOver) {
			gameOver = checkIfBoardIsComplete();
		}

		
	}

	showGameOverScreen();

}

bool Game::checkCollisionAndSearchRange(std::shared_ptr<Ghost> ghost) {
	bool gameOver = false;

	// Check if a ghost while blue ran into with Pac-Man.
	checkIfPacManBlueGhostCollision(ghost);

	// Check if a regular ghost ran into Pac-Man.
	gameOver = checkIfPacManRegularGhostCollision(ghost);
	if (gameOver) {
		return gameOver;
	}

	// Check if Pac-Man is within allowed range post-movement.
	if (checkIfPacManWithinRange(ghost) && ghost->currentMode == Mode::Scatter) {
		ghost->changeMode(Mode::Chase);
		ghost->chaseTimeLeft = Game::REGULAR_GHOST_CHASE_TIME;
	}

	return gameOver;
}

// Set the colour of the terminal text.
static void SetColor(HANDLE hConsole, int textColor, int bgColor = 0) {
	SetConsoleTextAttribute(hConsole, (WORD)((bgColor << 4) | textColor));
}

// Display the game board grid
void Game::displayGrid() const {
	system("cls"); // Clear the console.

	// Set the colour of the entire board to yellow, including Pac-Man and Ghosts.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int y = 0; y < GRID_Y; ++y) {
		for (int x = 0; x < GRID_X; ++x) {
			if (x == pacMan.pacmanX && y == pacMan.pacmanY) {
				SetColor(hConsole, 14); // Yellow
			} else if (x == ghostOrange->ghostX && y == ghostOrange->ghostY && ghostOrange->currentMode != Mode::Frightened) {
				SetColor(hConsole, 12); // Orange
			} else if (x == ghostRed->ghostX && y == ghostRed->ghostY && ghostRed->currentMode != Mode::Frightened) {
				SetColor(hConsole, 4); // Red
			} else if (x == ghostPink->ghostX && y == ghostPink->ghostY && ghostPink->currentMode != Mode::Frightened) {
				SetColor(hConsole, 13); // Pink
			} else if (x == ghostCyan->ghostX && y == ghostCyan->ghostY && ghostCyan->currentMode != Mode::Frightened) {
				SetColor(hConsole, 11); // Orange
			} else if (grid[y][x] == '.' || grid[y][x] == '*') {
				SetColor(hConsole, 14); // Yellow
			} else {
				SetColor(hConsole, 9); // Blue
			}
			cout << Game::grid[y][x];
		}
		cout << endl;

	}
	SetColor(hConsole, 7); // Default colour.

	cout << "pY\tgY\tpX\tgX" << endl;
	for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
		cout << pacMan.pacmanX << "\t" << ghost->ghostX << "\t" << pacMan.pacmanY << "\t" << ghost->ghostY << endl;
	}


}

void Game::showGameOverScreen() const {
	displayGrid();
	cout << "GAME OVER" << endl;
}

bool Game::checkValidPacManMovement(char wantedLocation) {
	return wantedLocation != Game::WALL;
}

bool Game::checkValidGhostMovement(char wantedLocation) {
	return wantedLocation != Game::WALL && wantedLocation != Game::GHOST_CHAR;
}

int Game::countCharInGameGrid(char grid[GRID_Y][GRID_X]) {
	int count = 0;
	for (int y = 0; y < GRID_Y; ++y) {
		for (int x = 0; x < GRID_X; ++x) {
			if (grid[y][x] == DOT || grid[y][x] == BIG_DOT) {
				count += 1;
			}
		}
	}
	return count;
}

bool Game::checkIfPacManWithinRange(std::shared_ptr<Ghost> ghost) const {
	int g_x = ghost->ghostX;
	int g_y = ghost->ghostY;

	// Check Up
	for (int y = g_y - 1; y >= max(0, g_y - PACMAN_SEARCH_RANGE); y--) {
		if (grid[y][g_x] == PacMan::PACMAN_CHAR) return true;
		if (grid[y][g_x] == WALL) break;
	}
	// Check Down
	for (int y = g_y + 1; y <= min(GRID_Y - 1, g_y + PACMAN_SEARCH_RANGE); y++) {
		if (grid[y][g_x] == PacMan::PACMAN_CHAR) return true;
		if (grid[y][g_x] == WALL) break;
	}
	// Check Left
	for (int x = g_x - 1; x >= max(0, g_x - PACMAN_SEARCH_RANGE); x--) {
		if (grid[g_y][x] == PacMan::PACMAN_CHAR) return true;
		if (grid[g_y][x] == WALL) break;
	}
	// Check Right
	for (int x = g_x + 1; x <= min(GRID_X - 1, g_x + PACMAN_SEARCH_RANGE); x++) {
		if (grid[g_y][x] == PacMan::PACMAN_CHAR) return true;
		if (grid[g_y][x] == WALL) break;
	}
	return false;
}

bool Game::checkIfBoardIsComplete() const {
	if (numberOfPelletsRemaining == 0) {
		return true;
	} else {
		return false;
	}
}


bool Game::checkIfPacManRegularGhostCollision(std::shared_ptr<Ghost> ghost) const {
	if (pacMan.pacmanX == ghost->ghostX && pacMan.pacmanY == ghost->ghostY && ghost->currentMode != Mode::Frightened) {
		return true;
	} else {
		return false;
	}
}

void Game::checkIfPacManBlueGhostCollision(std::shared_ptr<Ghost> ghost) {
	if (pacMan.pacmanX == ghost->ghostX && pacMan.pacmanY == ghost->ghostY && ghost->currentMode == Mode::Frightened) {
		// Ghost hit will be moved to the middle of the screen and returned to scatter mode.
		ghost->ghostX = GRID_X / 2 - 2;
		ghost->ghostY = GRID_Y / 2;
		// Update ghost's position
		ghost->blueGhostTimeLeft = 0;
		ghost->changeMode(Mode::Scatter);
		grid[ghost->ghostY][ghost->ghostX] = GHOST_CHAR;
		grid[pacMan.pacmanY][pacMan.pacmanX] = PacMan::PACMAN_CHAR;
	}
}


// Constructor implementation
Game::Game() :
	pacMan() {
	playGame();
}
