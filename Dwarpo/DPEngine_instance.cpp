#pragma once
#include "DPEngine_instance.h"
#include "DrawObject.h"
#include "Structure.h"
#include "QueueTypeLinkedList_impl.h"
#include "LinkedChunk.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>

//removeable after debug
#define debugI(x) printf_s(#x": %d\n", x);
#define debugF(x) printf_s(#x": %lf\n", x);
#define debugP(x) printf_s(#x": %p\n", x);

#define INITDEBUGBUFFER 1
#define DWARPO_SHOWGRID 1
#define SHOWSTATICBUFFER 0

inline double DPEngine_instance::zoomed_size() {
    return tileSize()* zoom;
}

void DPEngine_instance::CalculateLayout()
{
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize(); //GetSize returns in dip (device independent pixels), which is the correct measurement for all layout options
        width = size.width;
        height = size.height;
        camera_mutex.lock();
        left = disX;
        top = disY;
        camera_mutex.unlock();
        right = left + width;
        bottom = top + height;
        
    }
}

HRESULT DPEngine_instance::CreateGraphicsResources()
{
    HRESULT hr = S_OK;

    if (pRenderTarget == NULL || pbkBufferTarget == NULL )
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
        if (pRenderTarget == NULL) {
            hr = pFactory->CreateHwndRenderTarget(
                D2D1::RenderTargetProperties(),
                D2D1::HwndRenderTargetProperties(m_hwnd, size),
                &pRenderTarget);
        }



        //create Buffers
        if (SUCCEEDED(hr)) {
            hr = pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(tileSize()*DWARPO_GRID_WIDTH,tileSize()*DWARPO_GRID_HEIGHT),&pbkBufferTarget);

            printf_s("BackgroundBufferSize: %lf x %lf \n", (float)tileSize() * DWARPO_GRID_WIDTH, (float)tileSize() * DWARPO_GRID_HEIGHT);
            if (SUCCEEDED(hr)) {
                hr = pbkBufferTarget->GetBitmap(&bkbuffer);
            }


        }

        if (INITDEBUGBUFFER && SUCCEEDED(hr) ) {
            hr = pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(tileSize() * DWARPO_GRID_WIDTH, tileSize() * DWARPO_GRID_HEIGHT), &pdebugBufferTarget);
           if (SUCCEEDED(hr)) {
               printf_s("Initialized debug");
                hr = pdebugBufferTarget->GetBitmap(&debugbuffer);
            }
        }

        if (SUCCEEDED(hr)) {
            if (spriteManager != NULL) {
                delete spriteManager;
            }
            if (SUCCEEDED(hr)) {
                printf_s("SUCCEEDED so far! \n");
            }
            spriteManager = new SpriteManager(pRenderTarget, tileSize(), tileSize());
            hr = spriteManager->loadSpritesToBuffer();

            if (SUCCEEDED(hr)) {
                printf_s("SUCC1!\n");
            }
            else {
                printf_s("FAIL1!\n");
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
                color = D2D1::ColorF(0.15f, 0.15f, 0.15f, 1.0f);
            }
         
            printf_s("Created preconstructed Color %d \n", i);
            hr = pRenderTarget->CreateSolidColorBrush(color, cur);
            if (SUCCEEDED(hr)) {
                hr = pbkBufferTarget->CreateSolidColorBrush(color, bkbuffcurr);
            }
            if (i >= DRAW_LOADCOLOR_NUM) {
                break;
            }

        }
        if (SUCCEEDED(hr))
        {
            CalculateLayout();
        }
        bkSrcRect = D2D1::RectF(0.0f, 0.0f, tileSize() * DWARPO_GRID_WIDTH, tileSize() * DWARPO_GRID_HEIGHT);

    }
    return hr;
}

void DPEngine_instance::DiscardGraphicsResources()
{

    for (int i = 0; i <= DRAW_LOADCOLOR_NUM; i++) {
        BaseWindow::SafeRelease(&this->pBrushes[i]);
        BaseWindow::SafeRelease(&this->pbkBufferBrushes[i]);
    }
    BaseWindow::SafeRelease(&this->pRenderTarget);

    BaseWindow::SafeRelease(&this->pbkBufferTarget);
    BaseWindow::SafeRelease(&this->bkbuffer);

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

void DPEngine_instance::addStructureToBkBuffer(Structure* const& struc)
{
    pbkBufferTarget->BeginDraw();

    auto rect = D2D1::RectF(struc->targetRect.left, zoomed_size() * struc->targetRect.top, struc->targetRect.right, zoomed_size() * struc->targetRect.bottom);
    pbkBufferTarget->DrawBitmap(

        spriteManager->staticBuffer,
        rect,
        1.0f,
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        struc->getFrameRect()
    );

    if (SUCCEEDED(pbkBufferTarget->EndDraw())) {
        std::cout << "added " << struc->getType() << " to backgroundBuffer!\n";
    }
    else {
        std::cout << "could not add " << struc->getType() << " to backgroundBuffer!\n";

    }
}


//this will draw on the backgroundBuffer again but only on the necessary parts that should be updated upon destruction of this object
void DPEngine_instance::destroyStructure(Structure* const& struc)
{
    baseTile* curr;
    float xTar;
    float yTar;
    D2D1_RECT_F rect;
    pbkBufferTarget->BeginDraw();
    for (int x = struc->xPos; x <= struc->xPos + std::get<0>(struc->getOffsets()); x++) {
        for (int y = struc->yPos; y >= struc->yPos + std::get<1>(struc->getOffsets()); y--) {

             curr = model->getTileAt(x, y);
             xTar = x * this->zoomed_size();
             yTar = y * this->zoomed_size();
             rect = D2D1::RectF(xTar, yTar, xTar + this->zoomed_size(), yTar + this->zoomed_size());
            //this was needed to reset a transformation that some other rendering method needed. Unnecessary if skipped.

            pbkBufferTarget->DrawBitmap(spriteManager->getp_StaticBitMap(), rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, curr->getRect());
            if (DWARPO_SHOWGRID) {
                drawDebugGridObject(xTar, yTar, this->drawObjectBuffer + 490);
            }
        }
    }
    if (SUCCEEDED(pbkBufferTarget->EndDraw())) {
        std::cout << "Removed Structure " << struc->getType() << " from BackgroundBuffer" << std::endl;
    }
    else {
        std::cout << "Failed removing Structure " << struc->getType() << " at X: " << struc->xPos << " / Y: " << struc->yPos << std::endl;
    }

}

int DPEngine_instance::onCreate()
{
    this->CalculateLayout();
    
    return 0;
}

int __fastcall DPEngine_instance::onUpdate()
{

    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        camera_mutex.lock();
        float cameraX = disX;
        float cameraY = disY;
        camera_mutex.unlock();
        float dummy_x;
        float dummy_y;
        BeginPaint(m_hwnd, &ps);
        pRenderTarget->BeginDraw();
        //background
        pRenderTarget->Clear(pBrushes[this->backgroundColor]->GetColor());

        if (!bkBufferMutex.try_lock()) {
            std::this_thread::yield();
            bkBufferMutex.lock();
        }
        pRenderTarget->DrawBitmap(bkbuffer, D2D1::RectF(-cameraX, -cameraY, this->zoomed_size() * DWARPO_GRID_WIDTH - cameraX, this->zoomed_size() * DWARPO_GRID_HEIGHT - cameraY), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, bkSrcRect);
        bkBufferMutex.unlock();
        //drawYOrderedEntities
        D2D1_RECT_F actualRect;   
        for (Entity* const &ent : entityList)
        {
            dummy_x = -cameraX + tileSize() * ent->xPos;
            dummy_y = -cameraY + tileSize() * ent->yPos;
            //dont render if out of view
            if (dummy_x > -50.0f && dummy_x < width + 50.0f && dummy_y > -50.0f && dummy_y < height + 50.0f) {

                
                
                pRenderTarget->DrawBitmap(

                    spriteManager->animationbuffer,
                    D2D1::RectF(dummy_x, dummy_y, tileSize() + dummy_x, tileSize() + dummy_y),
                    1.0f,
                    D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                    ent->currentFrame
                );
                


            }



        }


        DrawObject** pToDraw = NULL;
        ListElem<DrawableEntity>* curr;

        curr = this->drawEntities->firstListElem();
        int i = 0;
        unsigned short drawOSize = 0;
        while(curr!=NULL) {
            pToDraw = curr->element->getObjectStart();
            drawOSize = curr->element->drawObjectsSize;
            for (int i = 0; i < drawOSize; i++) {
                this->handleDrawObject(curr->element->x, curr->element->y,*pToDraw);
                pToDraw++;
            }
            curr = curr->next;

        }

        

        //DEBUG: in Order to be able to correctly point Rectangles to Buffers, these will output the buffers (static and animation on top of the playing fields if unquotet)
        if (SHOWSTATICBUFFER) {
            pRenderTarget->DrawBitmap(spriteManager->staticBuffer, D2D1::RectF(), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, spriteManager->staticBuffer->GetSize().width, spriteManager->staticBuffer->GetSize().height));
            pRenderTarget->DrawBitmap(spriteManager->getp_AnimationBitMap(), D2D1::RectF(-cameraX, -cameraY, tileSize() * DWARPO_GRID_WIDTH - cameraX, tileSize() * DWARPO_GRID_HEIGHT - cameraY), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, bkSrcRect);
            pRenderTarget->DrawBitmap(spriteManager->getp_StaticBitMap(), D2D1::RectF(-cameraX, -cameraY, tileSize() * DWARPO_GRID_WIDTH - cameraX, tileSize() * DWARPO_GRID_HEIGHT - cameraY), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, bkSrcRect);


        }

        if (INITDEBUGBUFFER) {
        pRenderTarget->DrawBitmap(this->debugbuffer, D2D1::RectF(-cameraX, -cameraY, tileSize() * DWARPO_GRID_WIDTH - cameraX, tileSize() * DWARPO_GRID_HEIGHT - cameraY), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, bkSrcRect);
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


//legacy rendering of simplistic shapes. Only used for the debug grid at this point
inline void __fastcall DPEngine_instance::handleDrawObject(float x, float y, DrawObject* pDrawO) {
    float displayX;
    float displayY;
    camera_mutex.lock();
    displayX = (x - disX);
    displayY = (y - disY);
    camera_mutex.unlock();

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


//this is a legacy version of rendering using simple shapes. This is essentially outclassed by the sprite rendering, but is still used to add the debug grid
void __thiscall DPEngine_instance::fillBuffer()
{
    {
        //this is for debug purposes, to be removed later, maybe
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

inline void __fastcall DPEngine_instance::drawDebugGridObject(float x, float y, DrawObject* pDrawO)
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



        
        D2D1_RECT_F rectangle2 = D2D1::RectF(x+pDrawO->getLeft(), y+pDrawO->getTop(), x+pDrawO->getRight(), y+pDrawO->getBottom());
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
 

}

void DPEngine_instance::BKey() {
    camera_mutex.lock();
    this->disX = model->getBaseX();
    this->disY = model->getBaseY();
    camera_mutex.unlock();
}

HRESULT __stdcall DPEngine_instance::CreateD3DDevice(IDXGIAdapter* pAdapter, D3D10_DRIVER_TYPE driverType, UINT flags, ID3D10Device1** ppDevice)
{
    {
        HRESULT hr = S_OK;

        static const D3D10_FEATURE_LEVEL1 levelAttempts[] =
        {
            D3D10_FEATURE_LEVEL_10_0,
            D3D10_FEATURE_LEVEL_9_3,
            D3D10_FEATURE_LEVEL_9_2,
            D3D10_FEATURE_LEVEL_9_1,
        };

        for (UINT level = 0; level < ARRAYSIZE(levelAttempts); level++)
        {
            ID3D10Device1* pDevice = NULL;
            hr = D3D10CreateDevice1(
                pAdapter,
                driverType,
                NULL,
                flags,
                levelAttempts[level],
                D3D10_1_SDK_VERSION,
                &pDevice
            );

            if (SUCCEEDED(hr))
            {
                // transfer reference
                *ppDevice = pDevice;
                pDevice = NULL;
                break;
            }

        }

        return hr;
    }
}

void DPEngine_instance::WKey()
{
       
    cameraKey_mutex.lock();
    if (camMovY >= 0) {
        //the first bit is the relevant one for isPressed. 
        //  & is bitwise AND (which is one of the most effective CPU commands) -->    100000 & 100000 == 100000  / 000011 & 100000 == 000000
        if ((!(GetKeyState('S') & 0x8000)) || camMovY >0) {
            camMovY--;

        }
    }
    cameraKey_mutex.unlock();
}

void DPEngine_instance::WKeyUp()
{

    cameraKey_mutex.lock();
    if (camMovY <= 0) {
        camMovY++;
    }
    cameraKey_mutex.unlock();
}

void DPEngine_instance::AKey()
{
    cameraKey_mutex.lock();
    if (camMovX >= 0) {
        if ((!(GetKeyState('D') & 0x8000)) || camMovX > 0) {
            camMovX--;

        }
    }
    cameraKey_mutex.unlock();
}

void DPEngine_instance::AKeyUp()
{
    cameraKey_mutex.lock();
    if (camMovX <= 0) {
        camMovX++;
    }
    cameraKey_mutex.unlock();
}

void DPEngine_instance::SKey()
{

    cameraKey_mutex.lock();
    if (camMovY <= 0) {
        if ((!(GetKeyState('W') & 0x8000)) || camMovY < 0) {
            camMovY++;

        }
    }
    cameraKey_mutex.unlock();
}

void DPEngine_instance::SKeyUp()
{
    cameraKey_mutex.lock();
    if (camMovY >= 0) {
        camMovY--;
    }
    cameraKey_mutex.unlock();
}

void DPEngine_instance::DKey()
{
    cameraKey_mutex.lock();
    if (camMovX <= 0) {
        if ((!(GetKeyState('A') & 0x8000)) || camMovX < 0) {
            camMovX++;

        }
    }
    cameraKey_mutex.unlock();
}

void DPEngine_instance::DKeyUp()
{
    cameraKey_mutex.lock();
    if (camMovX >= 0) {
        camMovX--;
    }
    cameraKey_mutex.unlock();
}





void DPEngine_instance::drawBkBuffer()
{

    HRESULT hr = CreateGraphicsResources();
    if (!SUCCEEDED(hr)) {
        printf_s("COULD NOT CREATE GRAPHICS RESOURCES");
        return;
    }

    baseTile* curr;

    float xTar;
    float yTar;
    D2D1_RECT_F rect;
    bkBufferMutex.lock();

    this->pbkBufferTarget->BeginDraw();
    
    for (int y = 0; y < DWARPO_GRID_HEIGHT; y++) {
        for (int x = 0; x < DWARPO_GRID_WIDTH; x++) {
            curr = model->getTileAt(x, y);
            xTar = x * tileSize();
            yTar = y * tileSize();
            rect = D2D1::RectF(xTar, yTar, xTar + tileSize(), yTar + tileSize());
            //this was needed to reset a transformation that some other rendering method needed. Unnecessary if skipped.
            
            pbkBufferTarget->DrawBitmap(spriteManager->getp_StaticBitMap(), rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, curr->getRect());
            if (DWARPO_SHOWGRID) {
                drawDebugGridObject(xTar, yTar, this->drawObjectBuffer+490);
            }
        }
    }
    for (auto &ent:structureList) {

        Structure* struc = static_cast<Structure*>(ent);
        rect = D2D1::RectF(struc->targetRect.left, tileSize()  + struc->targetRect.top,  struc->targetRect.right, tileSize() + struc->targetRect.bottom);
        pbkBufferTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        pbkBufferTarget->DrawBitmap(

            spriteManager->staticBuffer,
            rect,
            1.0f,
            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
            struc->getFrameRect()
        );


    }


    if (SUCCEEDED(pbkBufferTarget->EndDraw()) ){
        std::cout << "Updated bkgrndBuffer \n";
    }
    else {
        std::cout << "Failed updating the bkgrndBuffer\n";
    }
    bkBufferMutex.unlock();
}







LRESULT DPEngine_instance::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    int ret;
    switch (uMsg)
    {
    case WM_MOUSEWHEEL:
        //TODO compute mousewheel
        break;
    case WM_CREATE:
        if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED))) {
            printf_s("FAILED initializing COM-Components");
            return -1;
        }
        if (FAILED(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_MULTI_THREADED, &pFactory)))
        {
            printf_s("FAILED to create Resource DPEngine_instance.pFactory (ID2D1HwndRenderTarget)\n");
            return -1;  // Fail CreateWindowEx.

        }


        /*
        if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pdxgiFactory))) {
            printf_s("FAILED t create Resource DPEngine_instance.pdxgiFactory");
            return -1;
        }*/
        
        if (FAILED(this->CreateD3DDevice(
            NULL,
            D3D10_DRIVER_TYPE_HARDWARE,
            D3D10_CREATE_DEVICE_SINGLETHREADED | D3D10_CREATE_DEVICE_BGRA_SUPPORT,
            &this->pd3dDevice
            ))) {
            printf_s("FAILED creating DRIVER_TYPE_HARDWARE d3d10Device, falling back to WARP\n");
            if (FAILED(this->CreateD3DDevice(
                NULL,
                D3D10_DRIVER_TYPE_WARP,
                D3D10_CREATE_DEVICE_SINGLETHREADED | D3D10_CREATE_DEVICE_BGRA_SUPPORT,
                &this->pd3dDevice
            ))) {
                return -1;
            }
        }
        this->onCreate();
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        CoUninitialize();
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        return 0;

    case WM_DWARPO_DRAW: 

        onUpdate();

        pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        return 0;

    case WM_KEYDOWN:
        switch(wParam)
        {
        case VK_ESCAPE:
            ret = MessageBoxW(this->Window(), L"Verlassen?",
                L"Quit?", MB_OKCANCEL);

            if (ret == IDOK) {
                SendMessage(this->Window(), WM_CLOSE, 0, 0);
            }
            break;
        case 0x46:
            //PAUSE -> F-key
            break;
        case VK_SPACE:
            // cntrl->spaceBar();
            break;
        case VK_LEFT:
            // cntrl->left();
            break;
        case VK_RIGHT:
            // cntrl->right();
            break;
        case 0x57: //W
            this->WKey();
            break;
        case 0x41: //A
            this->AKey();
            break;
        case 0x53: //S
            this->SKey();
            break;
        case 0x44: //D
            this->DKey();
            break;
        case 'B':
            this->BKey();
            break;
        }
        break;
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_SPACE:
            // cntrl->spaceBar();
            break;
        case VK_LEFT:
            // cntrl->left();
            break;
        case VK_RIGHT:
            // cntrl->right();
            break;
        case 0x57: //W
            this->WKeyUp();
            break;
        case 0x41: //A
            this->AKeyUp();
            break;
        case 0x53: //S
            this->SKeyUp();
            break;
        case 0x44: //D
            this->DKeyUp();
            break;
        }
        break;

    case WM_SIZE:
        Resize();
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}


//example implementation on how to use the debugBuffer to display functional information
//this function draws TO the debug buffer.
//in this case, this will draw shapes representative of the LinkedChunkMap from MapGenerator.cpp

void DPEngine_instance::drawDebugChunks(QueueTypeLinkedList<LinkedChunk>* &chunks, int w, int h)
{
    ID2D1SolidColorBrush* pbrush = NULL;
    HRESULT hr = 0;

    CreateGraphicsResources();
    if (pbrush == NULL) {
        hr = pdebugBufferTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &pbrush);
    }

    if (SUCCEEDED(hr)) {
        float tileSiz = this->zoomed_size() * 0.7;
       // if (w != 0 || h != 0) return;
        //if (w != 0) return;
        this->pdebugBufferTarget->BeginDraw();
        D2D1_RECT_F rect = D2D1::RectF(0, 0, tileSiz * (w), tileSiz * h);
        this->pdebugBufferTarget->FillRectangle(rect, this->pbkBufferBrushes[DrawO_COLOR_BLUE]);
        LinkedChunk* custart = chunks->firstListElem()->element;

        LinkedChunk* current = custart;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {

                if (current->northBlocked) {
                    this->pdebugBufferTarget->DrawLine(D2D1::Point2F(tileSiz*j, tileSiz*i),D2D1::Point2F(tileSiz*(j+1), tileSiz*i), pbrush, 3.0f);
                }
                if (current->southBlocked) {
                    this->pdebugBufferTarget->DrawLine(D2D1::Point2F(tileSiz * j, tileSiz * (i+1)), D2D1::Point2F(tileSiz * (j + 1), tileSiz * (i+1)), pbrush, 3.0f);
                }
                if (current->eastBlocked) {
                    this->pdebugBufferTarget->DrawLine(D2D1::Point2F(tileSiz * (j+1), tileSiz * i), D2D1::Point2F(tileSiz * (j + 1), tileSiz * (i+1)), pbrush, 3.0f);
                }
                if (current->westBlocked) {
                    this->pdebugBufferTarget->DrawLine(D2D1::Point2F(tileSiz * j, tileSiz * i), D2D1::Point2F(tileSiz * (j ), tileSiz * (i+1)), pbrush);
                }

                current = current->east;
            }
            custart = custart->south;
            current = custart;
        }

        
        hr = this->pdebugBufferTarget->EndDraw();
    }


    this->pRenderTarget->BeginDraw();
    pRenderTarget->DrawBitmap(this->debugbuffer, D2D1::RectF(-disX, -disY, this->zoomed_size() * DWARPO_GRID_WIDTH - disX, this->zoomed_size() * DWARPO_GRID_HEIGHT - disY), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, bkSrcRect);
    this->pRenderTarget->EndDraw();
    return;
}
