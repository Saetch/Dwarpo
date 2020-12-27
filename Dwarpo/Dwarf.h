#pragma once
//#include "BaseCreature.h"
#include "Omnivore.h"
#include "Personality.h"
#include "Job.h"
#include "Inventory.h"
#include <string>

class Dwarf :public Omnivore {

public:

	virtual void virt() {};

	Dwarf() {}

	float baseSpeed = 1.0f;

	float fleeingSpeed = 1.0f;

	float huntingSpeed = 1.0f;

	float carryStrength = 1.0f;

	Personality personality;

	Inventory inventory;

	float hunger = 0.0f;

	float thirst = 0.0f;

	float sanity = 1.0f;

	float dirtieness = 0.0f;

	//is the dwarf fat? Overweight dwarfs need more time to pass each other on the same field
	float walkTroughModifier = 1.0;

	//professin = mason,lumber,woodworker etc.
	//int* profession;

	//job = extract this particular resorce from there
	Job job;

	std::string name;

	void initDwarf();

	void initSpeed();

	void initStrength();

	inline void initName() {
		std::string arr[] = { "Agegg Darkroar","Ugohm Starkarm","Huladrahr Paleroar","Kaldougirn Cragpike","Sargokunn Smugroar",
			"Urkognium Slowbeard","Hjengol Marblepass","Akond Deepsteel","Krernen Boulderrock","Eliggs Mountainhost" };
		int random = rand() % (sizeof(arr) / sizeof(*arr));
		name = arr[random];
	}
};