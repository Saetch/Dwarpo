#pragma once
#include "BaseCreature.h"

class Herbivore : BaseCreature {

	float baseSpeed;

	float fleeingSpeed;

	float baseAggroValue;

	void graze();
};
