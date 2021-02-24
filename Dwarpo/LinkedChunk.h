#pragma once
#include <Windows.h>


class LinkedChunk
{
public:
	
	bool northBlocked = true;
	bool eastBlocked = true;
	bool southBlocked = true;
	bool westBlocked = true;

	bool visited = false;

	LinkedChunk* north = NULL;
	LinkedChunk* east = NULL;
	LinkedChunk* south = NULL;
	LinkedChunk* west = NULL;

	inline bool northLinked() {
		return(north);
	}

	inline bool eastLinked() {
		return(east);
	}

	inline bool southLinked() {
		return(south);
	}

	inline bool westLinked() {
		return(west);
	}

	bool clearRandomBorder(LinkedChunk* &p_nextChunk) {
		//use binary coding
		bool visitable[4] = { 0 };
		int amCl = 0;
		if ( northLinked() &&(northBlocked && !north->visited) ){
			visitable[0] = true;
			amCl++;
		}
		if ( eastLinked() &&(eastBlocked && !east->visited) ) {
			visitable[1] = true;
			amCl++;
		}
		if (southLinked() &&(southBlocked && !south->visited) ) {
			visitable[2] = true;
			amCl++;
		}
		if (westLinked() && (westBlocked && !west->visited)) {
			visitable[3] = true;
			amCl++;
		}

		if (amCl == 0) {
			return 0;
		}
		
		int rnd = rand() % amCl;
		rnd++;
		int i = 0;
		while (rnd) {
			if (visitable[i]) {
				rnd--;
			}
			if (rnd == 0) {
				break;
			}
			i++;
		}


		switch (i) {
		case 0:  //north
			northBlocked = false;
			p_nextChunk = north;
			break;
		case 1:  //east
			eastBlocked = false;
			p_nextChunk = east;
			break;
		case 2:  //south
			southBlocked = false;
			p_nextChunk = south;
			break;
		case 3:  //west
			westBlocked = false;
			p_nextChunk = west;
			break;
		}


		return amCl;
	}

};

