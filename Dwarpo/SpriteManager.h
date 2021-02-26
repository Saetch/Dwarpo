#pragma once
#include <stdio.h>
#include <d2d1.h>
#include <wincodec.h>



#define ANIMATION_BUFFER_WIDTH 8000
#define ANIMATION_BUFFER_HEIGHT 8000
#define STATIC_BUFFER_WIDTH 4000
#define STATIC_BUFFER_HEIGHT 4000


template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class SpriteManager
{
private:
   



    IWICImagingFactory* pIWICFactory = NULL;
    ID2D1RenderTarget* pMainRenderTarget;

   


    

    HRESULT LoadBitmapFromFile(
        const char* uri,
        D2D1_RECT_F destinationRect,
        D2D1_RECT_F sourceRect
    );



    HRESULT loadSpritesToAnimBuffer();
    HRESULT loadSpritesToStaticBuffer();

    HRESULT loadKnightToAnimBuffer();

    HRESULT loadGrassToStaticBuffer();
public:
    ID2D1Bitmap* staticBuffer = NULL;
    ID2D1Bitmap* animationbuffer = NULL;
    ID2D1BitmapRenderTarget* pstaticBufferTarget = NULL;
    ID2D1BitmapRenderTarget* panimationBufferTarget = NULL;

    float defaultWidth = 0;
    float defaultHeight = 0;

    HRESULT LoadBitmapFromFileTrgt(
        ID2D1RenderTarget* pRenderTarget,
        const char* uri,
        D2D1_RECT_F destinationRect,
        D2D1_RECT_F sourceRect
    );

    SpriteManager(ID2D1RenderTarget* pMainRenderTarget, float defWidth, float defHeight) {


        this->defaultWidth = defWidth;

        this->defaultHeight = defHeight;

        this->pMainRenderTarget = pMainRenderTarget;

        HRESULT hr = pMainRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(STATIC_BUFFER_WIDTH, STATIC_BUFFER_HEIGHT), &pstaticBufferTarget);

        if (FAILED(hr)) goto failed;

        hr = pstaticBufferTarget->GetBitmap(&staticBuffer);

        if (FAILED(hr)) goto failed;

        hr = pMainRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(ANIMATION_BUFFER_WIDTH, ANIMATION_BUFFER_HEIGHT), &panimationBufferTarget);

        if (FAILED(hr)) goto failed;

        hr = panimationBufferTarget->GetBitmap(&animationbuffer);

        if (FAILED(hr)) goto failed;

        hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof( IWICImagingFactory ), reinterpret_cast<void**>(&pIWICFactory));

        if (FAILED(hr)) {
            printf_s("FAILED CREATING IWICFactory in SpriteManager.h\n");
        }

        return;

    failed:
        printf_s("FAILED CREATING SPRITEMANAGER!\n");
    }

    ~SpriteManager() {
        SafeRelease(&pIWICFactory);
        SafeRelease(&staticBuffer);
        SafeRelease(&pstaticBufferTarget);
        SafeRelease(&animationbuffer);
        SafeRelease(&panimationBufferTarget);
    }

    HRESULT loadSpritesToBuffer() {

        HRESULT hr = loadSpritesToStaticBuffer();

        if (SUCCEEDED(hr)) {
            printf_s("Loading Sprites to AnimBuffer!\n");
            hr = loadSpritesToAnimBuffer();
        }
        if (FAILED(hr)) {
            printf_s("FAILED LOADING SPRITES!\n");
        }
        return hr;
    }

    void setRenderTarget(ID2D1RenderTarget* pMainTarget) {
        pMainRenderTarget = pMainTarget;
    }

    
    inline ID2D1Bitmap* getp_StaticBitMap() {
        return this->staticBuffer;
    }

    inline ID2D1Bitmap* getp_AnimationBitMap() {
        return this->animationbuffer;
    }
};

