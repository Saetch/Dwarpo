#pragma once
#include "groundTile.h"
#include <string>

class groundTile;

class Job {

	bool isReservedByDwarf = false;

	groundTile* position;

	std::string jobToString();
	 
};
