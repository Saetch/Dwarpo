#pragma once
#include "baseTile.h"
#include <vector>
class DPEngine_instance;

class MapGenerator
{
public:
	std::vector<baseTile*>* map;
	int width;
	int height;
	int chunkSize;
	int wallWidth;

	MapGenerator(std::vector<baseTile*>* grid, int gridWidth, int gridHeight, int chunkS, int wallW) : map(grid), width(gridWidth), height(gridHeight), chunkSize(chunkS), wallWidth(wallW) {};



	bool canPlaceStartBase(void* list, DPEngine_instance* viewcntrl);

	void generateMountains(DPEngine_instance* engine);

	baseTile* generateGameField(DPEngine_instance* viewcntrlr);
	bool getAtChecked(int w, int h, baseTile***);
};

