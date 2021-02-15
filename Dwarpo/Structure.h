#pragma once
#include "Entity.h"

class Structure : public Entity
{
	//structures are to be placed on the grid and thus only have whole numbers as x/y coordinates
	//(the root of the Structure, groundTile that's still a part of the structure)
	virtual void init() {
		animated = false;
	}
};

