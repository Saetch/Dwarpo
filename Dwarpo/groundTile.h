#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"
#include "Entity.h"


class groundTile
{
public:

	QueueTypeLinkedList<Entity> content;

	bool isSolid;

	bool isObstruted;

	float groundSpeedModifier = 1.0f;

	StaticEntity drawableEntity;

	float waterLevel = 0.0f;

	float lavaLevel = 0.0f;

	bool isHomeArea;

	float dirtienessLevel;
};

