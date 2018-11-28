//SDL Tutorial

#include <SDL2/SDL.h>
#include <iostream>
#include "GameOfLife.h"

using namespace std;

int main(int argc, char* args[]) {
	Uint16 cellSize = 4;
	Uint16 screenSize = 800;

	Uint16 bgColor = 0x2E;
	Uint16 cellColor = 0xEB;

	Uint16 updateRate = 20;

	GameOfLife game = GameOfLife(cellSize, screenSize, cellColor, bgColor);
	game.start(updateRate);

	SDL_Window* window = game.getWindow();

	while(game.isRunning()) {
		game.handleInput();
		game.drawCurrentState();
		game.updateState();
	}

	game.close();
	return 0;
}