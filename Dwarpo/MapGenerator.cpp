#include "MapGenerator.h"
#include "LinkedChunk.h"
#include "QueueTypeLinkedList.h"
#include "DPEngine_instance.h"


#define CAVE_CHANCE 17

//if the given algorithm runs over the field more than once, more interesting caves will form!
#define CAVE_LAYERS 20

baseTile* MapGenerator::generateGameField() {
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



		bool debug = true;
		for (unsigned int algoLayer = 0; algoLayer < CAVE_LAYERS; ++algoLayer) {
			//Generation of actual caves via simple method, by dividing into chunks
			//TODO, this would look nicer, if they weren't just x*y sized!
			for(unsigned int chunkY = 0; chunkY + chunkHeight < DWARPO_GRID_HEIGHT; chunkY += chunkHeight){

				for (unsigned int chunkX = 0; chunkWidth + chunkX < DWARPO_GRID_WIDTH; chunkX += chunkWidth) {
					//give a 1/CAVE_CHANCE chance of actually developing a cave in a given chunk
					if (rand() % CAVE_CHANCE != 0) {
						continue;
					}

					//randomize the height and width of the cave,somewhat
					xl = 2+(rand() % (chunkWidth - 3));
					yl = 2+ ( rand() % (chunkHeight - 2));
					if (xl > chunkWidth / 2 && rand()%2 != 0) {
						xl /= 2;
					}
						debug = false;
						startY = chunkY + rand() % (chunkHeight + 1 - yl);
						for (unsigned int actualX = chunkX +rand() % (chunkWidth + 1 - xl); xl > 0; --xl, ++actualX) {
							y_dummy = yl;
							for (unsigned int actualY = startY; y_dummy > 0; --y_dummy, ++actualY) {
								toOverride = &(*this->map)[actualX + actualY * DWARPO_GRID_WIDTH];
								delete *toOverride;
								*toOverride = new caveBasic();


							}
					
						}
				





					chunkWidth = (rand() % 31) + 20;

					}
					//chose a value from 5 to 15 for the height of the chunks and thus for the height of possible caves in these rows 




				chunkHeight = (rand() % 11) + 5;





                
                

                
        



		
			}
		}
	baseTile* ret = (*this->map)[0];
	return ret;
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
