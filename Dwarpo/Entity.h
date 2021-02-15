#pragma once
#include <D2D1.h>
#include <mutex>
#include <string>
class Entity
{
public:

	//frame to be displayed by the game engine, for fast access
	//mutexed since 2 different thread have access to this
	D2D_RECT_F* currentFrame;
	std::mutex frameMutex;
	//how often this Entity was checked for Frame updates.
	unsigned short tick_count = 0;

	//virtual void init() = 0;

	virtual void tick() = 0;

	float xPos=0.0f;

	float yPos = 0.0f;

	bool animated = true;

	virtual std::string getType() {
		return "Entity";
	}
};

