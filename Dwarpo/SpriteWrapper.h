#pragma once
#include <d2d1.h>
class SpriteWrapper
{	
	
	D2D1_RECT_F srcRect;
	unsigned int width;
	unsigned int height;
	

	inline D2D1_RECT_F getSrcRect() {
		return srcRect;
	}

	inline unsigned int getWidth() {
		return width;
	}

	inline unsigned int getHeight() {
		return height;
	}



};

