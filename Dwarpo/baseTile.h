#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"
#include <d2d1.h>
#include "SpriteManager.h"


class baseTile
{
public:


	const float x = 0;
	const float y = 0;

	unsigned short graphicRect = 0;

	bool isSolid = true;



	StaticEntity drawableEntity = NULL;



	virtual inline D2D1_RECT_F getRect() {
		return D2D1::RectF(graphicRect * BufferTileSize, 0.0f, (graphicRect + 1) * BufferTileSize, BufferTileSize);
	}

	inline void destroyBlock() {

			printf_s("WARN -- DestroyBlock called, but not yet implemented\n");

	}

	baseTile(int xVal, int yVal, int type = NULL) :x(xVal), y(yVal) {
		;
	}

	void initN(int type = NULL) {

		graphicRect = (rand()) % 4;
		printf_s("baseTileConstructorN called");

		return;
	}


	virtual void init(int type = NULL) {

		graphicRect = (rand()) % 4;

		return;


	}




};

