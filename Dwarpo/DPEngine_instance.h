#pragma once
#include "DwarPoEngine.h"
#include "DrawObject.h"

class DPEngine_instance: public DwarPoEngine<DPEngine_instance>
{
        ID2D1Factory* pFactory;
        ID2D1HwndRenderTarget* pRenderTarget;
        ID2D1SolidColorBrush** pBrushes;
        
        void    CalculateLayout();
        HRESULT CreateGraphicsResources();
        void    DiscardGraphicsResources();
        void DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth);
        void    OnPaint();
        void    Resize();

    public:

        DPEngine_instance() : pFactory(NULL), pRenderTarget(NULL), pBrushes(NULL)
        {
            pBrushes = (ID2D1SolidColorBrush **)calloc(DRAW_LOADCOLOR_NUM, sizeof(ID2D1SolidColorBrush*));
        }

        int onCreate();
        int onUpdate();

        PCWSTR  ClassName() const { return L"Circle Window Class"; }
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    
};

