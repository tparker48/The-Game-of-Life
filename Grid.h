// Grid.h
#ifndef GRID_H
#define GRID_H

#include <utility>

class Grid {
public:
	Grid();
	Grid(std::size_t size);
	~Grid();

	void toggleCell(int x, int y);
	void setCell(int x, int y, bool state);
	void clearGrid();
	void update();
	bool cellIsLiving(int x, int y);

private:
	int countLiveNeighbors(int x, int y);
	void updateCell(int x, int y);
	bool** currentState;
	bool** nextState;
	std::size_t size;
};

#endif