#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"
#include <d2d1.h>
#ifndef TILESIZE
#define TILESIZE 30
#endif

class Dwarf;

class BaseCreature;

class DPEngine_instance;

class baseTile
{
public:



	bool isSolid = 1;

	
	D2D1_RECT_F drawRect;
	StaticEntity drawableEntity = NULL;

	inline D2D1_RECT_F getRect(int ran) {
		return drawRect;
	}

	inline void destroyBlock() {

			printf_s("WARN -- DestroyBlock called, but not yet implemented\n");

	}

	baseTile(int type = NULL) {
		init(type);
	
	}

	virtual void init(int type = NULL) {

		int ran = (rand()) % 4;
		drawRect = D2D1::RectF(ran * TILESIZE, 0.0f, (ran + 1) * TILESIZE, TILESIZE);
		return;



	}




};

