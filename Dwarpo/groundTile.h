#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"


class groundTile
{
public:

	bool isSolid;

	bool isObstruted;

	float groundSpeedModifier = 1.0f;

	StaticEntity drawableEntity;

	float waterLevel = 0.0f;

	float lavaLevel = 0.0f;

	bool isHomeArea;

	float dirtienessLevel;
};

