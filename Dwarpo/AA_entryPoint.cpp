
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "DPEngine_instance.h"
#include "StaticEntity.h"
#include "DwarpoModel.h"
#include <chrono>
#include <thread>
#include "KnightD.h"
#include <stdio.h>
#include <atomic>
#include <future>
#include "Dwarf_BaseHouse.h"
//
void draw( HWND hwnd);
void frameCycle();
void gameLoop();
std::atomic_bool globalBool = TRUE;
DPEngine_instance* viewCntrlr;
DwarpoModel* model = new DwarpoModel;

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




    model->viewcontroller = viewCntrlr;
    model->init();
    viewCntrlr->setModel(model);
    viewCntrlr->drawBkBuffer();
    viewCntrlr->disX -= 20.0f;
    viewCntrlr->disY -= 20.0f;



    std:: thread* thr1 = new std::thread(draw, viewCntrlr->Window());
    std::thread* thr2 = new std::thread(frameCycle);
    std::thread* gameLogicThr = new std::thread(gameLoop);
    //DEBUGGING yOrderEntities
    
   
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        
        //handle messages like resize etc.
        TranslateMessage(&msg);
        if (msg.message == WM_CLOSE) {
            globalBool.store(FALSE);
            thr1->join();
            thr2->join();
            gameLogicThr->join();
            delete thr1;
            delete thr2;
            delete gameLogicThr;
        }
        DispatchMessage(&msg);

    }
    delete model;
    return 0;
}

void nothingyo() {
    for (int i = 0; i < 1000; i++) {
        if (i % 100 == 0) {
            std::cout << i / 100 << std::endl;
        }
    }
}



void frameCycle() {


    float diff;
    auto nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
    auto lastcall = nowMs;
    const float fpsThreshold = 1000.0f / 30.0f;
    while (globalBool.load()) {
        //60fps -->update x and y


        nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
        diff = (float)(nowMs.time_since_epoch().count() - lastcall.time_since_epoch().count());

        if (diff < fpsThreshold) {
            std::this_thread::sleep_for(std::chrono::nanoseconds((int)((fpsThreshold-diff)*1000)));
        }
            lastcall = nowMs;
            for (Entity* ent : viewCntrlr->entityList) {
                ent->tick();
            }

               

    }
}

void gameLoop()
{
    
    auto lastCall =  (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
    auto nowMs = std::move(lastCall);
    bool reloadBackground = false;
    int timeElapsed=16;
    int counter = 0;
    int calls = 0;
    std::vector<Structure*> vect;
    while (globalBool.load()) {
        lastCall = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
        reloadBackground = model->gameLoopTick(timeElapsed);
        if (!reloadBackground && counter>=1000) {
            counter = 0;
            /// <summary>
            /// THIS MIGHT NOT WORK EXACTLY AS EXPECTED; MIGHT LEAD TO ERRORS 
            /// </summary>
            calls++;
            Dwarf_BaseHouse* newH = new Dwarf_BaseHouse(6+calls*4, 7, viewCntrlr->tileSize());
            vect.push_back(newH);
            std::async(std::launch::async, &DPEngine_instance::addStructureToBkBuffer, viewCntrlr, newH);

            if (calls > 3) {
                std::async(std::launch::async, &DPEngine_instance::destroyStructure, viewCntrlr, vect[0]);

                vect.erase(vect.begin());
            }
        }
        counter+=timeElapsed;
        nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
        timeElapsed= (int)nowMs.time_since_epoch().count() - (int)lastCall.time_since_epoch().count();
        // std::cout << (timeElapsed) << std::endl;
    }

}


void draw( HWND hwnd ) {

    int f_counter = 0;
    float diff;
    auto nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
    auto sec = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
    auto lastcall = nowMs;
    while (globalBool.load()) {
        //60fps -->update x and y
        
            nowMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());            
            diff = (float)(nowMs.time_since_epoch().count() - lastcall.time_since_epoch().count());



            SendMessage(hwnd, WM_DWARPO_DRAW, 0, 0);

            lastcall = nowMs;


            viewCntrlr->updateCameraPos(diff);
            f_counter++;



            float diffr = (float)(lastcall.time_since_epoch().count() - sec.time_since_epoch().count());

            if ( diffr >= 1000.0f) {
                sec = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());
                printf_s("FPS: %d\n", f_counter);
                f_counter = 0;
            }
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


               
    }
}