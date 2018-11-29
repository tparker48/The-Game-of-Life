#include <SDL2/SDL.h>
#include "GameOfLife.h"

int main(int argc, char* args[]) {

	Uint16 cellSize = 4;
	Uint16 screenSize = 800;
	Uint16 screenColor = 0x2E;		// determines value for R, G, and B chanels (so sgrayscale only)
	Uint16 cellColor = 0xEB;	// determines value for R, G, and B chanels (so grayscale only)
	Uint16 millsecondsPerStep = 25;

	GameOfLife game = GameOfLife(cellSize, screenSize, cellColor, screenColor);
	game.start(millsecondsPerStep);
	SDL_Window* window = game.getWindow();

	while(game.isRunning()) {
		game.update();
	}

	game.close();
	return 0;
}