#include <iostream>
#include <conio.h> // For _getch()
#include <windows.h> // For colouring the terminal characters

#include "Game.h"

using namespace std;

void Game::playGame() {
	bool gameOver = false;

	// Initial placement of Pac-Man
	grid[pacMan.pacmanY][pacMan.pacmanX] = pacMan.PACMAN_CHAR;
	grid[ghostCyan.ghostY][ghostCyan.ghostX] = ghostCyan.GHOST_CHAR;
	
	while (!gameOver) {
		displayGrid();
		pacMan.movePacMan(grid);
		ghostCyan.moveGhost(pacMan.pacmanX, pacMan.pacmanY, grid);

		gameOver = checkIfGhostHitsPacMan(ghostCyan);
		if (!gameOver) {
			gameOver = checkIfBoardIsComplete();
		}
	}

	showGameOverScreen();

}

// Display the game board grid
void Game::displayGrid() const {
	system("cls"); // Clear the console.

	// Set the colour of the entire board to yellow, including Pac-Man and Ghosts.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Yellow

	for (int y = 0; y < GRID_Y; ++y) {
		for (int x = 0; x < GRID_X; ++x) {
			cout << Game::grid[y][x];
		}
		cout << endl;
	}
}

void Game::showGameOverScreen() const {
	displayGrid();
	cout << "GAME OVER" << endl;
}

bool Game::checkValidMovement(char wantedLocation) {
	return wantedLocation != Game::WALL;
}

bool Game::checkIfBoardIsComplete() const {
	// Check if there are no DOTs or BIG_DOTs left on the game board.
	for (int y = 0; y < GRID_Y; ++y) {
		for (int x = 0; x < GRID_X; ++x) {
			if (grid[y][x] == DOT || grid[y][x] == BIG_DOT) {
				return false; // Character found
			}
		}
	}
	return true; // Character not found
	// TODO: Replace with another methodology when ghosts are added, as they will "hide" the dots, 
	// e.g. have the total number of dots known and count available dots.
}

bool Game::checkIfGhostHitsPacMan(Ghost ghost) const {
	if (pacMan.pacmanX == ghost.ghostX && pacMan.pacmanY == ghost.ghostY) {
		return true;
	} else {
		return false;
	}
}


// Constructor implementation
Game::Game() : 
	pacMan(), 
	ghostOrange('o'), 
	ghostRed('r'), 
	ghostPink('p'), 
	ghostCyan('c')
{
	playGame();
}
