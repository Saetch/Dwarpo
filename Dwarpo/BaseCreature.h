#pragma once
#include"groundTile.h"
#include "Entity.h"
#include <d2d1.h>

#define STATE_IDLE 1
#define STATE_MOVING 2

class BaseCreature :public Entity{

public:

	D2D_RECT_F frameRect;

	float baseSpeed = 1.0f;
	
	float huntingSpeed = 1.0f;
	
	float fleeingSpeed = 1.0f;

	//functions need to be virtual, otherwise Collections of type <BaseCreature> will use BaseCreature implementation instead of the child class'
	
	virtual void roam();
	
	virtual void initSpeed();

	bool isDead;

	bool isUnconscious;

	//pure virtual function to make this non-instantiable
	virtual bool changeState() = 0;

	virtual void tick();

};