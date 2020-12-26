#include "Dwarf.h"
#include <stdlib.h>


float baseSpeed = 1.0f;

float fleeingSpeed = 1.2f;

float huntingSpeed = 1.1f;

float carryStrength = 1.0f;

Personality* personality;

Inventory* p_inventory;

float thirst = 0.0f;

float sanity;

float dirtieness;

float walkTroughModifier;

int profession;

Job job;

void Dwarf::initDwarf()
{
	initSpeed();


}


void Dwarf::initSpeed() {
	float speedModifier;
	int random = rand();
	if (random % 5 == 0) {
		if (random % 2 == 0) {
			speedModifier = random % 3;
		}
		else {
			speedModifier = 1 / (random % 3);
		}
	}
	baseSpeed *= speedModifier;
	huntingSpeed *= speedModifier;
	fleeingSpeed *= speedModifier;

}

void Dwarf::initStrength()
{
	float carryStrengthModifier;
	int random = rand();
	carryStrengthModifier = 1 / (random % 5 + 1);
	if (random % 2 == 0) {
		carryStrength -= carryStrengthModifier;
	}
	else {
		carryStrength -= carryStrengthModifier;
	}


}