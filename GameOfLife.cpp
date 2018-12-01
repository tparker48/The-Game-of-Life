#include <SDL2/SDL.h>
#include "GameOfLife.h"

GameOfLife::GameOfLife(Uint16 cellSize, Uint16 windowSize,
					 	Uint16 cellColor, Uint16 windowColor) {

    this->cellSize = cellSize;
    this->cellColor = cellColor;
    this->windowSize = windowSize;
    this->windowColor = windowColor;
    gridSize = windowSize / cellSize;
	grid = new Grid(gridSize);
    quit = false;
	paused = false;
}

void GameOfLife::start(Uint16 stepTimeInMilliseconds) {
	initializeSDL();
	this->stepTimeInMilliseconds = stepTimeInMilliseconds;
	timeOflastUpdate = SDL_GetTicks();
}

void GameOfLife::update(){
	handleInput();

    if(!paused && ( SDL_GetTicks() - timeOflastUpdate ) >= stepTimeInMilliseconds ) {
	    grid->update();
	    timeOflastUpdate = SDL_GetTicks();
	}

	drawCurrentState();
}

void GameOfLife::close(){
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
    SDL_Quit();
}

void GameOfLife::initializeSDL(){
	SDL_Init(SDL_INIT_VIDEO);
	this->window = SDL_CreateWindow( "Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize, windowSize, SDL_WINDOW_SHOWN );
	this->renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}

void GameOfLife::handleInput(){
    int mousePositionX;
    int mousePositionY;

    if( SDL_PollEvent(&e) ) {
	    if( e.type == SDL_QUIT)	quit = true;

		if(e.type == SDL_KEYDOWN){
			switch( e.key.keysym.sym ){
                	case SDLK_SPACE:
                    paused = !paused;
					break;

					case SDLK_ESCAPE:
					grid->clearGrid();
					break;
        	}
		}

		if(e.type == SDL_MOUSEBUTTONDOWN) mouseDown = true;
		else if(e.type == SDL_MOUSEBUTTONUP) mouseDown = false;

	    if(mouseDown){
   	    	SDL_GetMouseState(&mousePositionX, &mousePositionY);	   
			grid->setCell((mousePositionX/cellSize), (mousePositionY/cellSize), true);
	    }
    }
}

void GameOfLife::drawCurrentState(){
	SDL_SetRenderDrawColor(renderer, windowColor, windowColor, windowColor, 0xFF);
	SDL_RenderClear(renderer);

	for(int i = 0; i < gridSize; i+= 1){
		for(int j = 0; j < gridSize; j+= 1){

			if(grid->cellIsLiving(i,j)){
				SDL_Rect fillRect = { i * cellSize, j * cellSize, cellSize, cellSize};
				SDL_SetRenderDrawColor( renderer, cellColor, cellColor, cellColor, 0xFF );        
				SDL_RenderFillRect( renderer, &fillRect );
			}
		}
	}

	SDL_RenderPresent(renderer);
}