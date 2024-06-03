#pragma once

#include <iostream>

class PacMan {
public:
    const char PACMAN_CHAR = 'C';
    const char PACMAN_COLOUR = 'y';

    PacMan();
    void movePacMan();

private:
    bool checkIfHitByGhost();
    bool checkIfHittingBlueGhost();
};