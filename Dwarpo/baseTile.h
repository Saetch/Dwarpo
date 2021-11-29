#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"
#include <d2d1.h>
#include "SpriteManager.h"


class baseTile
{
public:




	unsigned short graphicRect = 0;

	bool isSolid = 1;



	StaticEntity drawableEntity = NULL;



	virtual inline D2D1_RECT_F getRect() {
		return D2D1::RectF(graphicRect * BufferTileSize, 0.0f, (graphicRect + 1) * BufferTileSize, BufferTileSize);
	}

	inline void destroyBlock() {

			printf_s("WARN -- DestroyBlock called, but not yet implemented\n");

	}

	baseTile(int type = NULL) {
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

