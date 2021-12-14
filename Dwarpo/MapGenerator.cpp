#include "MapGenerator.h"
#include "LinkedChunk.h"
#include "QueueTypeLinkedList.h"
#include "DPEngine_instance.h"


void MapGenerator::generateGameField() {
	//initialize background
	*this->map = {};
	(* this->map).reserve(DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH);
	for (int i = 0; i < DWARPO_GRID_HEIGHT * DWARPO_GRID_WIDTH; i++) {
		baseTile* newT = new baseTile();
		(*this->map).push_back(newT);
	}

	baseTile* curr;
	for (int w = 0; w < DWARPO_GRID_WIDTH; w++) {
		for (int h = 0; h < DWARPO_GRID_HEIGHT; h++) {

			//SEE model->getTileAt
			curr = (*this->map)[w + h * DWARPO_GRID_WIDTH];
			curr->init();







		}
	}
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
	//DwarpoEngine->drawDebugChunks(allChunks, chunkWidth, chunkHeight);

	delete allChunks;
	delete stack;
	delete[] chunkMap;
}
