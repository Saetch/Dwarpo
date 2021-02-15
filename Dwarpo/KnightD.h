#pragma once
#include "BaseCreature.h"
#include <mutex>

class KnightD :
    public BaseCreature
{
    

public:
    //frame to be displayed by the game engine, for fast access
    //mutexed since 2 different thread have access to this
    D2D_RECT_F* currentFrame = (KnightD::idleFrames);
    std::mutex frameMutex;
    //how often this Entity was checked for Frame updates.
    unsigned short tick_count = 0;


    //Frames for idling
    inline static D2D_RECT_F idleFrames[10];


    void init() {
        currentFrame = KnightD::idleFrames;
        tick_count = 0;
    }

    bool changeState();
   
    KnightD() {
        ;
    }
    
    inline void tick() {

        //cycling through the frames at 30fps (30 ticks per second)
        //cycling through the actual frames in a different thread means less work for the rendering thread
        switch (this->tick_count) {
        case 6:
            frameMutex.lock();
            currentFrame = &(KnightD::idleFrames[1]);
            frameMutex.unlock();
            break;
        case 12:
            frameMutex.lock();

            currentFrame = &(KnightD::idleFrames[2]);
            frameMutex.unlock();

            break;
        case 18:
            frameMutex.lock();

            currentFrame = &(KnightD::idleFrames[3]);
            frameMutex.unlock();

            break;
        case 24:
            frameMutex.lock();

            currentFrame = &(KnightD::idleFrames[4]);
            frameMutex.unlock();

            break;
        case 30:
            frameMutex.lock();

            currentFrame = &(KnightD::idleFrames[5]);
            frameMutex.unlock();

            break;
        case 36:
            frameMutex.lock();

            currentFrame = &(KnightD::idleFrames[6]);
            frameMutex.unlock();

            break;
        case 42:
            frameMutex.lock();

            currentFrame = &(KnightD::idleFrames[7]);
            frameMutex.unlock();

            break;
        case 48:
            frameMutex.lock();

            currentFrame = &(KnightD::idleFrames[8]);
            frameMutex.unlock();

            break;
        case 54:
            frameMutex.lock();

            currentFrame = &(KnightD::idleFrames[9]);
            frameMutex.unlock();

            break;
        case 60:
            tick_count = 0;
            frameMutex.lock();

            currentFrame = idleFrames;
            frameMutex.unlock();

            break;
        }
    }



    static void initKnightDClass() {


        //initialize "Pointers" in form of predefined RECTs, that point to the specified frame in the buffer.
        KnightD::idleFrames[0] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[1] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[2] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[3] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[4] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[5] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[6] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[7] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[8] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

        KnightD::idleFrames[9] = D2D1::RectF(0.0f, 0.0f, 30.0f, 30.0f);

    }

    
};

