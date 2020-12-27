#pragma once
#include "BaseCreature.h"

class BaseCreature;

 class Omnivore : public BaseCreature {
 public:

	 virtual void virt() = 0;

	float baseSpeed = 1.0f;

	float fleeingSpeed = 1.0f;

	float huntingSpeed = 1.0f;

	float baseAggroValue = 1.0f;
};