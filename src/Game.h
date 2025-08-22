#pragma once

#include <memory>
#include <vector>

#include "Main.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GUI.h"

class Game {
	char grid[GRID_Y][GRID_X] = {
	"#############################",
	"#............###............#",
	"#.####.#####.###.#####.####.#",
	"#*####.#####.###.#####.####*#",
	"#...........................#",
	"#.####.##.#########.##.####.#",
	"#......##....###....##......#",
	"######.##### ### #####.######",
	"     #.##### ### #####.#     ",
	"     #.##           ##.#     ",
	"     #.## ###---### ##.#     ",
	"######.## #       # ##.######",
	"........# #       # #........", // row 12 from 0
	"######.## #       # ##.######",
	"     #.## ######### ##.#     ",
	"     #.##           ##.#     ",
	"     #.## ######### ##.#     ",
	"######.## ######### ##.######",
	"#............###............#",
	"#.####.#####.###.#####.####.#",
	"#*..##.................##..*#",
	"###.##.##.#########.##.##.###",
	"###.##.##.#########.##.##.###",
	"#......##....###....##......#",
	"#.##########.###.##########.#",
	"#...........................#",
	"#############################"
	};

	static const char WALL = '#';
	static const char DOT = '.';
	static const char BIG_DOT = '*';
	static const char GHOST_WALL = '-';

	static const int BLUE_GHOST_TIME_LEFT = 60; // Cells
	static const int REGULAR_GHOST_CHASE_TIME = 30; // Cells
	static const int PACMAN_SEARCH_RANGE = 5; // 5 free non-wall columns/rows.


	void showGameOverScreen() const;
	void setupGame();
	void playGame(double deltaTime);
	bool checkIfBoardIsComplete() const;
	bool checkIfPacManRegularGhostCollision(std::shared_ptr<Ghost> ghost) const;
	void checkIfPacManBlueGhostCollision(std::shared_ptr<Ghost> ghost);
	int countCharInGameGrid(char grid[GRID_Y][GRID_X]);
	bool checkIfPacManWithinRange(std::shared_ptr<Ghost> ghost) const;

public:
	enum class DIRECTION { Up, Down, Left, Right };

	Game(GUI& gameGUI);

	void UserInputThread();
	void RenderingThread();

	void displayGrid() const;
	void displayGUIWindow() const;

	static bool checkValidPacManMovement(char wantedLocation);
	static bool checkValidStartGhostMovement(char wantedLocation);
	static bool checkValidNonStartGhostMovement(char wantedLocation);
	static int checkIfChangeInSideX(int posX);

	static const char GHOST_CHAR = 'G';
	static const char PACMAN_CHAR = 'C';
	static const char EMPTY = ' ';

	static const int DOT_SCORE = 100;
	static const int BIG_DOT_EXTRA_SCORE = 400;
	static const int BLUE_GHOST_SCORE = 1000;

	static int numberOfPelletsRemaining;
	static int score;
	static bool gameOver;

	bool checkCollisionAndSearchRange(std::shared_ptr<Ghost> ghost);

	PacMan pacMan;

	std::shared_ptr<Ghost> ghostOrange = std::make_shared<Ghost>(COLOUR::Orange);
	std::shared_ptr<Ghost> ghostRed = std::make_shared<Ghost>(COLOUR::Red);
	std::shared_ptr<Ghost> ghostPink = std::make_shared<Ghost>(COLOUR::Pink);
	std::shared_ptr<Ghost> ghostCyan = std::make_shared<Ghost>(COLOUR::Cyan);

	std::vector<std::shared_ptr<Ghost>> ghostsPtr = {
		ghostOrange,
		ghostRed,
		ghostPink,
		ghostCyan
	};

private:
	GUI& gameGUI;

};
