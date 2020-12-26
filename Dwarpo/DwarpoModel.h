#pragma once
#include "groundTile.h"
#include "DPEngine_instance.h"
#include "BaseCreature.h"
#include "Dwarf.h"
#include <malloc.h>
#define DWARPO_GRID_WIDTH 40
#define DWARPO_GRID_HEIGHT 40


class DwarpoModel
{
public:
	DPEngine_instance* viewcontroller;

	groundTile* map;

	groundTile* homeArea;

	BaseCreature* animals;

	Dwarf* dwarfs;

	int init();

	void constructMap();
	
	//initial creaure placing
	void placeCreatures();

	void placeDwarfs();

	void placeAnimals();

	void collectWalkableTiles();

	void placeOres();

	void placePlants();

	void migratingAnimals();

	void createJob();

	QueueTypeLinkedList<groundTile> walkableTiles;

	inline groundTile* getTileAt(int w, int h) {
		return &map[w + h * DWARPO_GRID_HEIGHT];
	}

};

