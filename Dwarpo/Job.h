#pragma once
#include "groundTile.h"

class Job {

	bool isReservedByDwarf = false;

	groundTile* position;

	Dwarf* reservedBy;

};
