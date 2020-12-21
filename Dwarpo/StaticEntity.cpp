#include "StaticEntity.h"
//static entities sollen sich nicht bewegen (auf dem Bildschirm),
//also sind für den Background und UI Elemente gemacht

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
