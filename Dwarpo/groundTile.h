#pragma once
#include "StaticEntity.h"


class groundTile
{
public:

	bool isSolid;

	float groundSpeedModifier = 1.0f;

	StaticEntity drawableEntity;

	float waterLevel = 0.0f;

	float lavaLevel = 0.0f;

	bool isHomeArea;

	float dirtienessLevel;


};

