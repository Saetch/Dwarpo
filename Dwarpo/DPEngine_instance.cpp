#include "DPEngine_instance.h"
#include "DrawObject.h"
#include "QueueTypeLinkedList_impl.h"
//TODO Layout (Anpassung je nach L�nge/Breite des Bildschirms) ist eventuell nicht n�tig
void DPEngine_instance::CalculateLayout()
{
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize(); //GetSize returns in dip (device independent pixels), which is the correct measurement for all layout options
        width = size.width;
        height = size.height;
        left = disX;
        right = disX + width;
        top = disY;
        bottom = disY + height ;
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
        //create Buffers
        if (SUCCEEDED(hr)) {
            hr = pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(tileSize()*DWARPO_GRID_WIDTH,tileSize()*DWARPO_GRID_HEIGHT),&pbkBufferTarget);
            if (SUCCEEDED(hr)) {
                hr = pbkBufferTarget->GetBitmap(&bkbuffer);
            }
        }

        int i = 0;
        D2D1_COLOR_F color;
        ID2D1SolidColorBrush** cur = this->pBrushes;
        ID2D1SolidColorBrush** bkbuffcurr = this->pbkBufferBrushes;
        while (SUCCEEDED(hr))
        {
            i++;
            cur++;
            bkbuffcurr++;
            switch (i){
            case DrawO_COLOR_WHITE:
                color = D2D1::ColorF(1.0f, 1.0f, 1.0f,1.0f);
                break;
            case DrawO_COLOR_BROWN:
                color = D2D1::ColorF(0.6f, 0.3f, 0.0f, 1.0f);
                break;
            case DrawO_COLOR_BLUE:
                color = D2D1::ColorF(0.2f, 0.0f, 0.8f, 1.0f);
                break;
            case DrawO_COLOR_RED:
                color = D2D1::ColorF(0.9f, 0.0f, 0.1f, 1.0f);
                break;
            case DrawO_COLOR_YELLOW:
                color = D2D1::ColorF(0.8f, 0.8f, 0.0f, 1.0f);
                break;
            case DrawO_COLOR_ORANGE:
                color = D2D1::ColorF(0.9f, 0.6f, 0.0f, 1.0f);
                break;
            case DrawO_COLOR_GREEN:
                color = D2D1::ColorF(0.f, 0.5f, 0.0f, 1.0f);
                break;
            case DrawO_COLOR_BLACK:
                color = D2D1::ColorF(0.1f, 0.1f, 0.1f, 1.0f);
                break;
            case DrawO_COLOR_LIGHTGREY:
                color = D2D1::ColorF(0.5f, 0.5f, 0.5f, 1.0f);
            }
         
            printf_s(" %d ", i);
            hr = pRenderTarget->CreateSolidColorBrush(color, cur);
            if (i >= DRAW_LOADCOLOR_NUM) {
                break;
            }
            if (SUCCEEDED(hr)) {
                hr = pbkBufferTarget->CreateSolidColorBrush(color, bkbuffcurr);
            }
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
    QueueTypeLinkedList<DrawableEntity>* list = &layers[layer];
    list->pushBack(pnewE);

    //this->drawEntities->pushBack(pnewE);
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
        //get first element of background
        DrawableEntity* pDE;
        pDE = this->layers[0].firstListElem()->element;
        pRenderTarget->DrawBitmap(bkbuffer, D2D1::RectF(-disX, -disY, tileSize()*DWARPO_GRID_WIDTH-disX, tileSize()*DWARPO_GRID_HEIGHT-disY), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, bkSrcRect);

        DrawObject** pToDraw = NULL;
        curr = this->drawEntities->firstListElem();
        int i = 0;
        unsigned short drawOSize = 0;
        while(curr!=NULL) {
            //printf_s("index: %d\n", i++);
            pToDraw = curr->element->getObjectStart();
            drawOSize = curr->element->drawObjectsSize;
            for (int i = 0; i < drawOSize; i++) {
                //printf_s("X: %lf Y:%lf\n", curr->element->x, curr->element->y);
                this->handleDrawObject(curr->element->x, curr->element->y,*pToDraw);
                pToDraw++;
            }
            curr = curr->next;

        }






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

inline void __fastcall DPEngine_instance::handleDrawObject(float x, float y, DrawObject* pDrawO) {
    float displayX;
    float displayY;
    displayX = (x - disX);
    displayY = (y - disY);


    //relative positioning

    switch (pDrawO->drawType) {

    case DrawO_RECT_FILL:
        pRenderTarget->SetTransform(
            D2D1::Matrix3x2F::Translation(displayX, displayY) * D2D1::Matrix3x2F::Rotation(pDrawO->getAngle(), D2D1::Point2F())
        );
        D2D1_RECT_F rectangle = D2D1::RectF(pDrawO->getLeft(), pDrawO->getTop(), pDrawO->getRight(), pDrawO->getBottom());
        this->pRenderTarget->FillRectangle(&rectangle, this->pBrushes[pDrawO->color]);
        return;



    case DrawO_RECT_DRAW:



        pRenderTarget->SetTransform(
            D2D1::Matrix3x2F::Translation(displayX, displayY) * D2D1::Matrix3x2F::Rotation(pDrawO->getAngle(), D2D1::Point2F())
        );
        D2D1_RECT_F rectangle2 = D2D1::RectF(pDrawO->getLeft(), pDrawO->getTop(), pDrawO->getRight(), pDrawO->getBottom());
        this->pRenderTarget->DrawRectangle(&rectangle2, this->pBrushes[pDrawO->color], pDrawO->width);


        return;
    case DrawO_LINE:

        D2D1_POINT_2F start = D2D1::Point2F(pDrawO->getX1() + displayX, pDrawO->getY1() + displayY);
        D2D1_POINT_2F end = D2D1::Point2F(pDrawO->getX2() + displayX, pDrawO->getY2() + displayY);
        this->pRenderTarget->DrawLine(start, end, this->pBrushes[pDrawO->color], pDrawO->width);

        return;
    default:
        printf_s("ILLEGAL drawType for DrawObject\n");
        return;
    }


}

void __thiscall DPEngine_instance::fillBuffer()
{
    {
        drawObjectBuffer[0].angle = 0.0f;
        drawObjectBuffer[0].color = DrawO_COLOR_GREEN;
        drawObjectBuffer[0].drawType = DrawO_RECT_FILL;
        drawObjectBuffer[0].width = 1.0f;
        drawObjectBuffer[0].x1 = 0.0f;
        drawObjectBuffer[0].y1 = tileSize();
        drawObjectBuffer[0].x2 = 0.0f;
        drawObjectBuffer[0].y2 = tileSize();
    }
    {
        //this is for debug purposes, to be removed later
        drawObjectBuffer[490].angle = 0.0f;
        drawObjectBuffer[490].color = DrawO_COLOR_BLACK;
        drawObjectBuffer[490].drawType = DrawO_RECT_DRAW;
        drawObjectBuffer[490].width = 1.3f;
        drawObjectBuffer[490].x1 = 0.0f;
        drawObjectBuffer[490].y1 = tileSize();
        drawObjectBuffer[490].x2 = 0.0f;
        drawObjectBuffer[490].y2 = tileSize();
    }
}

inline void __fastcall DPEngine_instance::drawBkObject(float x, float y, DrawObject* pDrawO)
{
    float displayX;
    float displayY;
    displayX = (x);
    displayY = (y);
    //this->pbkBufferTarget->BeginDraw(); //debug

    switch (pDrawO->drawType) {

    case DrawO_RECT_FILL:
        pbkBufferTarget->SetTransform(
            D2D1::Matrix3x2F::Translation(displayX, displayY) * D2D1::Matrix3x2F::Rotation(pDrawO->getAngle(), D2D1::Point2F())
        );
        D2D1_RECT_F rectangle = D2D1::RectF(pDrawO->getLeft(), pDrawO->getTop(), pDrawO->getRight(), pDrawO->getBottom());
        this->pbkBufferTarget->FillRectangle(&rectangle, this->pbkBufferBrushes[pDrawO->color]);
        break;



    case DrawO_RECT_DRAW:



        pbkBufferTarget->SetTransform(
            D2D1::Matrix3x2F::Translation(displayX, displayY) * D2D1::Matrix3x2F::Rotation(pDrawO->getAngle(), D2D1::Point2F())
        );
        D2D1_RECT_F rectangle2 = D2D1::RectF(pDrawO->getLeft(), pDrawO->getTop(), pDrawO->getRight(), pDrawO->getBottom());
        this->pbkBufferTarget->DrawRectangle(&rectangle2, this->pbkBufferBrushes[pDrawO->color], pDrawO->width);


        break;
    case DrawO_LINE:

        D2D1_POINT_2F start = D2D1::Point2F(pDrawO->getX1() + displayX, pDrawO->getY1() + displayY);
        D2D1_POINT_2F end = D2D1::Point2F(pDrawO->getX2() + displayX, pDrawO->getY2() + displayY);
        this->pbkBufferTarget->DrawLine(start, end, this->pbkBufferBrushes[pDrawO->color], pDrawO->width);

        break;
    default:
        printf_s("ILLEGAL drawType for DrawObject\n");
        return;
    }
    /* debug
    HRESULT hr = this->pbkBufferTarget->EndDraw();
     if (SUCCEEDED(hr)) {
      printf_s("Updated bkgrndBuffer\n");
  }
  else {
      printf_s("Failed updating the bkgrndBuffer\n");
      printf_s("%d\n", hr);
  }
     */
}

void DPEngine_instance::drawBkBuffer()
{
    HRESULT hr = CreateGraphicsResources();
    if (!SUCCEEDED(hr)) {
        printf_s("COULD NOT CREATE GRAPHICS RESOURCES");
        return;
    }
    QueueTypeLinkedList<DrawableEntity>* bkgrnd = this->layers;
    ListElem<DrawableEntity>* currentEntityElem = bkgrnd->firstListElem();
    unsigned int bkgrndSize = bkgrnd->getSize();
    DrawableEntity* ent;
    DrawObject** obj;
    this->pbkBufferTarget->BeginDraw();
    for (unsigned int index = 0; index < bkgrndSize; index++) {
        ent = currentEntityElem->element;
        obj = ent->getObjectStart();
        for (int object_i = 0; object_i < ent->drawObjectsSize; object_i++) {
            drawBkObject(ent->x, ent->y, *obj);
            obj++;
        }


        currentEntityElem = currentEntityElem->next;
    }

    if (SUCCEEDED(this->pbkBufferTarget->EndDraw())) {
        printf_s("Updated bkgrndBuffer");
    }
    else {
        printf_s("Failed updating the bkgrndBuffer");
    }
    bkSrcRect = D2D1::RectF(0.0f, 0.0f, tileSize()* DWARPO_GRID_WIDTH, tileSize()*DWARPO_GRID_HEIGHT );
    
}

void DPEngine_instance::constructGrassTileEntity(StaticEntity* pEnt)
{
    if (pEnt->drawObjectsSize != 2) {
        printf_s("ERR: Tried constructing GrassTileEntity from static entity with drawObjectSize: %d (2allowed)", pEnt->drawObjectsSize);
        return ;
    }
    pEnt->addDrawObjectReference(drawObjectBuffer);
    pEnt->addDrawObjectReference(drawObjectBuffer + 490);

}



LRESULT DPEngine_instance::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_MULTI_THREADED, &pFactory)))
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
        return 0;

    case WM_DWARPO_DRAW:
        onUpdate();
        pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        return 0;


    case WM_SIZE:
        Resize();
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
