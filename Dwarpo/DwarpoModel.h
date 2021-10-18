#pragma once
#include "DPEngine_instance.h"
//#include "BaseCreature.h"
#include "QueueTypeLinkedList_impl.h"
#include <malloc.h>
#include "baseTile.h"

#define DWARPO_GRID_WIDTH 400
#define DWARPO_GRID_HEIGHT 400

class Dwarf;
class DPEngine_instance;
class BaseCreature;

class DwarpoModel
{
public:
	int INITIAL_DWARF_COUNT = 7;
	int INITIAL_ANIMAL_COUNT = 10;

	DPEngine_instance* viewcontroller;

	baseTile* map;

	baseTile* homeArea;

	QueueTypeLinkedList<Dwarf**> dwarfs;

	QueueTypeLinkedList<BaseCreature**> animals;

	int init();

	void constructMap();
	
	//DEBUG YOU KNOW
	void placeDebugKnight();


	void placeBaseHouse();

	//initial creaure placing
	void placeCreatures();

	void placeDwarfs();

	void placeAnimals();

	void collectWalkableTiles();

	void placeOres();

	void placePlants();

	void migratingAnimals();

	void createJob();

	QueueTypeLinkedList<baseTile> walkableTiles;

	inline baseTile* getTileAt(int w, int h) {
		int os = w + h;
		os *= DWARPO_GRID_HEIGHT;
		baseTile* ret;
		ret = map + os;
		return ret;
	}

};

