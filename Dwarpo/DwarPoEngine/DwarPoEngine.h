#pragma once
#include <windows.h>
#include <stdio.h>
#include "BaseWindow.h"
#include "../QueueTypeLinkedList.h"

#pragma comment(lib, "user32.lib")


class DrawableEntity;

template <class DERIVED_TYPE>
class DwarPoEngine : public BaseWindow<DERIVED_TYPE> {
public:
	//definiert Displaygröße in px
	int width;
	int height;


	//definiert Camera-offset
	float disX;
	float disY;

	QueueTypeLinkedList<DrawableEntity>* drawEntities;

	virtual int onCreate() = 0;
	virtual int onUpdate() = 0;

protected:

	virtual PCWSTR  ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};