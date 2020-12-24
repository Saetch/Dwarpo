#pragma once
#include "Omnivore.h"

class Dwarf : Omnivore{

	int* p_inventory;

	float* thirst;

	float* sanity;

	float* dirtieness;

	float baseSpeed;

	float fleeingSpeed;

	float huntingSpeed;

	float carryStrength;

	int* personality;

	//mason,lumber,woodworker
	int* profession;

	//extract this particular resorce from there
	int* job;
};