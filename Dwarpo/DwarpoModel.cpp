#include "DwarpoModel.h"
#include <iostream>



int DwarpoModel::init()
{
	constructMap();
	placeOres();
	placeCreatures();
	placePlants();
	return 0;
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
			curr->drawableEntity.drawObjectsSize = 2;
			curr->drawableEntity.drawObjects = (DrawObject**)calloc(2, sizeof(DrawObject*));
			this->viewcontroller->constructGrassTileEntity(&curr->drawableEntity);
			curr->drawableEntity.x = w * this->viewcontroller->tileSize();
			//the view gets built from top to bottom --> thus up is down and vice versa
			curr->drawableEntity.y = h * this->viewcontroller->tileSize();
			//add the tile representation to the viewcontroller

			this->viewcontroller->addEntityL(&curr->drawableEntity, 0);


			
		}
	}









}

void DwarpoModel::placeCreatures() {
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
