#pragma once
#include "caveBasic.h"
#include "DPEngine_instance.h"
#include "BaseCreature.h"
#include "QueueTypeLinkedList_impl.h"
#include <malloc.h>
#include <vector>


class Dwarf;
class DPEngine_instance;

class DwarpoModel
{
public:
	int INITIAL_DWARF_COUNT = 7;
	int INITIAL_ANIMAL_COUNT = 10;

	DPEngine_instance* viewcontroller;

	std::vector<baseTile*> map;

	baseTile* homeArea;

	QueueTypeLinkedList<Dwarf**> dwarfs;

	QueueTypeLinkedList<BaseCreature**> animals;
	
	const int w;
	const int h;

	constexpr int WIDTH() {
		return w;
	}
	constexpr int HEIGHT() {
		return h;
	}

	DwarpoModel(const int wi, const int he) : w(wi), h(he) {

	}


	int init();

	void constructMap();
	
	//DEBUG YOU KNOW
	void placeDebugKnight();

	int gameLoopTick(int elapsedTime);

	void placeBaseHouse();

	//initial creaure placing
	void placeCreatures();

	void placeDwarfs();

	void placeAnimals();


	void placeOres();

	void placePlants();

	void migratingAnimals();

	void createJob();

	inline baseTile* getTileAt(int wi, int he) {
		return map[wi + he * WIDTH()];
	}

};

