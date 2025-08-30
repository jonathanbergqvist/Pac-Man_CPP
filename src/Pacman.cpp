#include <optional>

#include "GameLogic.h"
#include "Pacman.h"

GameLogic::DIRECTION currentPacManDirection;
GameLogic::DIRECTION wantedPacManDirection;

// Member function definitions
void PacMan::changePacManDirection(char grid[GRID_Y][GRID_X]) {

	// Get user input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		wantedPacManDirection = GameLogic::DIRECTION::Up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		wantedPacManDirection = GameLogic::DIRECTION::Down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		wantedPacManDirection = GameLogic::DIRECTION::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		wantedPacManDirection = GameLogic::DIRECTION::Right;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		exit(0); // Quit the game
	}
}

bool PacMan::movePacMan(char grid[GRID_Y][GRID_X], double deltaTime) {
    double speed = 1.0; // tiles per second
    moveAccumulator += speed * deltaTime;
	bool powerPelletHit = false;
    bool moved = false;
    while (moveAccumulator >= 1.0) {
		

		char currentPositionX = pacmanX;
		char currentPositionY = pacmanY;

		// Check the direction of the movement.
		if (wantedPacManDirection == GameLogic::DIRECTION::Up) {
			pacmanY--;
		}
		else if (wantedPacManDirection == GameLogic::DIRECTION::Left) {
			pacmanY++;
		}
		else if (wantedPacManDirection == GameLogic::DIRECTION::Down) {
			pacmanX--;
		}
		else if (wantedPacManDirection == GameLogic::DIRECTION::Right) {
			pacmanX++;
		}

		// Update Pac-Man's position in the grid only if a valid input, i.e. not into a wall.
		if (GameLogic::checkValidPacManMovement(grid[pacmanY][pacmanX])) {
			currentPacManDirection = wantedPacManDirection;

			// Check if PacMan shall switch side on the game board.
			pacmanX = GameLogic::checkIfChangeInSideX(pacmanX);


			if (grid[pacmanY][pacmanX] == '.' || grid[pacmanY][pacmanX] == '*') {
				GameLogic::numberOfPelletsRemaining -= 1;
				GameLogic::score += GameLogic::DOT_SCORE; // Score per regular pellet.
			}
			if (grid[pacmanY][pacmanX] == '*') {
				powerPelletHit = true;
				GameLogic::score += GameLogic::BIG_DOT_EXTRA_SCORE; // An additional score per power pellet.
			}

			// Change current position first, in case current position and the new position is the same through e.g. pressing a non-allowed button (i.e. not wasdq).
			grid[currentPositionY][currentPositionX] = GameLogic::EMPTY;
			grid[pacmanY][pacmanX] = GameLogic::PACMAN_CHAR;
		}
		else {
			// Reset the position of Pac-Man to the position before used selected direction.
			pacmanX = currentPositionX;
			pacmanY = currentPositionY;
			wantedPacManDirection = currentPacManDirection;
		}
        moveAccumulator -= 1.0;
        
    }
    return powerPelletHit;
}

PacMan::PacMan() {
	pacmanX = 14;
	pacmanY = 20;

}