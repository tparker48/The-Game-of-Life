#include <SDL2/SDL.h>
#include "GameOfLife.h"

GameOfLife::GameOfLife(Uint16 cellSize, Uint16 windowSize, Uint16 cellColor, Uint16 windowColor) {
    this->cellSize = cellSize;
    this->windowSize = windowSize;
    this->cellColor = cellColor;
    this->windowColor = windowColor;
    gridSize = windowSize / cellSize;
    running = true;
    mouseDown = false;
    grid = new Grid(windowSize/cellSize);
}


void GameOfLife::start(Uint32 updateRate){
    initializeSDL();
    this->updateRate = updateRate;
    timeOflastUpdate = SDL_GetTicks();
}


SDL_Window* GameOfLife::getWindow(){
    return window;
}


void GameOfLife::handleInput(){
    int mousePositionX;
    int mousePositionY;

    if( SDL_PollEvent(&e) ) {
	    if( e.type == SDL_QUIT)	running = false;
        
	    else if(e.type == SDL_MOUSEBUTTONDOWN) mouseDown = true;
	    else if (e.type == SDL_MOUSEBUTTONUP) mouseDown = false;

	    else if(mouseDown && e.type == SDL_MOUSEMOTION){
   	    	SDL_GetMouseState(&mousePositionX, &mousePositionY);
	    	grid->toggleCell((mousePositionX/cellSize), (mousePositionY/cellSize));
	    }
    }
}


void GameOfLife::updateState(){
    if((SDL_GetTicks() - timeOflastUpdate) >= updateRate) {
	    grid->update();
	    timeOflastUpdate = SDL_GetTicks();
	}
}


void GameOfLife::drawCurrentState(){
	SDL_SetRenderDrawColor(renderer, windowColor, windowColor, windowColor, 0xFF);
	SDL_RenderClear(renderer);

	for(int i = 0; i < gridSize; i+= 1){
		for(int j = 0; j < gridSize; j+= 1){

			if(grid->getCellStatus(i,j)){
				SDL_Rect fillRect = { i * cellSize, j * cellSize, cellSize, cellSize};
				SDL_SetRenderDrawColor( renderer, cellColor, cellColor, cellColor, 0xFF );        
				SDL_RenderFillRect( renderer, &fillRect );
			}
		}
	}

	SDL_RenderPresent(renderer);
}


void GameOfLife::initializeSDL(){
	SDL_Init(SDL_INIT_VIDEO);
	this->window = SDL_CreateWindow( "Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize, windowSize, SDL_WINDOW_SHOWN );
	this->renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}


void GameOfLife::close(){
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
    SDL_Quit();
}