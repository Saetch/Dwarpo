#include "BaseCreature.h"

void BaseCreature::roam()
{
}

void BaseCreature::initSpeed() {
	float speedModifier = 0.0f;
	int random = rand();
	if (random % 5 == 0) {
		if (random % 2 == 0) {
			speedModifier = random % 3;
		}
		else {
			speedModifier = 1 / (random % 3);
		}
		baseSpeed *= speedModifier;
		huntingSpeed *= speedModifier;
		fleeingSpeed *= speedModifier;
	}

}

