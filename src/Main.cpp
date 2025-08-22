#include "Game.h"

#include "GUI.h"
#include "TextureHandler.h"

int main() {
	
	TextureHandler textures;
	GUI gameGUI(textures);
	Game game(gameGUI);
	return 0;
}
