#include "Dwarf.h"
#include <stdlib.h>

void Dwarf::initDwarf()
{
	initSpeed();
	initStrength();
	initName();


}


void Dwarf::initSpeed() {
	float speedModifier = 0.0f;
	int random = rand();
	if (random % 5 == 0) {
		if (random % 2 == 0) {
			speedModifier = (float)(random % 3);
		}
		else {
			speedModifier = (float)(1 / (random % 3));
		}
		baseSpeed *= speedModifier;
		huntingSpeed *= speedModifier;
		fleeingSpeed *= speedModifier;
	}

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

void Dwarf::init()
{

	//TODO 
}

void Dwarf::tick()
{
	//TODO
}

bool Dwarf::changeState() {
	//TODO

	return false;
}
