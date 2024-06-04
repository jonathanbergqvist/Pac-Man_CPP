#pragma once

#include <iostream>
#include "Main.h"
#include "Pacman.h"
#include "Ghost.h"

class Game {
	char grid[GRID_Y][GRID_X] = {
		"#####################",
		"#...................#",
		//"#.##.###.###.###.##.#",
		//"#...................#",
		//"#.##.#.#####.#.##.#.#",
		//"#....#.......#......#",
		//"#.##.#.##.##.#.##.#.#",
		//"#...................#",
		//"#.##.###.###.###.##.#",
		//"#...................#",
		"#####################"
	};

	PacMan pacMan;
	Ghost ghostOrange;
	Ghost ghostRed;
	Ghost ghostPink;
	Ghost ghostCyan;

	static const char WALL = '#';
	static const char DOT = '.';
	static const char BIG_DOT = '*';

	void showGameOverScreen() const;
	void playGame();
	bool checkIfBoardIsComplete() const;

public:
	Game();
	void displayGrid() const;
	static bool checkValidMovement(char wantedLocation);

};
