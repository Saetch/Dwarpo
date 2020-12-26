#include "DwarpoModel.h"

void DwarpoModel::constructMap()
{

	//initialize groundType
	StaticEntity* pDrawEnt = new StaticEntity(2);
	this->viewcontroller->constructGrassTileEntity(pDrawEnt);

	map = (groundTile*)malloc(sizeof(groundTile)*DWARPO_GRID_HEIGHT*DWARPO_GRID_WIDTH);
	
	groundTile* curr;
	for (int w = 0; w < DWARPO_GRID_WIDTH;w++) {
		for (int h = 0; h < DWARPO_GRID_HEIGHT; h++) {
			curr = getTileAt(w, h);
			curr->drawableEntity.drawObjectsSize = 2;
			curr->drawableEntity.drawObjects = (DrawObject**)calloc(2,sizeof(DrawObject*));
			this->viewcontroller->constructGrassTileEntity(&curr->drawableEntity);
			curr->drawableEntity.x = w * this->viewcontroller->tileSize();
			//the view gets built from top to bottom --> thus up is down and vice versa
			curr->drawableEntity.y = h * this->viewcontroller->tileSize();
			//add the tile representation to the viewcontroller

			this->viewcontroller->addEntityL(&curr->drawableEntity, 0);
			

			ListElem<DrawableEntity>* p;
			p = viewcontroller->drawEntities->firstListElem();

		}
	}




}
