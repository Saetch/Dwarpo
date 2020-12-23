#pragma once
#include <windows.h>
#include <stdio.h>
#include "BaseWindow.h"
#include "../QueueTypeLinkedList.h"

#pragma comment(lib, "user32.lib")

#define WM_DWARPO_DRAW 0x2411
class DrawableEntity;

template <class DERIVED_TYPE>
class DwarPoEngine : public BaseWindow<DERIVED_TYPE> {
public:
	//definiert Displaygröße in dipx
	float width;
	float height;

	float left;
	float right;
	float top;
	float bottom;

	//definiert Camera-offset
	float disX;
	float disY;

	QueueTypeLinkedList<DrawableEntity>* drawEntities;
	virtual void addEntityL(DrawableEntity* pnewE, unsigned short int layer) = 0;
	virtual int onCreate() = 0;
	virtual int onUpdate() = 0;

protected:

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};