#include "DwarpoModel.h"
#include "KnightD.h"
#include <iostream>
#include "Dwarf_BaseHouse.h"

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
	this->viewcontroller->addToYOrderedEntityList(knuffte);

	knuffte = new KnightD();

	knuffte->init();
	knuffte->xPos = 3.2f;
	knuffte->yPos = 2.0f;
	this->viewcontroller->addToYOrderedEntityList(knuffte);

	printf_s("\n\nadded Knights to YOrderedEntityList!\n");
	return;

}

void DwarpoModel::constructMap()
{



	//initialize groundType
	StaticEntity* pDrawEnt = new StaticEntity(2);
	this->viewcontroller->constructGrassTileEntity(pDrawEnt);

	map = (groundTile*)malloc(sizeof(groundTile) * DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH);

	groundTile* curr;
	for (int w = 0; w < DWARPO_GRID_WIDTH; w++) {
		for (int h = 0; h < DWARPO_GRID_HEIGHT; h++) {
			curr = getTileAt(w, h);
			curr->init(GROUNDTILE_GRASS);
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


void DwarpoModel::placeBaseHouse() {
	Dwarf_BaseHouse* p_house;
	p_house = new Dwarf_BaseHouse(5,7, viewcontroller->tileSize());

	this->viewcontroller->addToYOrderedEntityList(p_house);
}



void DwarpoModel::placeCreatures() {
	placeDebugKnight();
	placeDwarfs();
	//placeAnimals();
}

void DwarpoModel::placeDwarfs() {
	int startposX = rand() % DWARPO_GRID_WIDTH;
	int startposY = rand() % DWARPO_GRID_HEIGHT;
	for (int i = 0; i < INITIAL_DWARF_COUNT; i++)
	{
		Dwarf* d = new Dwarf();	
		groundTile* curr = getTileAt(startposY, startposY);
		curr->dwarfs.push(d);
	}
}

void DwarpoModel::placeOres() {

}

void DwarpoModel::placePlants() {

}

void DwarpoModel::placeAnimals() {

}

void DwarpoModel::collectWalkableTiles()
{
	for (int w = 0; w < DWARPO_GRID_WIDTH; w++) {
		for (int h = 0; h < DWARPO_GRID_HEIGHT; h++) {
			walkableTiles.push(getTileAt(w, h));
		}
	}
}

void DwarpoModel::migratingAnimals()
{
}

void DwarpoModel::createJob()
{
}
