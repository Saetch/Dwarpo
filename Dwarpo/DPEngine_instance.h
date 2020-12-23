#pragma once
#include "DwarPoEngine.h"
#include "QueueTypeLinkedList_impl.h"
#include "DrawableEntity.h"
#include "StaticEntity.h"


#define DPENGINE_OBJECTBUFFER_SIZE 500

class DPEngine_instance: public DwarPoEngine<DPEngine_instance>
{
        unsigned short int backgroundColor = DrawO_COLOR_BLACK;
        ID2D1Factory* pFactory;
        ID2D1HwndRenderTarget* pRenderTarget;
        ID2D1SolidColorBrush** pBrushes;

        QueueTypeLinkedList<DrawableEntity>** layers;
        DrawObject drawObjectBuffer[500] = { 0 };


        void    CalculateLayout();
        HRESULT CreateGraphicsResources();
        void    DiscardGraphicsResources();
        void    Resize();
        inline void __fastcall handleDrawObject(float x, float y, DrawObject* pDrawO);
        void __thiscall fillBuffer();
    public:
        constexpr float tileSize() { return 40.0f; }
        void setBkgrnd(unsigned short int newBkgrnd);
        unsigned short int getBkgrnd();
        void addEntityL(DrawableEntity*, unsigned short int layer);
        void constructGrassTileEntity(StaticEntity* pEnt);

        DPEngine_instance() : pFactory(NULL), pRenderTarget(NULL), pBrushes(NULL)
        {
            pBrushes = (ID2D1SolidColorBrush **)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
            disX = 0.0f;
            disY = 0.0f;
            drawEntities = new QueueTypeLinkedList<DrawableEntity>();

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

