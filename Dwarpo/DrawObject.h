#pragma once

#define DrawO_LINE		     0x15
#define DrawO_RECT_FILL		 0x29
#define DrawO_RECT_DRAW		 0x2a


//update this number if more colors get added
#define DRAW_LOADCOLOR_NUM 9

#define DrawO_COLOR_WHITE	  0x001
#define DrawO_COLOR_BROWN	  0x002
#define DrawO_COLOR_BLUE	  0x003
#define DrawO_COLOR_RED		  0x004
#define DrawO_COLOR_YELLOW    0x005
#define DrawO_COLOR_ORANGE	  0x006
#define DrawO_COLOR_GREEN	  0x007
#define DrawO_COLOR_BLACK     0x008
#define DrawO_COLOR_LIGHTGREY 0x009

class DrawObject
{
public:
	//0 bis 65535
	unsigned short int drawType;
	unsigned short int color;



	inline void setX1(float x);
	inline void setLeft(float left);
	inline float getX1();
	inline float getLeft();


	inline void setY1(float y);
	inline void setRight(float right);
	inline float getY1();
	inline float getRight();


	inline void setX2(float x);
	inline void setTop(float top);
	inline float getX2();
	inline float getTop();


	inline void setY2(float y);
	inline void setBottom(float bottom);
	inline float getY2();
	inline float getBottom();


	inline void setWidth(float newWidth) { width = newWidth; }
	inline float getWidth() { return width; }
	inline void setAngle(float newAngle) { angle = newAngle; }
	inline float getAngle() { return angle; }
	//Vektoren der Endpunkte der Form, in je x und y koordinate für Line, 
	//left, right, up und down für rect
	float x1;
	float y1;
	float x2;
	float y2;


	//breite der Linie bei draw (nicht fill) functions
	float width;
	float angle = 0.0f;
};


inline void DrawObject::setX1(float x)
{
	x1 = x;
}

inline void DrawObject::setLeft(float left)
{
	x1 = left;
}

inline float DrawObject::getX1()
{
	return x1;
}

inline float DrawObject::getLeft()
{
	return x1;
}

inline void DrawObject::setY1(float y)
{
	y1 = y;
}

inline void DrawObject::setRight(float right)
{
	y1 = right;
}

inline float DrawObject::getY1()
{
	return y1;
}

inline float DrawObject::getRight()
{
	return y1;
}

inline void DrawObject::setX2(float x)
{
	x2 = x;
}

inline void DrawObject::setTop(float top)
{
	x2 = top;
}

inline float DrawObject::getX2()
{
	return x2;
}

inline float DrawObject::getTop()
{
	return x2;
}

inline void DrawObject::setY2(float y)
{
	y2 = y;
}

inline void DrawObject::setBottom(float bottom)
{
	y2 = bottom;
}

inline float DrawObject::getY2()
{
	return y2;
}

inline float DrawObject::getBottom()
{
	return y2;
}


