#define NOMINMAX // To avoid min/max macros from windows.h

#include <iostream>
#include <thread>

#include "GameLogic.h"
#include "Ghost.h"

int GameLogic::numberOfPelletsRemaining;
int GameLogic::score = 0;

bool powerPelletHit = false;
bool GameLogic::gameOver = false;

const double TARGET_FPS = 60.0;
const double FRAME_DURATION = 1.0 / TARGET_FPS;


void GameLogic::setupGame() {
	// Initial placement of Pac-Man
	grid[pacMan.pacmanY][pacMan.pacmanX] = GameLogic::PACMAN_CHAR;

	// Count the total number of pellets on the game grid, including the ones covered by the ghosts. PacMan doesn't cover a pellet!
	GameLogic::numberOfPelletsRemaining = countCharInGameGrid(grid);

	// Print the initial ghosts on the map.
	for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
		grid[ghost->ghostY][ghost->ghostX] = GameLogic::GHOST_CHAR;
	}

	auto lastFrameTime = std::chrono::high_resolution_clock::now();
	while (!gameOver) {

		auto currentFrameTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		handleGameFlow(deltaTime.count());

		// Frame limiting (optional)
		double sleepTime = FRAME_DURATION - deltaTime.count();
		if (sleepTime > 0) {
			std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
		}
	}
}

void GameLogic::handleGameFlow(double deltaTime) {

	while (const std::optional event = gameGUI.window.pollEvent()) {
		// "close requested" event: we close the window
		if (event->is<sf::Event::Closed>()) {
			gameGUI.window.close();
		}

		pacMan.changePacManDirection(grid);

		// Display the game
		displayGameContent();

		// Move Pac-Man in the set direction if it's valid.
		bool powerPelletHit = pacMan.movePacMan(grid, deltaTime);
		// Change ghosts movement to FRIGHTENED if Pac-Man hit a power pellet.
		if (powerPelletHit) {
			for (std::shared_ptr<Ghost> ghost : ghostsPtr) {
				ghost->changeMode(MODE::Frightened);
				ghost->chaseTimeLeft = 0; // Remove eventual chase time.
				ghost->blueGhostTimeLeft = GameLogic::BLUE_GHOST_TIME_LEFT; // Moves left for the ghost as blue.
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
			ghost->moveGhost(pacMan.pacmanX, pacMan.pacmanY, grid, deltaTime);

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

	gameGUI.window.display();
	//gameGUI.window.clear(sf::Color::Black);
}

bool GameLogic::checkCollisionAndSearchRange(std::shared_ptr<Ghost> ghost) {
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
		ghost->chaseTimeLeft = GameLogic::REGULAR_GHOST_CHASE_TIME;
	}

	return gameOver;
}

// Display the game board GUI
void GameLogic::displayGameContent() const {

	gameGUI.drawBackground();

	for (int y = 0; y < GRID_Y; y++) {
		for (int x = 0; x < GRID_X; x++) {
			if (x == pacMan.pacmanX && y == pacMan.pacmanY) {
				gameGUI.drawPacMan(pacMan);
			}
			else if (x == ghostOrange->ghostX && y == ghostOrange->ghostY) {
				gameGUI.drawSingleGhost(*ghostOrange);
			}
			else if (x == ghostRed->ghostX && y == ghostRed->ghostY) {
				gameGUI.drawSingleGhost(*ghostRed);
			}
			else if (x == ghostPink->ghostX && y == ghostPink->ghostY) {
				gameGUI.drawSingleGhost(*ghostPink);
			}
			else if (x == ghostCyan->ghostX && y == ghostCyan->ghostY) {
				gameGUI.drawSingleGhost(*ghostCyan);
			}
			else if (grid[y][x] == '.') {
				gameGUI.drawPelletSmall(x, y);
			}
			else if (grid[y][x] == '*') {
				gameGUI.drawPelletLarge(x, y);
			}
		}
	}
}

bool GameLogic::checkValidPacManMovement(char wantedLocation) {
	return wantedLocation != GameLogic::WALL && wantedLocation != GameLogic::GHOST_WALL;
}

bool GameLogic::checkValidStartGhostMovement(char wantedLocation) {
	return wantedLocation != GameLogic::WALL && wantedLocation != GameLogic::GHOST_CHAR;
}

bool GameLogic::checkValidNonStartGhostMovement(char wantedLocation) {
	return wantedLocation != GameLogic::WALL && wantedLocation != GameLogic::GHOST_WALL && wantedLocation != GameLogic::GHOST_CHAR;
}

int GameLogic::checkIfChangeInSideX(int posX) {
	if (posX == -1) {
		posX = GRID_X - 2;
	} else if (posX == GRID_X - 1) {
		posX = 0;
	}

	return posX;
}

int GameLogic::countCharInGameGrid(char grid[GRID_Y][GRID_X]) {
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

bool GameLogic::checkIfPacManWithinRange(std::shared_ptr<Ghost> ghost) const {
	int g_x = ghost->ghostX;
	int g_y = ghost->ghostY;

	// Make sure that the coordinates are within allowed ranges.
	if (g_x >= 0 && g_x < GRID_X && g_y >= 0 && g_y < GRID_Y) {
		// Check Up
		for (int y = g_y - 1; y >= std::max(0, g_y - PACMAN_SEARCH_RANGE); y--) {
			if (grid[y][g_x] == GameLogic::PACMAN_CHAR) return true;
			if (grid[y][g_x] == WALL) break;
		}
		// Check Down
		for (int y = g_y + 1; y <= std::min(GRID_Y - 1, g_y + PACMAN_SEARCH_RANGE); y++) {
			if (grid[y][g_x] == GameLogic::PACMAN_CHAR) return true;
			if (grid[y][g_x] == WALL) break;
		}
		// Check Left
		for (int x = g_x - 1; x >= std::max(0, g_x - PACMAN_SEARCH_RANGE); x--) {
			if (grid[g_y][x] == GameLogic::PACMAN_CHAR) return true;
			if (grid[g_y][x] == WALL) break;
		}
		// Check Right
		for (int x = g_x + 1; x <= std::min(GRID_X - 1, g_x + PACMAN_SEARCH_RANGE); x++) {
			if (grid[g_y][x] == GameLogic::PACMAN_CHAR) return true;
			if (grid[g_y][x] == WALL) break;
		}
		return false;
	}
	return false;
}

bool GameLogic::checkIfBoardIsComplete() const {
	if (numberOfPelletsRemaining == 0) {
		return true;
	} else {
		return false;
	}
}

bool GameLogic::checkIfPacManRegularGhostCollision(std::shared_ptr<Ghost> ghost) const {
	if (pacMan.pacmanX == ghost->ghostX && pacMan.pacmanY == ghost->ghostY && ghost->currentMode != MODE::Frightened) {
		return true;
	} else {
		return false;
	}
}

void GameLogic::checkIfPacManBlueGhostCollision(std::shared_ptr<Ghost> ghost) {
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

		grid[pacMan.pacmanY][pacMan.pacmanX] = GameLogic::PACMAN_CHAR;
	}
}


// Constructor implementation
GameLogic::GameLogic(GUI& gui) :
	gameGUI(gui),
	pacMan() {
}
