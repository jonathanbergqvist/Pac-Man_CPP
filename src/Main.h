#pragma once

constexpr int GRID_X = 30;
constexpr int GRID_Y = 27;

constexpr int ORANGE_GHOST_CORNER_X = 1; // Orange ghost, top left corner
constexpr int ORANGE_GHOST_CORNER_Y = 1;

constexpr int RED_GHOST_CORNER_X = GRID_X - 3; // Red ghost, top right corner
constexpr int RED_GHOST_CORNER_Y = 1;

constexpr int PINK_GHOST_CORNER_X = 1; // Pink ghost, bottom left corner
constexpr int PINK_GHOST_CORNER_Y = GRID_Y - 2;

constexpr int CYAN_GHOST_CORNER_X = GRID_X - 3; // Cyan ghost, bottom right corner
constexpr int CYAN_GHOST_CORNER_Y = GRID_Y - 2;


#include <iostream>
#include "Game.h"