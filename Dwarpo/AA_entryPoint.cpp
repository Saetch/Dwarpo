
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "DPEngine_instance.h"
#include "StaticEntity.h"
#include "DwarpoModel.h"
#include <chrono>
#include <thread>
//
void moveHouse(StaticEntity** pphouse, HWND hwnd);
void addEntity(DPEngine_instance* viewc, StaticEntity* phouse);
int globalBool = 1;
DPEngine_instance* viewCntrlr;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR szCmdLine, int CmdShow)
{
    //Initialisiere random function
    srand((int)time(NULL));

	//initialisiere Engine
	viewCntrlr = new DPEngine_instance();


    if (!viewCntrlr->Create(L"Dwarpo!", WS_OVERLAPPEDWINDOW | WS_VISIBLE))
    {
        return 0;
    }

    //es gibt momentan 8 versch. Farben (#include DrawObject.h::DRAW_LOADCOLOR_NUM)
    //8 ist schwarz, das wird beim Zufall rausgenommen
    viewCntrlr->setBkgrnd(DrawO_COLOR_LIGHTGREY);
    StaticEntity* phouse = new StaticEntity(6);

    /*
    {




        phouse->addDrawObject(DrawO_RECT_DRAW, DrawO_COLOR_BLACK, 50.0f, 0.0f, 50.0f, -90.0f, 3.0f);
        //this way, added objects can be changed. Tho if the entity holds a reference that is shared
        //between multiple entitites, the changes will be visible for all of them
        //use this carefully, outside of game setup
        phouse->getObjectStart()[0]->drawType = DrawO_LINE;


        phouse->addDrawObject(DrawO_LINE, DrawO_COLOR_BLACK, -50.0f, 0.0f, -50.0f, -90.0f, 3.0f);
        phouse->addDrawObject(DrawO_LINE, DrawO_COLOR_BLACK, -50.0f, -90.0f, 0.0f, -140.0f, 3.0f);
        phouse->addDrawObject(DrawO_LINE, DrawO_COLOR_BLACK, 0.0f, -140.0f, 50.0f, -90.0f, 3.0f);
        phouse->addDrawObject(DrawO_LINE, DrawO_COLOR_BLACK, -50.0f, -90.0f, 50.0f, -90.0f, 3.0f);
        phouse->addDrawObject(DrawO_LINE, DrawO_COLOR_BLACK, -50.0f, 0.0f, 50.0f, 0.0f, 3.0f);
        //phouse->addDrawObject(DrawO_RECT_DRAW, DrawO_COLOR_BLACK, 7.0f, 0.0f, 7.0f, -15.0f, 3.0f);

        //center
        phouse->x = viewCntrlr->disX;
        phouse->y = viewCntrlr->disY;
        addEntity(viewCntrlr, phouse);
        StaticEntity* phouse2 = new StaticEntity(6);

        StaticEntity* phouse3 = new StaticEntity(6);

        {

            phouse2->addDrawObject(DrawO_RECT_DRAW, DrawO_COLOR_BLUE, 50.0f, 0.0f, 50.0f, -90.0f, 3.0f);
            //this way, added objects can be changed. Tho if the entity holds a reference that is shared
            //between multiple entitites, the changes will be visible for all of them
            //use this carefully, outside of game setup
            phouse2->getObjectStart()[0]->drawType = DrawO_LINE;


            phouse2->addDrawObject(DrawO_LINE, DrawO_COLOR_BLUE, -50.0f, 0.0f, -50.0f, -90.0f, 3.0f);
            phouse2->addDrawObject(DrawO_LINE, DrawO_COLOR_BLUE, -50.0f, -90.0f, 0.0f, -140.0f, 3.0f);
            phouse2->addDrawObject(DrawO_LINE, DrawO_COLOR_BLUE, 0.0f, -140.0f, 50.0f, -90.0f, 3.0f);
            phouse2->addDrawObject(DrawO_LINE, DrawO_COLOR_BLUE, -50.0f, -90.0f, 50.0f, -90.0f, 3.0f);
            phouse2->addDrawObject(DrawO_LINE, DrawO_COLOR_BLUE, -50.0f, 0.0f, 50.0f, 0.0f, 3.0f);
            //phouse->addDrawObject(DrawO_RECT_DRAW, DrawO_COLOR_BLACK, 7.0f, 0.0f, 7.0f, -15.0f, 3.0f);

            //center
            phouse2->x = viewCntrlr->disX;
            phouse2->y = viewCntrlr->disY;
            addEntity(viewCntrlr, phouse2);
        }
        {

            phouse3->addDrawObject(DrawO_RECT_DRAW, DrawO_COLOR_BROWN, 50.0f, 0.0f, 50.0f, -90.0f, 3.0f);
            //this way, added objects can be changed. Tho if the entity holds a reference that is shared
            //between multiple entitites, the changes will be visible for all of them
            //use this carefully, outside of game setup
            phouse3->getObjectStart()[0]->drawType = DrawO_LINE;


            phouse3->addDrawObject(DrawO_LINE, DrawO_COLOR_BROWN, -50.0f, 0.0f, -50.0f, -90.0f, 3.0f);
            phouse3->addDrawObject(DrawO_LINE, DrawO_COLOR_BROWN, -50.0f, -90.0f, 0.0f, -140.0f, 3.0f);
            phouse3->addDrawObject(DrawO_LINE, DrawO_COLOR_BROWN, 0.0f, -140.0f, 50.0f, -90.0f, 3.0f);
            phouse3->addDrawObject(DrawO_LINE, DrawO_COLOR_BROWN, -50.0f, -90.0f, 50.0f, -90.0f, 3.0f);
            phouse3->addDrawObject(DrawO_LINE, DrawO_COLOR_BROWN, -50.0f, 0.0f, 50.0f, 0.0f, 3.0f);
            //phouse->addDrawObject(DrawO_RECT_DRAW, DrawO_COLOR_BLACK, 7.0f, 0.0f, 7.0f, -15.0f, 3.0f);

            //center
            phouse3->x = viewCntrlr->disX;
            phouse3->y = viewCntrlr->disY;
            addEntity(viewCntrlr, phouse3);
        }

        int r;
        for (int c = 0; c < 800; c++) {
            r = rand() % 3;
            StaticEntity* phouse4 = new StaticEntity(6);
            for (int i = 0; i < 6; i++) {
                switch (r) {
                case 0:
                    phouse4->addDrawObjectReference(phouse->getObjectStart()[i]);
                    break;
                case 1:
                    phouse4->addDrawObjectReference(phouse2->getObjectStart()[i]);
                    break;
                case 2:
                    phouse4->addDrawObjectReference(phouse3->getObjectStart()[i]);
                    break;
                }
            }
            phouse4->x = -600 + (rand() % 1200);
            phouse4->y = -600 + (rand() % 1200);
            addEntity(viewCntrlr, phouse4);
        }
    }

    */
    
    DwarpoModel* model = new DwarpoModel;

    model->viewcontroller = viewCntrlr;
    model->init();

    viewCntrlr->drawBkBuffer();
    viewCntrlr->disX -= 20.0f;
    viewCntrlr->disY -= 20.0f;



    std:: thread* thr1 = new std::thread(moveHouse, &phouse, viewCntrlr->Window());
  
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        
        //handle messages like resize etc.
        TranslateMessage(&msg);
        if (msg.message == WM_CLOSE) {
            globalBool = NULL;
            thr1->join();
            delete thr1;
        }
        DispatchMessage(&msg);

    }

    return 0;
}


void addEntity(DPEngine_instance* viewc, StaticEntity* pHouse) {


    viewc->addEntityL(pHouse, 0);
}

void moveHouse(StaticEntity** pphouse, HWND hwnd) {
    StaticEntity* phouse = *pphouse;
    signed short int directionToMove = 1;
    auto callMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

    while (globalBool) {
        //60fps -->update x and y
            callMs = callMs + (std::chrono::milliseconds) 16;
            phouse->x += 5.0f * directionToMove;
            if ((phouse->x) > 400.0f) {
                directionToMove = -1;
            }
            else if (phouse->x < -400.0f) {
                directionToMove = 1;
            }
            SendMessage(hwnd, WM_DWARPO_DRAW, 0, 0);
            std::this_thread::sleep_until(callMs);

    }
}