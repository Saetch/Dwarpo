#pragma once
#include "groundTile.h"

class DPEngine_instance;

class MapGenerator
{
public:
	groundTile* map;
	int width;
	int height;
	int chunkSize;
	int wallWidth;

	MapGenerator(groundTile* grid, int gridWidth, int gridHeight, int chunkS, int wallW) : map(grid), width(gridWidth), height(gridHeight), chunkSize(chunkS), wallWidth(wallW) {};

	void generateMountains(DPEngine_instance* engine);
};

