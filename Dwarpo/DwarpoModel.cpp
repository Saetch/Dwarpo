#include "DwarpoModel.h"
#include "KnightD.h"
#include <iostream>
#include "Dwarf_BaseHouse.h"
#include "MapGenerator.h"
#include <vector>
#include <future>
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

	for (int i = 0; i < 400; i++) {
		knuffte = new KnightD();

		knuffte->xPos = (rand()%3990)/10.0f;
		knuffte->yPos = (rand()%3990)/10.0f;
		knuffte->init();
		this->viewcontroller->entityList.push_back(knuffte);

	}
	return;

}


void DwarpoModel::constructMap()
{
	MapGenerator* mapGen = new MapGenerator(&this->map, DWARPO_GRID_WIDTH, DWARPO_GRID_HEIGHT, 10, 2);
	this->homeArea = mapGen->generateGameField();




	


	//mapGen->generateMountains(viewcontroller);





	



	delete mapGen;

}


void DwarpoModel::placeBaseHouse() {
	Dwarf_BaseHouse* p_house;
	p_house = new Dwarf_BaseHouse(5,7, viewcontroller->tileSize());

	this->viewcontroller->structureList.push_back(p_house);
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

