#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"
#include <d2d1.h>

class Dwarf;

class BaseCreature;

class DPEngine_instance;

class baseRock
{
public:




	unsigned short graphicRect;

	QueueTypeLinkedList<Dwarf> dwarfs;

	QueueTypeLinkedList<BaseCreature> enemy;

	bool isAnimated = 0;

	bool isSolid = 1;

	bool isBlocked = 0;

	float groundSpeedModifier = 1.0f;

	StaticEntity drawableEntity = NULL;

	float waterLevel = 0.0f;

	float lavaLevel = 0.0f;

	bool isHomeArea = 0;

	float dirtienessLevel = 0.0f;

	inline D2D1_RECT_F getRect(float tileSize) {
		return D2D1::RectF(graphicRect * tileSize, 0.0f, (graphicRect + 1) * tileSize, tileSize);
	}

	inline void destroyBlock() {
		if (!isBlocked) {
			printf_s("WARN -- DestroyBlock called on non-blocked groundTile!\n");
		}
		graphicRect++;
		isBlocked = false;

	}

	baseRock(int type) {
		init(type);
	}

	void init(int type) {



		graphicRect = (rand()) % 4;
		return;


	}




};

