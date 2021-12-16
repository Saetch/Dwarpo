#pragma once
#include <vector>


class baseTile;
struct TupleI {
	unsigned int x;
	unsigned int y;
};

struct TupleF {
	float x;
	float y;
};


class MCave
{

public:
	std::vector<baseTile*> tiles;

	inline void swallow(MCave* o) {
		for (auto tile : o->tiles) {
			this->tiles.push_back(tile);
		}
	}

	MCave(baseTile* start = NULL) {
		if (start) {
			tiles.push_back(start);
		}
	}
};



