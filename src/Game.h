#pragma once

#include <iostream>
#include "Pacman.h"
#include "Ghost.h"

constexpr int GRID_WIDTH = 22;
constexpr int GRID_HEIGHT = 11;

class Game {
	PacMan pacMan;
	Ghost ghostOrange;
	Ghost ghostRed;
	Ghost ghostPink;
	Ghost ghostCyan;

	const char PACMAN;
	const char WALL;
	const char DOT;
	const char BIG_DOT;
	const char EMPTY;

	int pacmanX;
	int pacmanY;

	char grid[GRID_HEIGHT][GRID_WIDTH] = {
		"#####################",
		"#...................#",
		"#.##.###.###.###.##.#",
		"#...................#",
		"#.##.#.#####.#.##.#.#",
		"#....#.......#......#",
		"#.##.#.##.##.#.##.#.#",
		"#...................#",
		"#.##.###.###.###.##.#",
		"#...................#",
		"#####################"
	};

	void displayGrid() const;
	void showGameOverScreen();
	void getPlayerInput();
	void playGame();
	bool checkValidUserInput() const;
	bool checkIfBoardIsComplete() const;



public:
	Game();
};
