#pragma once
#include "Structure.h"
#include "SpriteManager.h"
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
		ret = D2D1::RectF(BufferTileSize, BufferTileSize, BufferTileSize*5, BufferTileSize*6);
	}
	Dwarf_BaseHouse(float x, float y, float tileSize){
		this->xPos = x;
		this->yPos = y;
		animated = false;
		printf_s("TILESIZE: %f\n", tileSize);
		printf_s("House:  %f --> %f\n" , xPos, yPos);
		printf_s("H: %f --> %f", tileSize * xPos, tileSize * yPos);
		targetRect = D2D1::RectF(tileSize*xPos, tileSize*yPos-5*tileSize, tileSize*xPos+4*tileSize, tileSize*yPos);
		

		//this might be a good place to make the represented tiles solid/blocked
	}
	const std::tuple<short, short> getOffsets() {
		return { 3,-4 };
	}

	inline Entity* getLinkedEntities(int* size) {
		return NULL;
	}
};

