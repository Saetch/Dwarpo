#pragma once
#include "DwarPoEngine.h"
#include "QueueTypeLinkedList_impl.h"
#include "DrawableEntity.h"

class DPEngine_instance: public DwarPoEngine<DPEngine_instance>
{
        unsigned short int backgroundColor = DrawO_COLOR_BLACK;
        ID2D1Factory* pFactory;
        ID2D1HwndRenderTarget* pRenderTarget;
        ID2D1SolidColorBrush** pBrushes;

        QueueTypeLinkedList<DrawableEntity>** layers;



        void    CalculateLayout();
        HRESULT CreateGraphicsResources();
        void    DiscardGraphicsResources();
        void    Resize();
        inline void handleDrawObject(DrawObject* pDrawO);

    public:
        void setBkgrnd(unsigned short int newBkgrnd);
        unsigned short int getBkgrnd();
        void addEntityL(DrawableEntity*, unsigned short int layer);
        DPEngine_instance() : pFactory(NULL), pRenderTarget(NULL), pBrushes(NULL)
        {
            pBrushes = (ID2D1SolidColorBrush **)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
            disX = 0.0f;
            disY = 0.0f;
            drawEntities = new QueueTypeLinkedList<DrawableEntity>();
        }

        ~DPEngine_instance() {
            free(pBrushes);
        }

        int onCreate();
        int onUpdate();

        const PCWSTR  ClassName()  {  return L"DwarPoEngine 0.1A"; }
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    
};

