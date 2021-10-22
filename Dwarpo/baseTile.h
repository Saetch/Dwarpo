#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"
#include <d2d1.h>

class Dwarf;

class BaseCreature;

class DPEngine_instance;

class baseTile
{
public:




	unsigned short graphicRect;

	bool isSolid = 1;



	StaticEntity drawableEntity = NULL;



	inline D2D1_RECT_F getRect(float tileSize) {
		return D2D1::RectF(graphicRect * tileSize, 0.0f, (graphicRect + 1) * tileSize, tileSize);
	}

	inline void destroyBlock() {

			printf_s("WARN -- DestroyBlock called, but not yet implemented\n");

	}

	baseTile(int type = NULL) {
		init(type);
	
	}

	void init(int type = NULL) {

		graphicRect = (rand()) % 4;
		return;



	}




};

