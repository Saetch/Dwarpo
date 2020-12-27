#pragma once
#include"groundTile.h"
#include "Entity.h"

class BaseCreature:public Entity {

public:
	BaseCreature(){}

	float baseSpeed = 1.0f;
	
	float huntingSpeed = 1.0f;
	
	float fleeingSpeed = 1.0f;
	
	void roam();
	
	void initSpeed();
};