#pragma once
#include "groundTile.h"
#include <malloc.h>
#include "DPEngine_instance.h"

#define DWARPO_GRID_WIDTH 200
#define DWARPO_GRID_HEIGHT 200

class DPEngine_instance;

class DwarpoModel
{
public:
	DPEngine_instance* viewcontroller;

	groundTile* map;

	void constructMap();

	void placeCreatures();

	void createJob();

	inline groundTile* getTileAt(int w, int h) {
		return &(map[w + h * DWARPO_GRID_WIDTH]);
	}

};

