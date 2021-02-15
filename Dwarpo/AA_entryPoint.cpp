
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "DPEngine_instance.h"
#include "StaticEntity.h"
#include "DwarpoModel.h"
#include <chrono>
#include <thread>
#include "KnightD.h"
//
void draw(StaticEntity** pphouse, HWND hwnd);
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


    viewCntrlr->setBkgrnd(DrawO_COLOR_LIGHTGREY);
    StaticEntity* phouse = new StaticEntity(6);


    DwarpoModel* model = new DwarpoModel;

    model->viewcontroller = viewCntrlr;
    model->init();

    viewCntrlr->drawBkBuffer();
    viewCntrlr->disX -= 20.0f;
    viewCntrlr->disY -= 20.0f;



    std:: thread* thr1 = new std::thread(draw, &phouse, viewCntrlr->Window());
  
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

void draw(StaticEntity** pphouse, HWND hwnd) {


    StaticEntity* phouse = *pphouse;
    signed short int directionToMove = 1;
    float diff;
    auto nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
    auto lastcall = nowMs;
    while (globalBool) {
        //60fps -->update x and y
            
        
            nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());            
            diff = (float)(nowMs.time_since_epoch().count() - lastcall.time_since_epoch().count());



            SendMessage(hwnd, WM_DWARPO_DRAW, 0, 0);
            lastcall = nowMs;
            viewCntrlr->updateCameraPos(diff);

   /*         //DEBUG to dynamically change the pointer to the frames ingame
            float left;
            float top;
            float right;
            float bottom;
            printf_s("Enter left/top/right/bottom coordinates for Knight sprite!\n");
            scanf_s("%f", &left);
            scanf_s("%f", &top);
            scanf_s("%f", &right);
            scanf_s("%f", &bottom);
            */



            bool half = true;
            //vorübergehend, neuen Thread für das Cyclen der Frames einbauen!
            if (viewCntrlr->yOrderedEntityList->getSize() == 2) {
            Entity* ent = viewCntrlr->yOrderedEntityList->firstListElem()->element;
            Entity* ent2 = viewCntrlr->yOrderedEntityList->firstListElem()->next->element;
            if (ent != NULL) {
                if (half) {
                    ent->tick();
                    ent2->tick();
                    half = false;
                }
                else {
                    half = true;
                }
            }

            
        }
        
    }
}