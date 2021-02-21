#pragma once
#include "Structure.h"
class Dwarf_BaseHouse: public Structure
{
public:

	inline static D2D1_RECT_F ret;


	inline static D2D1_RECT_F getFrameRect_static() {
		 return ret;
	}


	inline void tick() {
		return;
	}

	inline D2D1_RECT_F* getTargetRect() {
		return &(this->targetRect);
	}

	inline D2D1_RECT_F getFrameRect() {
		return Dwarf_BaseHouse::getFrameRect_static();
	}

	inline static void init() {
		ret = D2D1::RectF(30.0f, 30.0f, 150.0f, 180.0f);
	}
	Dwarf_BaseHouse(float x, float y, float tileSize) {
		this->xPos = x;
		this->yPos = y;
		animated = false;
		targetRect = D2D1::RectF(tileSize*xPos, tileSize*yPos-150.0f, tileSize*xPos+120.0f, tileSize*yPos);
		

		//this might be a good place to make the represented tiles solid/blocked
	}

	inline Entity* getLinkedEntities(int* size) {
		return NULL;
	}
};

