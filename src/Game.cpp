#include <iostream>
#include <conio.h> // For _getch()
#include <windows.h> // For colouring the terminal characters

#include "Game.h"

using namespace std;

// Function to display the grid
void Game::displayGrid() const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Yellow


	for (int y = 0; y < GRID_HEIGHT; ++y) {
		for (int x = 0; x < GRID_WIDTH; ++x) {
			cout << grid[y][x];
		}
		cout << endl;
	}
}

void Game::playGame() {
	bool gameOver = false;

	while (!gameOver) {
		getPlayerInput();
		gameOver = checkIfBoardIsComplete();
		// TODO: Check if hit by ghost.
	}

	showGameOverScreen();

}

void Game::showGameOverScreen() {
	system("cls"); // Clear the console.
	displayGrid();
	cout << "GAME OVER" << endl;
}

void Game::getPlayerInput() {
	char input;

	system("cls"); // Clear the console.

	// Initial placement of Pac-Man
	grid[pacmanY][pacmanX] = PACMAN;

	// Display the grid
	displayGrid();

	// Get user input
	input = _getch();

	char currentPositionX = pacmanX;
	char currentPositionY = pacmanY;

	// Update Pac-Man's position based on input
	switch (input) {
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
	if (checkValidUserInput()) {
		grid[pacmanY][pacmanX] = PACMAN;
		grid[currentPositionY][currentPositionX] = EMPTY;
	}
	else {
		// Reset the position of Pac-Man to the position before used selected direction.
		pacmanX = currentPositionX;
		pacmanY = currentPositionY;
	}

}

bool Game::checkValidUserInput() const {
	return grid[pacmanY][pacmanX] != WALL;
}

bool Game::checkIfBoardIsComplete() const {
	// Check if there are no DOTs or BIG_DOTs left on the game board.
	for (int y = 0; y < GRID_HEIGHT; ++y) {
		for (int x = 0; x < GRID_WIDTH; ++x) {
			if (grid[y][x] == DOT || grid[y][x] == BIG_DOT) {
				return false; // Character found
			}
		}
	}
	return true; // Character not found
	// TODO: Replace with another methodology when ghosts are added, as they will "hide" the dots.
}


// Constructor implementation
Game::Game() : 
	pacMan(), 
	ghostOrange('o'), 
	ghostRed('r'), 
	ghostPink('p'), 
	ghostCyan('c'),
	PACMAN(pacMan.PACMAN_CHAR), 
	WALL('#'), 
	DOT('.'), 
	BIG_DOT('*'), 
	EMPTY(' '),
	pacmanX(1), 
	pacmanY(1)
{
	playGame();
}
