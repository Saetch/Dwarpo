#include "SpriteManager.h"


HRESULT SpriteManager::LoadBitmapFromFileTrgt(ID2D1RenderTarget* pRenderTarget, PCWSTR uri, D2D1_RECT_F destinationRect,
    D2D1_RECT_F sourceRect)
{
    ID2D1Bitmap* pBitmap = NULL;
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;
    IWICBitmapScaler* pScaler = NULL;



    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );


    if (SUCCEEDED(hr))
    {

        // Convert the image format to 32bppPBGRA
        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
        hr = pIWICFactory->CreateFormatConverter(&pConverter);

    }


    if (SUCCEEDED(hr))
    {
        // Create the initial frame.
        hr = pDecoder->GetFrame(0, &pSource);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pSource,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.f,
            WICBitmapPaletteTypeMedianCut
        );
    }

    if (SUCCEEDED(hr))
    {

        // Create a Direct2D bitmap from the WIC bitmap.
        hr = pRenderTarget->CreateBitmapFromWicBitmap(
            pConverter,
            NULL,
            &pBitmap
        );
    }

    //copy volatile Bitmap to StaticBuffer or AnimationBuffer
    if (SUCCEEDED(hr)) {
        pRenderTarget->BeginDraw();

        pRenderTarget->DrawBitmap(pBitmap, destinationRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);

        pRenderTarget->EndDraw();
    }

    SafeRelease(&pDecoder);
    SafeRelease(&pDecoder);
    SafeRelease(&pSource);
    SafeRelease(&pStream);
    SafeRelease(&pConverter);
    SafeRelease(&pScaler);
    SafeRelease(&pBitmap);

	return hr;
}

HRESULT SpriteManager::LoadBitmapFromFile(PCWSTR uri, D2D1_RECT_F destinationRect,
    D2D1_RECT_F sourceRect)
{
    return this->LoadBitmapFromFileTrgt(this->pstaticBufferTarget, uri, destinationRect, sourceRect);
}

HRESULT SpriteManager::loadKnightToAnimBuffer()
{
    HRESULT hr = CB_OKAY;
    //here, the correct measurements need to be taken, in order to put the sprites at the correct spot in the buffer.
    hr = LoadBitmapFromFileTrgt(
        this->panimationBufferTarget, 
        L"Sprites/Entities/Knight/Idle.png",
        //this will make sure where the copied image is put
        D2D1::RectF(0.0f, 0.0f, defaultWidth* 40, defaultHeight),
        //this will make sure where the original image will be cut. Only important if there are "blank" spaces to be skipped.
        //If number is higher than resolution, will just use max.
        D2D1::RectF(0.0f, 46.0f, 1350.0f, 86.0f)
    );
    
    if (SUCCEEDED(hr)) {
        printf_s("SUCCEEDED loading Sprite to anim Buffer!\n");
    }
    

    return hr;
}




































HRESULT SpriteManager::loadSpritesToAnimBuffer()
{
    HRESULT hr = loadKnightToAnimBuffer();


    return hr;
}



HRESULT SpriteManager::loadSpritesToStaticBuffer()
{
    HRESULT hr = CB_OKAY;

    return hr;
}
