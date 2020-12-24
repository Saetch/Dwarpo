#pragma once
#include "BaseCreature.h"

class Carnivore : BaseCreature {

	float baseSpeed;

	float huntingSpeed;

	float baseAggroValue;

	float aggroValueModifier;

	void hunt();

};