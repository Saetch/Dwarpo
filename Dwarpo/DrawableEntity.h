#pragma once
#include "DrawObject.h"
#define DRAPO_ENTITY_TYPE_STATIC 4
#define DRAPO_ENTITY_TYPE_PURE_STATIC 5


class DrawableEntity
{
public:
	//Bildschirmkoordinaten der Entity
	float x;
	float y;

	//LAYER definiert, wann die Entity gezeichnet wird ( Hintergrund -> Mitte -> Vordergrund )

	const int LAYER;

	DrawObject* drawObjects;
	int drawObjectsSize;


	DrawObject* getObjectStart() {
		return drawObjects;
	}
	virtual int getType() = 0;
	virtual bool isAnimated() = 0;
};

