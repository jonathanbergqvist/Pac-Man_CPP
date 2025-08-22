#include "Game.h"
#include "GUI.h"
#include "TextureHandler.h"
#include <thread>

int main() {
    TextureHandler textures;
    GUI gameGUI(textures);
    Game game(gameGUI);

    // Start user input in a separate thread if needed
    std::thread inputThread(&Game::UserInputThread, &game);

    // Run rendering/game loop on the main thread
    game.RenderingThread();

    inputThread.join();
    return 0;
}
