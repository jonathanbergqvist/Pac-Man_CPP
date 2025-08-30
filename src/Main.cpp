#include "GameLogic.h"
#include "GUI.h"
#include "TextureHandler.h"

int main() {
    TextureHandler textures;
    GUI gameGUI(textures);
    GameLogic game(gameGUI);
    game.setupGame();

    return 0;
}
