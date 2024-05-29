#include <iostream>
#include <conio.h> // For _getch()

using namespace std;

// Constants for game elements
const char PACMAN = 'C';
const char GHOST = 'G';
const char WALL = '#';
const char DOT = '.';
const char BIG_DOT = '*';
const char EMPTY = ' ';

// Game grid
const int GRID_WIDTH = 22;
const int GRID_HEIGHT = 11;

// Initial Pac-Man position, top left
int pacmanX = 2;
int pacmanY = 1;

// Initialize the game grid
char grid[GRID_HEIGHT][GRID_WIDTH] = {
    "#####################",
    "#C..................#",
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

// Function to display the grid
void displayGrid() {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            cout << grid[y][x];
        }
        cout << endl;
    }
}

int main() {
    char input;

    while (true) {
        system("cls"); // Clear the console

        // Display the grid
        displayGrid();

        // Get user input
        input = _getch();

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

        // Check for collisions (e.g., hitting walls or collecting dots)
        // You can add more game logic here!

        // Update Pac-Man's position in the grid
        grid[pacmanY][pacmanX] = PACMAN;
    }

    return 0;
}
