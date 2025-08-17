#define NOMINMAX // To avoid min/max macros from windows.h

#include <iostream>
#include <windows.h> // For colouring the terminal characters
#include <thread>
#include <atomic>
#include <string>

#include "Game.h"
#include "Ghost.h"

int Game::numberOfPelletsRemaining;
int Game::score = 0;

bool powerPelletHit = false;
bool Game::gameOver = false;

const double TARGET_FPS = 60.0;
const double FRAME_DURATION = 1.0 / TARGET_FPS;


void Game::setupGame() {
	// Initial placement of Pac-Man
	grid[pacMan.pacmanY][pacMan.pacmanX] = Game::PACMAN_CHAR;

	// Count the total number of pellets on the game grid, including the ones covered by the ghosts. PacMan doesn't cover a pellet!
	Game::numberOfPelletsRemaining = countCharInGameGrid(grid);

	// Print the initial ghosts on the map.
	for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
		grid[ghost->ghostY][ghost->ghostX] = Game::GHOST_CHAR;
	}
}

void Game::playGame() {
	
		// Display the game grid
		displayGrid();

		// Move Pac-Man in the set direction if it's valid.
		bool powerPelletHit = pacMan.movePacMan(grid);
		// Change ghosts movement to FRIGHTENED if Pac-Man hit a power pellet.
		if (powerPelletHit) {
			for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
				ghost->changeMode(MODE::Frightened);
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

bool Game::checkCollisionAndSearchRange(std::shared_ptr<Ghost> ghost) {
	bool gameOver = false;

	if (ghost->ghostX == START_POSITION.first && ghost-> ghostY == START_POSITION.second && ghost->currentMode == MODE::Start) {
		ghost->changeMode(MODE::Scatter);
	}

	// Check if a ghost while blue ran into with Pac-Man.
	checkIfPacManBlueGhostCollision(ghost);

	// Check if a regular ghost ran into Pac-Man.
	gameOver = checkIfPacManRegularGhostCollision(ghost);
	if (gameOver) {
		return gameOver;
	}

	// Check if Pac-Man is within allowed range post-movement.
	if (checkIfPacManWithinRange(ghost) && ghost->currentMode == MODE::Scatter) {
		ghost->changeMode(MODE::Chase);
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

	for (int y = 0; y < GRID_Y; y++) {
		for (int x = 0; x < GRID_X; x++) {
			if (x == pacMan.pacmanX && y == pacMan.pacmanY) {
				SetColor(hConsole, 14); // Yellow
			} else if (x == ghostOrange->ghostX && y == ghostOrange->ghostY && ghostOrange->currentMode != MODE::Frightened) {
				SetColor(hConsole, 12); // Orange
			} else if (x == ghostRed->ghostX && y == ghostRed->ghostY && ghostRed->currentMode != MODE::Frightened) {
				SetColor(hConsole, 4); // Red
			} else if (x == ghostPink->ghostX && y == ghostPink->ghostY && ghostPink->currentMode != MODE::Frightened) {
				SetColor(hConsole, 13); // Pink
			} else if (x == ghostCyan->ghostX && y == ghostCyan->ghostY && ghostCyan->currentMode != MODE::Frightened) {
				SetColor(hConsole, 11); // Cyan
			} else if (grid[y][x] == '.' || grid[y][x] == '*') {
				SetColor(hConsole, 14); // Yellow
			} else {
				SetColor(hConsole, 9); // Blue
			}
			std::cout << Game::grid[y][x];
		}
		//std::cout << "% " << y;

		std::cout << std::endl;

	}
	SetColor(hConsole, 7); // Default colour.

	//std::cout << std::endl << "PELLETS LEFT: " << numberOfPelletsRemaining << std::endl;
	
	std::cout << "SCORE: " << score << std::endl;

}

void Game::showGameOverScreen() const {
	displayGrid();
	std::cout << "GAME OVER" << std::endl;
}

bool Game::checkValidPacManMovement(char wantedLocation) {
	return wantedLocation != Game::WALL && wantedLocation != Game::GHOST_WALL;
}

bool Game::checkValidStartGhostMovement(char wantedLocation) {
	return wantedLocation != Game::WALL && wantedLocation != Game::GHOST_CHAR;
}

bool Game::checkValidNonStartGhostMovement(char wantedLocation) {
	return wantedLocation != Game::WALL && wantedLocation != Game::GHOST_WALL && wantedLocation != Game::GHOST_CHAR;
}

int Game::checkIfChangeInSideX(int posX) {
	if (posX == -1) {
		posX = GRID_X - 2;
	} else if (posX == GRID_X - 1) {
		posX = 0;
	}

	return posX;
}

int Game::countCharInGameGrid(char grid[GRID_Y][GRID_X]) {
	int count = 0;
	for (int y = 0; y < GRID_Y; y++) {
		for (int x = 0; x < GRID_X; x++) {
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

	// Make sure that the coordinates are within allowed ranges.
	if (g_x >= 0 && g_x < GRID_X && g_y >= 0 && g_y < GRID_Y) {
		// Check Up
		for (int y = g_y - 1; y >= std::max(0, g_y - PACMAN_SEARCH_RANGE); y--) {
			if (grid[y][g_x] == Game::PACMAN_CHAR) return true;
			if (grid[y][g_x] == WALL) break;
		}
		// Check Down
		for (int y = g_y + 1; y <= std::min(GRID_Y - 1, g_y + PACMAN_SEARCH_RANGE); y++) {
			if (grid[y][g_x] == Game::PACMAN_CHAR) return true;
			if (grid[y][g_x] == WALL) break;
		}
		// Check Left
		for (int x = g_x - 1; x >= std::max(0, g_x - PACMAN_SEARCH_RANGE); x--) {
			if (grid[g_y][x] == Game::PACMAN_CHAR) return true;
			if (grid[g_y][x] == WALL) break;
		}
		// Check Right
		for (int x = g_x + 1; x <= std::min(GRID_X - 1, g_x + PACMAN_SEARCH_RANGE); x++) {
			if (grid[g_y][x] == Game::PACMAN_CHAR) return true;
			if (grid[g_y][x] == WALL) break;
		}
		return false;
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
	if (pacMan.pacmanX == ghost->ghostX && pacMan.pacmanY == ghost->ghostY && ghost->currentMode != MODE::Frightened) {
		return true;
	} else {
		return false;
	}
}

void Game::checkIfPacManBlueGhostCollision(std::shared_ptr<Ghost> ghost) {
	if (pacMan.pacmanX == ghost->ghostX && pacMan.pacmanY == ghost->ghostY && ghost->currentMode == MODE::Frightened) {
		// Ghost hit will be moved to the middle of the screen and returned to scatter mode.
		score += BLUE_GHOST_SCORE; // Score for hitting blue ghost.

		// Get the colour of the ghost hit.
		COLOUR colour = ghost->ghostColour;

		// Replace the hit ghost position with EMPTY.
		grid[ghost->ghostY][ghost->ghostX] = EMPTY;

		// Replace the position char with EMPTY, to allow no dots in start box.
		ghost->currentPositionChar = EMPTY;

		// Update ghost's position to the staring box
		ghost->ghostX = GRID_X / 2;
		ghost->ghostY = 12;
		ghost->blueGhostTimeLeft = 0;
		ghost->changeMode(MODE::Start);
		grid[ghost->ghostY][ghost->ghostX] = GHOST_CHAR;

		grid[pacMan.pacmanY][pacMan.pacmanX] = Game::PACMAN_CHAR;
	}
}

//////////////////////////////////////////////////////////////////////////////

std::atomic_bool g_run(true); // Shared flag for both threads

void Game::UserInputThread() {
	std::string input;
	while (g_run) {
		pacMan.changePacManDirection(grid);
	}
}

void Game::RenderingThread() {
	setupGame();

	while (g_run && !gameOver) {
		playGame();
		std::this_thread::sleep_for(std::chrono::duration<double>(FRAME_DURATION));
	}
	g_run = false; // Block further input and rendering.
	showGameOverScreen();

}

// Constructor implementation
Game::Game() :
	pacMan() {
	std::thread inputThread(&Game::UserInputThread, this);
	std::thread renderThread(&Game::RenderingThread, this);

	// Wait for threads to finish
	inputThread.join();
	renderThread.join();
}
