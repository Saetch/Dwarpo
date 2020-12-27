#pragma once
#include "DwarPoEngine.h"
#include "QueueTypeLinkedList_impl.h"
#include "DrawableEntity.h"
#include "StaticEntity.h"
#include "DwarpoModel.h"
#include <mutex>
class DwarpoModel;

#define DPENGINE_LAYER_AMOUNT 3
#define DPENGINE_OBJECTBUFFER_SIZE 500


#define DPENGINE_CAMSPEED 1

class DPEngine_instance: public DwarPoEngine<DPEngine_instance>
{
        std::mutex camera_mutex;
        std::mutex cameraKey_mutex;
        unsigned short int backgroundColor = DrawO_COLOR_BLACK;
        ID2D1Factory* pFactory;
        ID2D1HwndRenderTarget* pRenderTarget;
        ID2D1SolidColorBrush** pBrushes;


        ID2D1Bitmap* bkbuffer;
        ID2D1BitmapRenderTarget* pbkBufferTarget;
        ID2D1SolidColorBrush** pbkBufferBrushes;
        D2D1_RECT_F bkSrcRect;


        QueueTypeLinkedList<DrawableEntity>* layers;
        DwarpoModel* model;
        signed short camMovX = 0;
        signed short camMovY = 0;
        DrawObject drawObjectBuffer[500] = { 0 };




        void    CalculateLayout();
        HRESULT CreateGraphicsResources();
        void    DiscardGraphicsResources();
        void    Resize();
        inline void __fastcall handleDrawObject(float x, float y, DrawObject* pDrawO);
        void __thiscall fillBuffer();
        inline void __fastcall drawBkObject(float x, float y, DrawObject* pDrawO);

        void CALLBACK WKey();
        void CALLBACK WKeyUp();
        void CALLBACK AKey();
        void CALLBACK AKeyUp();
        void CALLBACK SKey();
        void CALLBACK SKeyUp();
        void CALLBACK DKey();
        void CALLBACK DKeyUp();


    public:
        void drawBkBuffer();
        constexpr float tileSize() { return 30.0f; }
        void setBkgrnd(unsigned short int newBkgrnd);
        unsigned short int getBkgrnd();
        void addEntityL(DrawableEntity*, unsigned short int layer);
        void constructGrassTileEntity(StaticEntity* pEnt);


        void inline __thiscall updateCameraPos(float fElapsedTime) {
            camera_mutex.lock();

            disX += camMovX * (float)DPENGINE_CAMSPEED * fElapsedTime;
            disY += camMovY * (float)DPENGINE_CAMSPEED * fElapsedTime;

            camera_mutex.unlock();
        }

        DPEngine_instance() : pFactory(NULL), pRenderTarget(NULL), pBrushes(NULL)
        {
            pBrushes = (ID2D1SolidColorBrush **)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
            pbkBufferBrushes = (ID2D1SolidColorBrush**)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
            disX = 0.0f;
            disY = 0.0f;
            layers = (QueueTypeLinkedList<DrawableEntity>*)calloc(DPENGINE_LAYER_AMOUNT, sizeof(QueueTypeLinkedList<DrawableEntity>));

            drawEntities = new QueueTypeLinkedList<DrawableEntity>;


            fillBuffer();










        }

        ~DPEngine_instance() {
            free(pBrushes);
        }

        int onCreate();
        int onUpdate();

        const PCWSTR  ClassName()  {  return L"DwarPoEngine 0.1A"; }
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    
};

