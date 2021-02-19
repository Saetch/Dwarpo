#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"
#include <d2d1.h>

#define GROUNDTILE_GRASS 1

class Dwarf;

class BaseCreature;

class DPEngine_instance;

class groundTile
{
public:




	unsigned short graphicRect;

	QueueTypeLinkedList<Dwarf> dwarfs;

	QueueTypeLinkedList<BaseCreature> enemy;

	bool isAnimated = 0;

	bool isSolid = 0;

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

	groundTile(int type) {
		init(type);
	}

	void init(int type) {
		graphicRect = 0;
		switch (type) {
		case GROUNDTILE_GRASS:


			graphicRect = (rand()) % 4;
			return;
		default:
			printf_s("GROUNDTILE CONSTRUCTED WITH ILLEGAL TYPE");
		}
	}


	

};

