#include "MapGenerator.h"
#include "LinkedChunk.h"
#include "QueueTypeLinkedList.h"
#include "DPEngine_instance.h"

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
	LinkedChunk* curr = chunkMap;
	LinkedChunk* retChunk = 0;

	int linkedChunks = 0;
	stack->push(curr);
	linkedChunks++;
	while (linkedChunks < chunkSize) {
		printf_s("LinkedChunks: %d\n", linkedChunks);
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
	DPEngine_instance* DwarpoEngine = engine;

	for (int i = 0; i < chunkSize; i++) {
		DwarpoEngine->ok();
		//DwarpoEngine->drawDebugChunktoBkgrnd(chunkMap[i],  i % chunkWidth, i / chunkWidth);
	}

	//TODO add rocks according to map generated


	delete[] chunkMap;
}
