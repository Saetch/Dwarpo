#pragma once
#include "DwarPoEngine/DwarPoEngine.h"
#include "DrawableEntity.h"
#include "StaticEntity.h"
#include "DwarpoModel.h"
#include <mutex>
#include "SpriteManager.h"
#include "BaseCreature.h"
#include <vector>
#include "Structure.h"


#define DPENGINE_LAYER_AMOUNT 3
#define DPENGINE_OBJECTBUFFER_SIZE 500
//TILESIZE OF 35 can support a GRID_WIDTH OF UP TO 460
//for more possible tiles, multiple background buffers need to be implemented
#define TILESIZE 32
#define DWARPO_GRID_WIDTH 460
#define DWARPO_GRID_HEIGHT 400
//this should be considered as a percentage
#define DPENGINE_CAMSPEED 125.0f

class DwarpoModel;
class LinkedChunk;
class SpriteManager;

class DPEngine_instance: public DwarPoEngine<DPEngine_instance>
{
        std::mutex camera_mutex;
        std::mutex cameraKey_mutex;
        std::mutex bkBufferMutex;
        unsigned short int backgroundColor = DrawO_COLOR_BLACK;
        ID2D1Factory* pFactory;
        ID2D1HwndRenderTarget* pRenderTarget;
        ID2D1SolidColorBrush** pBrushes;
        std::atomic<bool> needToUpdateBkBuffer=false;


        ID2D1Bitmap* bkbuffer;
        ID2D1BitmapRenderTarget* pbkBufferTarget;

        ID2D1Bitmap* debugbuffer;
        ID2D1BitmapRenderTarget* pdebugBufferTarget;

        ID2D1SolidColorBrush** pbkBufferBrushes;
        D2D1_RECT_F bkSrcRect;

        IDXGIFactory* pdxgiFactory;
        ID2D1DeviceContext* pd2dDeviceContext;
        ID3D10Device1* pd3dDevice;

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
        inline void __fastcall drawDebugGridObject(float x, float y, DrawObject* pDrawO);
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

        std::vector<Entity*> entityList;
        std::vector<Entity*> foregroundList;
        std::vector<Entity*> structureList;
        std::mutex yOrderedEntityList_mutex;
        std::mutex entityListMutex;
        std::mutex foreGroundListMutex;


        void drawBkBuffer();



        constexpr float tileSize() { return (float)TILESIZE; }
        static constexpr float staticTileSize() { return (float)TILESIZE; }


        void setBkgrnd(unsigned short int newBkgrnd);
        unsigned short int getBkgrnd();
        void drawDebugChunks(QueueTypeLinkedList<LinkedChunk>* &chunks, int w, int h);
        void setModel(DwarpoModel* m) {
            model = m;
        }
        void inline __thiscall updateCameraPos(const float fElapsedTime) {
            camera_mutex.lock();

            disX += camMovX * DPENGINE_CAMSPEED /100.0f * fElapsedTime;
            if (disX < -10.0f*tileSize()) {
                disX = -10.0f * tileSize();
            }
            else if (disX > -20*tileSize() + tileSize() * DWARPO_GRID_WIDTH) {
                disX = -20.0f * tileSize() + tileSize() * DWARPO_GRID_WIDTH;
            }
            disY += camMovY * DPENGINE_CAMSPEED / 100.0f * fElapsedTime;
            if (disY < -10.0f * tileSize()) {
                disY = -10.0f * tileSize();
            }
            else if (disY > -12.0f * tileSize() + tileSize() * DWARPO_GRID_HEIGHT) {
                disY = -12.0f * tileSize() + tileSize() * DWARPO_GRID_HEIGHT;
            }
            camera_mutex.unlock();
        }

        DPEngine_instance() : pFactory(NULL), pRenderTarget(NULL), pBrushes(NULL)
        {

            pBrushes = (ID2D1SolidColorBrush **)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
            pbkBufferBrushes = (ID2D1SolidColorBrush**)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
            disX = 0.0f;
            disY = 0.0f;

            drawEntities = new QueueTypeLinkedList<DrawableEntity>;


            fillBuffer();










        }

        void addStructureToBkBuffer(Structure* const& struc);
        void destroyStructure(Structure* const& struc);


        ~DPEngine_instance() {
            free(pbkBufferBrushes);
            free(pBrushes);
            delete drawEntities;
        }

        int onCreate();
        int onUpdate();

        bool ok() { return true; }
        const PCWSTR  ClassName()  {  return L"DwarPoEngine 0.1A"; }
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    
};

