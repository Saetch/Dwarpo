#pragma once
#include "groundTile.h"
#include <string>
using namespace std;

class Job {

	bool isReservedByDwarf = false;

	groundTile* position;

	string jobToString();
	 
};
