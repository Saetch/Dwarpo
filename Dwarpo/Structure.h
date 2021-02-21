#pragma once
#include "Entity.h"

class Structure : public Entity
{
public:

	D2D1_RECT_F targetRect;

	//structures are to be placed on the grid and thus only have whole numbers as x/y coordinates
	//most top left field, does not need to be part of the structure per se
	
	virtual inline D2D1_RECT_F getFrameRect() = 0;

	//if the Structure is animated, a non-interactable entity needs to be spawned aswell
	virtual Entity* getLinkedEntities(int* size) = 0;
	
};

