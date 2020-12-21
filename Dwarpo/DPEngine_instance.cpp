#include "DPEngine_instance.h"
#include "DrawObject.h"
#include "QueueTypeLinkedList_impl.h"

//TODO Layout (Anpassung je nach Länge/Breite des Bildschirms) ist eventuell nicht nötig
void DPEngine_instance::CalculateLayout()
{
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize(); //GetSize returns in dip (device independent pixels), which is the correct measurement for all layout options
        width = size.width;
        height = size.height;
        left = disX - width / 2;
        right = disX + width/2;
        top = disY - height / 2;
        bottom = disY + height / 2;
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
        int i = 0;
        D2D1_COLOR_F color;
        ID2D1SolidColorBrush** cur = this->pBrushes;
        while (SUCCEEDED(hr))
        {
            i++;
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
            printf_s(" %d ", i);
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

void DPEngine_instance::DiscardGraphicsResources()
{
    BaseWindow::SafeRelease(&this->pRenderTarget);
    for (int i = 0; i <= DRAW_LOADCOLOR_NUM; i++) {
        BaseWindow::SafeRelease(&this->pBrushes[i]);
    }
}

void DPEngine_instance::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        CalculateLayout();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}



void DPEngine_instance::addEntityL(DrawableEntity* pnewE, unsigned short int layer)
{   

    this->drawEntities->pushBack(pnewE);
    printf_s("Called addEntityL, layer not implemented yet, fix this\n");
}

void DPEngine_instance::setBkgrnd(unsigned short int newBK)
{
    if (newBK <= 0 || newBK > DRAW_LOADCOLOR_NUM) {
        printf_s("LOADED BKGRND WITH ILLEGAL VALUE: %d\n", newBK);
    }
    this->backgroundColor = newBK;
}

unsigned short int DPEngine_instance::getBkgrnd()
{
    return this->backgroundColor;
}

int DPEngine_instance::onCreate()
{
    this->CalculateLayout();
    return 0;
}

int DPEngine_instance::onUpdate()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        ListElem<DrawableEntity>* curr;
        BeginPaint(m_hwnd, &ps);
        pRenderTarget->BeginDraw();
        //background
        pRenderTarget->Clear(pBrushes[this->backgroundColor]->GetColor());
        DrawObject* pToDraw = NULL;
        curr = this->drawEntities->firstListElem();
        unsigned short drawOSize = 0;
        while(curr!=NULL) {

            pToDraw = curr->element->getObjectStart();
            drawOSize = curr->element->drawObjectsSize;
            for (int i = 0; i < drawOSize; i++) {
                this->handleDrawObject(curr->element->x, curr->element->y,pToDraw);
                pToDraw++;
            }
            curr = curr->next;

        }





        // Restore the identity transformation.
        pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            this->DiscardGraphicsResources();
            EndPaint(m_hwnd, &ps);
            return 1;
        }
        EndPaint(m_hwnd, &ps);
        return 0;
    }
    return 1;
}

inline void DPEngine_instance::handleDrawObject(float x, float y, DrawObject* pDrawO) {
    float displayX;
    float displayY;
    displayX = (x - disX) - left;
    displayY = (y - disY) - top;


    switch (pDrawO->drawType) {
    case DrawO_RECT_FILL:
    case DrawO_RECT_DRAW:
        printf_s("HANDLEDRAWOBJECT case not yet implemented");
    case DrawO_LINE:
        D2D1_POINT_2F start = D2D1::Point2F(pDrawO->getX1()+displayX, pDrawO->getY1()+displayY);
        D2D1_POINT_2F end = D2D1::Point2F(pDrawO->getX2()+displayX, pDrawO->getY2()+displayY);
        this->pRenderTarget->DrawLine(start, end, this->pBrushes[pDrawO->color], pDrawO->width);
        break;
    default: 
        printf_s("ILLEGAL drawType for DrawObject\n");
        return;
    }
}



LRESULT DPEngine_instance::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            printf_s("FAILED to create Resource DPEngine_instance.pFactory (ID2D1HwndRenderTarget)\n");
            return -1;  // Fail CreateWindowEx.

        }
        this->onCreate();
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        onUpdate();
        return 0;



    case WM_SIZE:
        Resize();
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
