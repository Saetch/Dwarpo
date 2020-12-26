#pragma once
#include "Omnivore.h"
#include "Personality.h"
#include "Job.h"
#include "Inventory.h"
#include <string>
using namespace std;


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
	Job job;

	string name;

	void initDwarf();

	void initSpeed();

	void initStrength();

	inline void initName() {
		string arr[] = { "Agegg Darkroar","Ugohm Starkarm","Huladrahr Paleroar","Kaldougirn Cragpike","Sargokunn Smugroar",
			"Urkognium Slowbeard","Hjengol Marblepass","Akond Deepsteel","Krernen Boulderrock","Eliggs Mountainhost" };
		int random = rand() % (sizeof(arr) / sizeof(*arr));
		name = arr[random];
	}
};