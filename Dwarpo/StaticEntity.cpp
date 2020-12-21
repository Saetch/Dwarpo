#include "StaticEntity.h"
#include <malloc.h>
//static entities sollen sich nicht bewegen (auf dem Bildschirm),
//also sind für den Background und UI Elemente gemacht und haben keine Referenz auf ein Model-Objekt

StaticEntity::StaticEntity(const int size)
{
	drawObjectsSize = size;
	drawObjects = (DrawObject*)calloc(size, sizeof(DrawObject));
}

StaticEntity::~StaticEntity(){


	free(drawObjects);
}

void StaticEntity::addDrawObject(int type, int color, float x1, float y1, float x2, float y2, float width)
{


	DrawObject* curr = drawObjects;
	//niedrigstes NULL --> noch nicht beschriebenes array Element
	while (curr->color != NULL) {
		curr++;
	}
	curr->drawType = type;
	curr->color = color;
	curr->setX1(x1);
	curr->setY1(y1);
	curr->setX2(x2);
	curr->setY2(y2);
	curr->width = width;
	
}



