#include "SpriteManager.h"
//#include <sstream>
//#include <fileapi.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "base64.h"
HRESULT SpriteManager::LoadBitmapFromFileTrgt(ID2D1RenderTarget* pRenderTarget, const char* uri, D2D1_RECT_F destinationRect,
    D2D1_RECT_F sourceRect)
{
    ID2D1Bitmap* pBitmap = NULL;
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;
    IWICBitmapScaler* pScaler = NULL;


    std::string str;
    std::ifstream in(uri, ::std::ios::binary);
    unsigned int length = 0;
    while (in) {
        char c;
        in.get(c);
        if (in) {
            //::std::cout << "Read a " << int(c) << "\n";
            length++;
            str = str + c;
        }
    }
    in.close();

    //first 3 byte are data type and thus need to be excluded

    BYTE* buffer = new BYTE[length-3];
    const char* c_str = new char[str.size()-3];
    str = str.substr(3, str.length());
    c_str = str.c_str();
    for (int i = 0; i < str.size(); i++) {
        printf_s("Orig: %d\n", c_str[i]);
    }
    str = base64_decode(c_str, str.size());
    c_str = str.c_str();
    for (int i = 0; i < str.size(); i++) {
        printf_s("Read a %d\n", int(c_str[i]));
        buffer[i] = c_str[i];
    }


    HRESULT hr = pIWICFactory->CreateStream(&pStream);


    if (SUCCEEDED(hr)) {

        hr = pStream->InitializeFromMemory(buffer, length);

    }


    if (SUCCEEDED(hr)) {

    hr = pIWICFactory->CreateDecoderFromStream(
        pStream,
        NULL,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder);
    }



    if (SUCCEEDED(hr))
    {
        printf_s("SUCC1\n");

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

HRESULT SpriteManager::LoadBitmapFromFile(const char* uri, D2D1_RECT_F destinationRect,
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
        "Sprites/Entities/Knight/Knight1.txt",
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
