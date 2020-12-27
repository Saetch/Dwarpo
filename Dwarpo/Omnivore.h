#pragma once
#include "BaseCreature.h"

 class Omnivore : BaseCreature {
 public:
	 Omnivore() {};

	float baseSpeed = 1.0f;

	float fleeingSpeed = 1.0f;

	float huntingSpeed = 1.0f;

	float baseAggroValue = 1.0f;
};