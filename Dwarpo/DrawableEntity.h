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



	DrawObject* drawObjects;
	int drawObjectsSize;

	DrawableEntity() {};
	virtual ~DrawableEntity() = 0;

	DrawObject* getObjectStart() {
		return drawObjects;
	}
	virtual int getType() = 0;
	virtual bool isAnimated() = 0;
};

