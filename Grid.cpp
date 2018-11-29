// Grid.cpp
#include "Grid.h"
#include <iostream>

Grid::Grid(std::size_t size) {
	this->size = size;
	currentState = new bool*[size];
	nextState = new bool*[size];

	for(int i = 0; i < size; i++){
		currentState[i] = new bool[size];
		nextState[i] = new bool[size];
	}

	for(std::size_t i = 0; i < size; i++) {
		for (std::size_t j = 0; j < size; j++) {
			currentState[i][j] = false;
			nextState[i][j] = false;
		}
	}
}

Grid::~Grid(){
	delete[] currentState;
	delete[] nextState;
}

void Grid::toggleCell(int x, int y) {
	currentState[x][y] = !currentState[x][y];
}

void Grid::clearGrid() {
	for(int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			currentState[i][j] = false;
		}
	}
}

void Grid::update() {
	for(int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			updateCell(i,j);
		}
	}

	bool** temp = currentState;
	currentState = nextState;
	nextState = temp;
}


bool Grid::cellIsLiving(int x, int y) {
	if(x < 0 || y < 0 || x >= size || y >= size){
		return false;
	}
	else return currentState[x][y];
}

int Grid::countLiveNeighbors(int x, int y) {
	int sum = 0;
	sum+= cellIsLiving(x  , y+1);
	sum+= cellIsLiving(x  , y-1);
	sum+= cellIsLiving(x-1, y);
	sum+= cellIsLiving(x+1, y);
	sum+= cellIsLiving(x-1, y+1);
	sum+= cellIsLiving(x+1, y+1);
	sum+= cellIsLiving(x-1, y-1);
	sum+= cellIsLiving(x+1, y-1);
	return sum;
}

void Grid::updateCell(int x, int y) {
	int neighbors = countLiveNeighbors(x,y);

	if(currentState[x][y]) {
		if (neighbors != 2 && neighbors != 3) nextState[x][y] = false;
		else nextState[x][y] = true;
	}

	else {
		if (neighbors == 3) nextState[x][y] = true;
		else nextState[x][y] = false;
	}
}