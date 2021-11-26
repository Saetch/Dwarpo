#include "DwarpoModel.h"
#include "KnightD.h"
#include <iostream>
#include "Dwarf_BaseHouse.h"

#include "MapGenerator.h"
//remove this when debug is done! TODO
#define LOADDEBUG 1
#include <vector>
void initClasses() {
	Dwarf_BaseHouse::init();
	KnightD::initKnightDClass();

	//other classes that need initialization to follow


}


int DwarpoModel::init()
{
	initClasses();


	constructMap();

	placeBaseHouse();

	placeOres();
	placeCreatures();
	placePlants();
	return 0;
}


//debugging / example of placing a knight on screen
void DwarpoModel::placeDebugKnight() {
	KnightD* knuffte;
	knuffte = new KnightD();
	knuffte->xPos = 1.0f;
	knuffte->yPos = 1.0f;
	knuffte->init();
	

	printf_s("adding first knight!\n");
	printf_s(knuffte->getType().c_str());
	printf_s("\n");
	this->viewcontroller->entityList.push_back(knuffte);

	knuffte = new KnightD();

	knuffte->init();
	knuffte->xPos = 3.2f;
	knuffte->yPos = 2.0f;
	this->viewcontroller->entityList.push_back(knuffte);
	srand(10);

	for (int i = 0; i < 400000; i++) {
		knuffte = new KnightD();

		knuffte->xPos = (rand()%4000)/10.0f;
		knuffte->yPos = (rand()%4000)/10.0f;
		knuffte->init();
		this->viewcontroller->entityList.push_back(knuffte);

	}
	return;

}


void DwarpoModel::constructMap()
{
	MapGenerator* mapGen = new MapGenerator(this->map, DWARPO_GRID_WIDTH, DWARPO_GRID_HEIGHT, 10, 2);
	//TODO move generation to dedicated generator class



	//initialize background
	this->map = {};
	this->map.reserve(DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH);
	for (int i = 0; i < DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH; i++) {
		caveBasic* newT= new caveBasic();
		this->map.push_back(newT);
	}

	baseTile* curr;
	for (int w = 0; w < DWARPO_GRID_WIDTH; w++) {
		for (int h = 0; h < DWARPO_GRID_HEIGHT; h++) {
			curr = getTileAt(w, h);			
			curr->init();
			
			

			


			
		}
	}


	if (LOADDEBUG) {
		for (int w = 0; w < DWARPO_GRID_WIDTH; w++) {
			for (int h = 0; h < DWARPO_GRID_HEIGHT; h++) {
				curr = getTileAt(w, h);
				//this chunk of actions is only needed for debug-grid, can be removed later (when DPEngine_instance.cpp -> DWARPO_SHOWGRID is 0)
				curr->drawableEntity.drawObjectsSize = 2;
				curr->drawableEntity.drawObjects = (DrawObject**)calloc(2, sizeof(DrawObject*));
				this->viewcontroller->constructGrassTileEntity(&curr->drawableEntity);
				curr->drawableEntity.x = w * this->viewcontroller->tileSize();
				//the view gets built from top to bottom --> thus up is down and vice versa
				curr->drawableEntity.y = h * this->viewcontroller->tileSize();
				//add the tile representation to the viewcontroller



			}
		}
	}


	mapGen->generateMountains(viewcontroller);





	





}


void DwarpoModel::placeBaseHouse() {
	Dwarf_BaseHouse* p_house;
	p_house = new Dwarf_BaseHouse(5,7, viewcontroller->tileSize());

	this->viewcontroller->entityList.push_back(p_house);
}



void DwarpoModel::placeCreatures() {
	placeDebugKnight();
	//placeAnimals();
}


void DwarpoModel::placeOres() {

}

void DwarpoModel::placePlants() {

}

void DwarpoModel::placeAnimals() {

}



void DwarpoModel::migratingAnimals()
{
}

void DwarpoModel::createJob()
{
}


int DwarpoModel::gameLoopTick(int elapsedTime)
{
	int reloadBackground = false;
	for (Entity* ent : viewcontroller->entityList) {
		
	}




	return reloadBackground;
}

