#pragma once
#include"groundTile.h"

class BaseCreature {

	groundTile* map;

	float health = 1.0f;

	float hunger = 0.0f;

	float* xPos;

	float* yPos;

	float baseSpeed;
	float huntingSpeed;
	float fleeingSpeed;

	//how much are ceatures slowed down if passing each other on the same field?
	float baseWalkTrough = 0.5f;

	void roam();
	void initSpeed();
};