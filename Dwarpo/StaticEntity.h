#pragma once
#include "DrawableEntity.h"
class StaticEntity: public DrawableEntity
{
private:
	bool Animated = false;


	//addDrawObjectP is actually a copy, not an adding of the reference
	void addDrawObjectP(DrawObject* newP);
public:
	StaticEntity(const int size);
	virtual ~StaticEntity();

	void addDrawObject(int type, int color, float x1, float y1, float x2, float y2, float width);
	inline bool isAnimated() { return Animated; }


	inline int getType() {
		return DRAPO_ENTITY_TYPE_STATIC;
	}
};

