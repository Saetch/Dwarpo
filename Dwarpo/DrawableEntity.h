#pragma once
#include "DrawObject.h"
#define DRAPO_ENTITY_TYPE_STATIC 4
#define DRAPO_ENTITY_TYPE_PURE_STATIC 5


class DrawableEntity
{
public:
	//Bildschirmkoordinaten der Entity
	float x = 0;
	float y = 0;



	DrawObject** drawObjects;
	int drawObjectsSize;

	DrawableEntity() {};
	virtual ~DrawableEntity() {};

	DrawObject** getObjectStart() {
		return drawObjects;
	}
	virtual void addDrawObject(int type, int color, float x1, float y1, float x2, float y2, float width) = 0;
	virtual int getType() = 0;
	virtual bool isAnimated() = 0;
};

