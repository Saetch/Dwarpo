#include "StaticEntity.h"
//static entities sollen sich nicht bewegen (auf dem Bildschirm),
//also sind f�r den Background und UI Elemente gemacht und haben keine Referenz auf ein Model-Objekt

StaticEntity::StaticEntity(const int size)
{
	drawObjectsSize = size;
}


void StaticEntity::addDrawObject(DrawObject newO)
{
}

bool StaticEntity::isAnimated()
{
	return false;
}
