#pragma once
#include "DrawableEntity.h"
class StaticEntity: public DrawableEntity
{
private:
	bool Animated = false;
public:

	StaticEntity(const int size);
	virtual ~StaticEntity()=0;


	void addDrawObject(DrawObject newO);

	virtual bool isAnimated();


	inline int getType() {
		return DRAPO_ENTITY_TYPE_STATIC;
	}
};

