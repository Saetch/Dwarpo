#pragma once
#include "Omnivore.h"
#include "Personality.h"
#include "Job.h"
#include "Inventory.h"

class Dwarf : Omnivore {

	float baseSpeed;

	float fleeingSpeed;

	float huntingSpeed;

	float carryStrength;

	Personality* personality;

	Inventory* p_inventory;

	float* thirst;

	float* sanity;

	float* dirtieness;

	//is the dwarf fat? Overweight dwarfs need more time to pass each other on the same field
	float walkTroughModifier;

	//professin = mason,lumber,woodworker etc.
	int* profession;

	//job = extract this particular resorce from there
	Job* job;

	void initDwarf();

	void initSpeed();

	void initStrength();

};