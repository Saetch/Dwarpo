#pragma once
#include "DwarPoEngine.h"
#include "QueueTypeLinkedList_impl.h"
#include "DrawableEntity.h"
#include "StaticEntity.h"
#include "DwarpoModel.h"
#include <mutex>
#include "SpriteManager.h"
#include "BaseCreature.h"

class DwarpoModel;
class LinkedChunk;

#define DPENGINE_LAYER_AMOUNT 3
#define DPENGINE_OBJECTBUFFER_SIZE 500
#define TILESIZE 30


#define DPENGINE_CAMSPEED 1


class SpriteManager;

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

        ID2D1Bitmap* debugbuffer;
        ID2D1BitmapRenderTarget* pdebugBufferTarget;

        ID2D1SolidColorBrush** pbkBufferBrushes;
        D2D1_RECT_F bkSrcRect;

        IDXGIFactory* pdxgiFactory;
        ID2D1DeviceContext* pd2dDeviceContext;
        ID3D10Device1* pd3dDevice;

        QueueTypeLinkedList<DrawableEntity>* layers;
        DwarpoModel* model;
        signed short camMovX = 0;
        signed short camMovY = 0;
        DrawObject drawObjectBuffer[491] = { 0 };


        SpriteManager* spriteManager;

        void    CalculateLayout();
        HRESULT CreateGraphicsResources();
        void    DiscardGraphicsResources();
        void    Resize();
        inline void __fastcall handleDrawObject(float x, float y, DrawObject* pDrawO);
        void __thiscall fillBuffer();
        inline void __fastcall drawBkObject(float x, float y, DrawObject* pDrawO);
        HRESULT __stdcall CreateD3DDevice(
            IDXGIAdapter* pAdapter,
            D3D10_DRIVER_TYPE driverType,
            UINT flags,
            ID3D10Device1** ppDevice
        );
        void CALLBACK WKey();
        void CALLBACK WKeyUp();
        void CALLBACK AKey();
        void CALLBACK AKeyUp();
        void CALLBACK SKey();
        void CALLBACK SKeyUp();
        void CALLBACK DKey();
        void CALLBACK DKeyUp();


    public:

        QueueTypeLinkedList<Entity>* yOrderedEntityList;
        std::mutex yOrderedEntityList_mutex;


        void addToYOrderedEntityList(Entity* newCreature);

        void drawBkBuffer();


        constexpr float tileSize() { return (float)TILESIZE; }
        static constexpr float staticTileSize() { return (float)TILESIZE; }


        void setBkgrnd(unsigned short int newBkgrnd);
        unsigned short int getBkgrnd();
        void addEntityL(DrawableEntity*, unsigned short int layer);
        void constructGrassTileEntity(StaticEntity* pEnt);
        void drawDebugChunks(QueueTypeLinkedList<LinkedChunk>* &chunks, int w, int h);
        void setModel(DwarpoModel* m) {
            model = m;
        }
        void inline __thiscall updateCameraPos(float fElapsedTime) {
            camera_mutex.lock();

            disX += camMovX * (float)DPENGINE_CAMSPEED * fElapsedTime;
            disY += camMovY * (float)DPENGINE_CAMSPEED * fElapsedTime;

            camera_mutex.unlock();
        }

        DPEngine_instance() : pFactory(NULL), pRenderTarget(NULL), pBrushes(NULL)
        {
            yOrderedEntityList = new QueueTypeLinkedList<Entity>();

            pBrushes = (ID2D1SolidColorBrush **)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
            pbkBufferBrushes = (ID2D1SolidColorBrush**)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
            disX = 0.0f;
            disY = 0.0f;
            layers = (QueueTypeLinkedList<DrawableEntity>*)calloc(DPENGINE_LAYER_AMOUNT, sizeof(QueueTypeLinkedList<DrawableEntity>));

            drawEntities = new QueueTypeLinkedList<DrawableEntity>;


            fillBuffer();










        }




        ~DPEngine_instance() {
            free(pbkBufferBrushes);
            free(layers);
            free(pBrushes);
            delete yOrderedEntityList;
        }

        int onCreate();
        int onUpdate();

        bool ok() { return true; }
        const PCWSTR  ClassName()  {  return L"DwarPoEngine 0.1A"; }
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    
};

