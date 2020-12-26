#include "BaseCreature.h"

float baseSpeed = 1.0f;

float fleeingSpeed = 1.2f;

float huntingSpeed = 1.1f;

void BaseCreature::roam()
{
}

void BaseCreature::initSpeed() {
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

