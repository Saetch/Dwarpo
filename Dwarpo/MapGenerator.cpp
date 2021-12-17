#include "MapGenerator.h"
#include "LinkedChunk.h"
#include "QueueTypeLinkedList.h"
#include "DPEngine_instance.h"
#include "MCave.h"
#include "KnightD.h"

#define CAVE_CHANCE 17

//if the given algorithm runs over the field more than once, more interesting caves will form!
#define CAVE_LAYERS 21

#define MAX_START_DEPTH 43

//make sure, these are in the correct ranges!
#define MIN_CAVE_WIDTH 2
//#define MAX_CAVE_WIDTH 
//#define MAX_CAVE_HEIGHT
#define MIN_CAVE_HEIGHT 3
bool vecContains(void* vecP,  baseTile** const elemP);

baseTile* MapGenerator::generateGameField(DPEngine_instance* viewcntrl) {
	//initialize background
	*this->map = {};
	(* this->map).reserve(DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH);
	for (int i = 0; i < DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH; i++) {
		baseTile* newT = new baseTile();
		(*this->map).push_back(newT);
	}

	baseTile* curr;
	for (int h = 0; h < DWARPO_GRID_HEIGHT; h++) {
		for (int w = 0; w < DWARPO_GRID_WIDTH; w++) {

			//SEE model->getTileAt
			curr = (*this->map)[w + h * DWARPO_GRID_WIDTH];
			curr->init();


		}
	}

		unsigned int y_dummy;
        unsigned short chunkHeight;
		unsigned short chunkWidth;
		chunkWidth = (rand() % 31) + 20;
		chunkHeight = (rand() % 11) + 5;
		unsigned int xl;
		unsigned int yl;
		unsigned int startY;
		baseTile** toOverride;

		QueueTypeLinkedList<MCave>* caveList = new QueueTypeLinkedList<MCave>();

		bool debug = true;
		do {
			for (unsigned int algoLayer = 0; algoLayer < CAVE_LAYERS; ++algoLayer) {
				//Generation of actual caves via simple method, by dividing into chunks
				//TODO, this would look nicer, if they weren't just x*y sized!
				for (unsigned int chunkY = 0; chunkY + chunkHeight < DWARPO_GRID_HEIGHT; chunkY += chunkHeight) {

					for (unsigned int chunkX = 0; chunkWidth + chunkX < DWARPO_GRID_WIDTH; chunkX += chunkWidth) {
						//give a 1/CAVE_CHANCE chance of actually developing a cave in a given chunk
						if (rand() % CAVE_CHANCE != 0) {
							continue;
						}

						//randomize the height and width of the cave,somewhat
						xl = MIN_CAVE_WIDTH + (rand() % ((chunkWidth - (MIN_CAVE_WIDTH + 3)) ));
						yl = MIN_CAVE_HEIGHT + (rand() % ((chunkHeight -( MIN_CAVE_HEIGHT + 3))> 0 ? (chunkHeight - (MIN_CAVE_HEIGHT + 3)): 1)) ;
						if (xl > chunkWidth / 2 && rand() % 2 != 0) {
							xl /= 2;
						}
						debug = false;
						startY = chunkY + rand() % (chunkHeight + 1 - yl);
						for (unsigned int actualX = chunkX + rand() % (chunkWidth + 1 - xl); xl > 0; --xl, ++actualX) {
							y_dummy = yl;
							for (unsigned int actualY = startY; y_dummy > 0; --y_dummy, ++actualY) {
								/*if (actualX + actualY * DWARPO_GRID_WIDTH > (DWARPO_GRID_WIDTH) * (DWARPO_GRID_HEIGHT - 1)) {
									continue;
								}
								toOverride = &(*this->map)[actualX + actualY * DWARPO_GRID_WIDTH];
								delete *toOverride;
								*toOverride = new caveBasic();*/
								if (getAtChecked(actualX, actualY, &toOverride)) {
									delete* toOverride;
									*toOverride = new caveBasic();
								}

								if (rand() % 70 == 0) {
									startY += (rand() % 5) - 2;
								}

							}

						}






						chunkWidth = (rand() % 31) + 20;

					}



					//chose a value from 5 to 15 for the height of the chunks and thus for the height of possible caves in these rows 

					chunkHeight = (rand() % 7) + 5;














				}
			}
		} while (!canPlaceStartBase(&caveList, viewcntrl));
		

		//TODO after initializing the field in such a way, that a baseHouse can be placed, it needs to be placed aswell
		//implement chosing a correct spot, when the dwarf base house is updated. Also consider spawning a few workers
		//therefor return the correct baseTile that represents the actual startPoint of the house!






	baseTile* ret = (*this->map)[0];
	return ret;
}


//safe method for getting the baseTile** at the index
bool MapGenerator::getAtChecked(int w, int h, baseTile*** toPoint) {
	if (w + h * DWARPO_GRID_WIDTH < 0 || w + h * DWARPO_GRID_WIDTH >= DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH) {
		return false;
	}



	*toPoint = &((*this->map)[w + h * DWARPO_GRID_WIDTH]);

	return true;
}

MCave* completeCave(int x, int y, void* alreadyProcessedTilesVectorPointer, void* mapPointer, DPEngine_instance* viewcntrl);


bool MapGenerator::canPlaceStartBase(void* l, DPEngine_instance* viewcntrl)
{
	//TODO REFACTOR THIS. This should be a data field of viewcntrl, so it can be used in cave discovery in the future.
	QueueTypeLinkedList<MCave>* list = *(static_cast<QueueTypeLinkedList<MCave>**>(l));

	if (list->getSize()>0) {
		printf_s("PossibleCaveList overwritten ... size: %d\n", list->getSize());

		while (list->getSize() > 0) {
			delete list->pop();
		}
	}
	std::vector<baseTile*> alreadyProcessedTiles;
	baseTile** currentTile;

	// +2 / +3, because that is the minimum caveSize, and thus less tiles need to be checked, but still all caves will be visited
	for (int y = 0; y < MAX_START_DEPTH; y+= MIN_CAVE_HEIGHT){
		for (int x = 0; x < DWARPO_GRID_WIDTH; x+= MIN_CAVE_WIDTH) {
			if (this->getAtChecked(x, y, &currentTile)) {
				//printf_s("%d / %d    SOLID: ",x,y);
				//printf_s(((*currentTile)->isSolid) ? "true\n" : "false\n");
				if (!((*currentTile)->isSolid) &&  !vecContains(&alreadyProcessedTiles, currentTile)) {



					list->push(completeCave(x, y, &alreadyProcessedTiles, &(this->map), viewcntrl));
					list->get(0).tiles.resize(list->get(0).tiles.size());


					break;
					if (rand() % 2 == 0) {
						return true;
					}
				}

			}
		}
	}



	return true;
}

bool getAtCheckedFunc(int w, int h, baseTile** toPoint, void* mapPointer) {
	if (w + h * DWARPO_GRID_WIDTH < 0 || w + h * DWARPO_GRID_WIDTH >= DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH || w >= DWARPO_GRID_WIDTH || h >= DWARPO_GRID_HEIGHT || w <0 || h < 0) {
		return false;
	}
	std::vector<baseTile*>* map = *(static_cast<std::vector<baseTile*>**>(mapPointer));
	*toPoint = ((*map)[w + h * DWARPO_GRID_WIDTH]);

	return true;
}

MCave* completeCave(int x, int y, void* alreadyProcessedTilesVectorPointer, void* mapPointer, DPEngine_instance* viewcntrl) {
	std::vector<baseTile*>* processedTiles = (static_cast<std::vector<baseTile*>*>(alreadyProcessedTilesVectorPointer));
	std::vector<baseTile*>* map = *(static_cast<std::vector<baseTile*>**>(mapPointer));

	baseTile* currentTile;
	//add the 4 neighboring tiles to the list of Tiles to check
	if (getAtCheckedFunc(x, y, &currentTile, &map)) {
		MCave* ret = new MCave(currentTile);
		if (vecContains(processedTiles, &currentTile)) {
			return ret;
		}


		processedTiles->push_back(currentTile);
		//use char to store 4 bools
		byte con = 0b0000;
		if (getAtCheckedFunc(x+1, y, &currentTile, &map)) {
			if (!(currentTile->isSolid) && !vecContains(processedTiles, &currentTile)) {
				con += 0b0001;
			}
		}
		if (getAtCheckedFunc(x - 1, y, &currentTile, &map)) {
			if (!(currentTile->isSolid) && !vecContains(processedTiles, &currentTile)) {
				con += 0b0010;
			}
		}
		if (getAtCheckedFunc(x, y+1, &currentTile, &map)) {
			if (!(currentTile->isSolid) && !vecContains(processedTiles, &currentTile)) {
				con += 0b0100;
			}
		}
		if (getAtCheckedFunc(x , y -1, &currentTile, &map)) {
			if (!(currentTile->isSolid) && !vecContains(processedTiles, &currentTile)) {
				con += 0b1000;
			}
		}
		if (con & 0b0001) {
				ret->swallow(completeCave(x + 1, y, processedTiles, &map, viewcntrl));

		}
		if (con & 0b0010) {
				ret->swallow(completeCave(x - 1, y, processedTiles, &map, viewcntrl));

		}
		if (con & 0b0100) {
				ret->swallow(completeCave(x , y+1, processedTiles, &map, viewcntrl));

		}
		if (con & 0b1000) {
				ret->swallow(completeCave(x , y-1, processedTiles, &map, viewcntrl));

		}






		return ret;
	}
	else {
		printf_s("UNEXPECTED ACTION IN MAPGENERATOR->COMPLETECAVE!!\n");
		return (new MCave());
	}



	
	
}


bool vecContains(void* vecP, baseTile** elemP) {
	std::vector<baseTile*>* vec = (static_cast<std::vector<baseTile*>*>(vecP));
	
	for (auto pInVec : *vec) {
		if (pInVec == *elemP) {
			return true;
		}
	}
	return false;

}



void MapGenerator::generateMountains(DPEngine_instance* engine)
{
	if (this->wallWidth > (this->chunkSize / 2)) {
		printf_s("ERR!: Erroneous wallWidth and chunkSize declared for map generation!\n");
		return;
	}

	int chunkWidth = this->width / this->chunkSize;
	if (this->width % this->chunkSize > 0) {
		chunkWidth++;
	}

	int chunkHeight = this->height / this->chunkSize;
	if (this->height % this->chunkSize > 0) {
		chunkHeight++;
	}

	//generating gameChunks for everyTile
	LinkedChunk* chunkMap = new LinkedChunk[chunkWidth*chunkHeight];
	int left;
	int top;
	int right;
	int bottom;
	int chunkSize = chunkWidth * chunkHeight;

	//connecting all the chunks to each other, so they know which chunk is top/left/right/bot of them!
	for (int i = 0; i < chunkSize; i++) {
		left = i - 1;
		right = i + 1;
		top = i - chunkWidth;
		bottom = i + chunkWidth;
		if (!(i%chunkWidth == 0)) {
			chunkMap[i].west = &chunkMap[left];
		}
		if (!(i%chunkWidth == chunkWidth -1)) {
			chunkMap[i].east = &chunkMap[right];
		}
		if (!(i / chunkWidth == chunkHeight - 1)) {
			chunkMap[i].south = &chunkMap[bottom];
		}
		if (!(i / chunkWidth == 0)) {
			chunkMap[i].north = &chunkMap[top];
		}
	}

	//make possible link to every chunk

	QueueTypeLinkedList<LinkedChunk>* stack = new QueueTypeLinkedList<LinkedChunk>();


	//DBG
	QueueTypeLinkedList<LinkedChunk>* allChunks = new QueueTypeLinkedList<LinkedChunk>();
	LinkedChunk* curr = chunkMap;
	//this pointer is used as an argument for clearRandomBorder and thus will be changed to point to the next reached Chunk
	LinkedChunk* retChunk = 0;

	int linkedChunks = 0;
	stack->push(curr);
	linkedChunks++;
	while (linkedChunks < chunkSize) {
		if (curr->clearRandomBorder(retChunk)) {
			curr = retChunk;
			stack->push(curr);
			linkedChunks++;
		}
		else {
			curr = stack->pop();
		}
	}
	//DEBUG
	for (int i = 0; i < chunkSize; i++) {
		allChunks->pushBack(&chunkMap[i]);
	}
	DPEngine_instance* DwarpoEngine = engine;
	DwarpoEngine->drawDebugChunks(allChunks, chunkWidth, chunkHeight);

	delete allChunks;
	delete stack;
	delete[] chunkMap;
}
