#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

#include <SDL2/SDL.h>
#include "Grid.h"

class GameOfLife {

public:
	GameOfLife(Uint16 cellSize, Uint16 windowSize, 
				Uint16 cellColor, Uint16 windowColor);

	void start(Uint16 stepTimeInMilliseconds);
	void update();
	void close();

	bool isRunning() {return running;}
	SDL_Window* getWindow() {return window;}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Grid* grid;
	Uint16 cellSize, cellColor;
	Uint16 windowSize, windowColor;
	Uint16 gridSize;
	bool mouseDown;
	bool running;

	Uint16 stepTimeInMilliseconds;
	Uint32 timeOflastUpdate;
	SDL_Event e;

	void initializeSDL();
	void handleInput();
	void drawCurrentState();
};

#endif