#pragma once

#include <iostream>

class Ghost {
public:
    const char GHOST_COLOUR_CHASED = 'b'; // Blue
    const char GHOST_CHAR = 'G';

    char GHOST_COLOUR;

    Ghost(char colour);

    void moveGhost();
    void escapePacMan();
};