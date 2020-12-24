#pragma once
#include "groundTile.h"
#include "DPEngine_instance.h"
#include <malloc.h>
#define DWARPO_GRID_WIDTH 40
#define DWARPO_GRID_HEIGHT 40


class DwarpoModel
{
public:
	DPEngine_instance* viewcontroller;

	groundTile* map;

	void constructMap();

	void placeCreatures();

	void createJob();

	inline groundTile* getTileAt(int w, int h) {
		return &map[w + h * DWARPO_GRID_HEIGHT];
	}

};

