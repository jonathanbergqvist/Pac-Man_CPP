#pragma once

#include <iostream>
#include "Main.h"
#include "Pacman.h"
#include "Ghost.h"

class Game {
	char grid[GRID_Y][GRID_X] = {
		"#####################",
		"#...*...........*...#",
		"#.##.###.###.###.##.#",
		"#...................#",
		"#.##.#.#####.#.##.#.#",
		"#....#.......#......#",
		"#.##.#.##.##.#.##.#.#",
		"#...................#",
		"#.##.###.###.###.##.#",
		"#...*...........*...#",
		"#####################"
	};

	static const char WALL = '#';
	static const char DOT = '.';
	static const char BIG_DOT = '*';
	static const char GHOST_CHAR = 'G';
	static const int BLUE_GHOST_TIME_LEFT = 15; // Cells
	static const int REGULAR_GHOST_CHASE_TIME = 30; // Cells
	static const int PACMAN_SEARCH_RANGE = 5; // 5 free non-wall columns/rows.

	void showGameOverScreen() const;
	void playGame();
	bool checkIfBoardIsComplete() const;
	bool checkIfPacManRegularGhostCollision(std::shared_ptr<Ghost> ghost) const;
	void checkIfPacManBlueGhostCollision(std::shared_ptr<Ghost> ghost);
	int countCharInGameGrid(char grid[GRID_Y][GRID_X]);
	bool checkIfPacManWithinRange(std::shared_ptr<Ghost> ghost) const;


public:
	Game();

	void displayGrid() const;

	static bool checkValidPacManMovement(char wantedLocation);
	static bool checkValidGhostMovement(char wantedLocation);

	static int numberOfPelletsRemaining;

	bool checkCollisionAndSearchRange(std::shared_ptr<Ghost> ghost);

	PacMan pacMan;

	std::shared_ptr<Ghost> ghostOrange = std::make_shared<Ghost>(Colour::Orange);
	std::shared_ptr<Ghost> ghostRed = std::make_shared<Ghost>(Colour::Red);
	std::shared_ptr<Ghost> ghostPink = std::make_shared<Ghost>(Colour::Pink);
	std::shared_ptr<Ghost> ghostCyan = std::make_shared<Ghost>(Colour::Cyan);

	std::vector<std::shared_ptr<Ghost>> ghostsPtr = {
		ghostOrange,
		ghostRed,
		ghostPink,
		ghostCyan
	};

};
