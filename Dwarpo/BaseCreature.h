#pragma once
#include"groundTile.h"

class BaseCreature {

public:

	float baseSpeed = 1.0f;
	
	float huntingSpeed = 1.0f;
	
	float fleeingSpeed = 1.0f;
	
	void roam();
	
	void initSpeed();
};