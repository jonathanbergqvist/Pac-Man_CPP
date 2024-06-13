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

	// Display the game grid
	displayGrid();
	while (!gameOver) {

		bool powerPelletHit = pacMan.movePacMan(grid);

		if (powerPelletHit) {
			for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
				ghost->changeMode(Mode::Frightened);
				ghost->blueGhostTimeLeft = Game::BLUE_GHOST_TIME_LEFT; // Moves left for the ghost as blue.
			}
		}

		// Move the ghosts and check if they hit Pac-Man.
		for (std::shared_ptr<Ghost> ghost : ghostsPtr) {

			// PRE-GHOST MOVEMENT
			// Check if Pac-Man ran into a blue ghost.
			checkIfPacManBlueGhostCollision(ghost);

			// Check if Pac-Man ran into a regular ghost.
			gameOver = checkIfPacManRegularGhostCollision(ghost);
			if (gameOver) {
				break;
			}
			ghost->moveGhost(pacMan.pacmanX, pacMan.pacmanY, grid);

			// POST-GHOST MOVEMENT

			// Check if a ghost while blue ran into with Pac-Man.
			checkIfPacManBlueGhostCollision(ghost);

			// Check if a regular ghost ran into Pac-Man.
			gameOver = checkIfPacManRegularGhostCollision(ghost);
			if (gameOver) {
				break;
			}
		}


		// Check if the board is out of pellets.
		if (!gameOver) {
			gameOver = checkIfBoardIsComplete();
		}

		// Display the game grid
		displayGrid();
	}

	showGameOverScreen();

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

	//cout << Game::numberOfPelletsRemaining << endl;
	//for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
	//	cout << static_cast<int>(ghost->currentMode) << " " << pacMan.pacmanX << " " << ghost->ghostX << " " << pacMan.pacmanY << " " << ghost->ghostY << " " << ghost->blueGhostTimeLeft << endl;
	//}


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
	if (pacMan.pacmanX == ghost->ghostX && pacMan.pacmanY == ghost->ghostY && ghost->blueGhostTimeLeft > 0) {
		// Ghost hit will be moved to the middle of the screen and returned to scatter mode.
		ghost->ghostX = GRID_X / 2 - 1;
		ghost->ghostY = GRID_Y / 2;
		// Update ghost's position
		ghost->blueGhostTimeLeft = 0;
		ghost->changeMode(Mode::Scatter);
		grid[ghost->ghostY][ghost->ghostX] = GHOST_CHAR;
		grid[pacMan.pacmanY][pacMan.pacmanX] = PacMan::PACMAN_CHAR;
		//cout << static_cast<int>(ghost->currentMode) << " " << pacMan.pacmanX << " " << ghost->ghostX << " " << pacMan.pacmanY << " " << ghost->ghostY << " " << ghost->blueGhostTimeLeft << endl;

	}
}


// Constructor implementation
Game::Game() :
	pacMan() {
	playGame();
}
