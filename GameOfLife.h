#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

#include <SDL2/SDL.h>
#include "Grid.h"

class GameOfLife {
public:
	GameOfLife(Uint16 cellSize, Uint16 windowSize, Uint16 cellColor, Uint16 windowColor);
	void start(Uint32 updateRate);
	SDL_Window* getWindow();
	void handleInput();
	void updateState();
	void drawCurrentState();
	bool isRunning() {return running;}
	void close();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Grid* grid;
	Uint16 cellSize, cellColor;
	Uint16 windowSize, windowColor;
	Uint16 gridSize;
	bool mouseDown;
	bool running;

	Uint32 updateRate;
	Uint32 timeOflastUpdate;
	SDL_Event e;

	void initializeSDL();
};

#endif