#pragma once
#include "StaticEntity.h"
#include "QueueTypeLinkedList_impl.h"

class Dwarf;

class BaseCreature;

class groundTile
{
public:

	QueueTypeLinkedList<Dwarf> dwarfs;

	QueueTypeLinkedList<BaseCreature> enemy;

	bool isSolid;

	bool isBlocked;

	float groundSpeedModifier = 1.0f;

	StaticEntity drawableEntity;

	float waterLevel = 0.0f;

	float lavaLevel = 0.0f;

	bool isHomeArea;

	float dirtienessLevel;
};

