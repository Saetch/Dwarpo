#include "DPEngine_instance.h"



//TODO Layout (Anpassung je nach Länge/Breite des Bildschirms) ist eventuell nicht nötig
void DPEngine_instance::CalculateLayout()
{
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize(); //GetSize returns in dip (device independent pixels), which is the correct measurement for all layout options
    }
}

HRESULT DPEngine_instance::CreateGraphicsResources()
{
    HRESULT hr = S_OK;

    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &pRenderTarget);
        int i = 1;
        D2D1_COLOR_F color;
        ID2D1SolidColorBrush** cur = this->pBrushes;
        while (SUCCEEDED(hr))
        {
            cur++;
            switch (i){
            case DrawO_COLOR_WHITE:
                color = D2D1::ColorF(1.0f, 1.0f, 1.0f);
                break;
            case DrawO_COLOR_BROWN:
                color = D2D1::ColorF(0.6f, 0.3f, 0.0f);
                break;
            case DrawO_COLOR_BLUE:
                color = D2D1::ColorF(0.2f, 0.0f, 0.8f);
                break;
            case DrawO_COLOR_RED:
                color = D2D1::ColorF(0.9f, 0.0f, 0.1f);
                break;
            case DrawO_COLOR_YELLOW:
                color = D2D1::ColorF(0.8f, 0.8f, 0.0f);
                break;
            case DrawO_COLOR_ORANGE:
                color = D2D1::ColorF(0.9f, 0.6f, 0.0f);
                break;
            case DrawO_COLOR_GREEN:
                color = D2D1::ColorF(0.3f, 0.7f, 0.0f);
                break;
            case DrawO_COLOR_BLACK:
                color = D2D1::ColorF(0.1f, 0.1f, 0.1f);
                break;
            }
             
            hr = pRenderTarget->CreateSolidColorBrush(color, cur);

            if (i >= DRAW_LOADCOLOR_NUM) break;
        }
        if (SUCCEEDED(hr))
        {
            CalculateLayout();
        }
    }
    return hr;
}
