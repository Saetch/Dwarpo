#pragma once
#include "groundTile.h"
#include "DPEngine_instance.h"
//#include "BaseCreature.h"
#include "Dwarf.h"
#include "QueueTypeLinkedList_impl.h"
#include <malloc.h>

#define DWARPO_GRID_WIDTH 100
#define DWARPO_GRID_HEIGHT 100

class Dwarf;
class DPEngine_instance;

class DwarpoModel
{
public:
	int INITIAL_DWARF_COUNT = 7;
	int INITIAL_ANIMAL_COUNT = 10;

	DPEngine_instance* viewcontroller;

	groundTile* map;

	groundTile* homeArea;

	QueueTypeLinkedList<Dwarf**> dwarfs;

	QueueTypeLinkedList<BaseCreature**> animals;

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

