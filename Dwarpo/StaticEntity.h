#pragma once
#include "DrawableEntity.h"
class StaticEntity: public DrawableEntity
{
public:
	virtual bool isAnimated() = 0;
	inline int getType() {
		return DRAPO_ENTITY_TYPE_STATIC;
	}
};

