
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "DPEngine_instance.h"
//

void addHouse(DPEngine_instance* viewc);


int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR szCmdLine, int CmdShow)
{
    //initialize random function
    srand(time(NULL));
	

	//initialize
	DPEngine_instance* viewCntrlr = new DPEngine_instance();


    if (!viewCntrlr->Create(L"Circle", WS_OVERLAPPEDWINDOW | WS_VISIBLE))
    {
        return 0;
    }

    //es gibt momentan 8 versch. Farben (#include DrawObject.h::DRAW_LOADCOLOR_NUM)
    viewCntrlr->setBkgrnd((rand() % DRAW_LOADCOLOR_NUM) + 1);


    addHouse(viewCntrlr);


    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        //SendMessage(viewCntrlr->Window(), WM_PAINT, 0, 0);
    }

    return 0;
}


//TODO implement this function, so the Engine knows how to draw a basic house
void addHouse(DPEngine_instance* viewc) {

}