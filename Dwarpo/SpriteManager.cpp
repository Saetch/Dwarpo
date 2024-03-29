#pragma once

#include "SpriteManager.h"

#include <string>
#include <fstream>
#include "base64.h"

HRESULT loadDwarfStructures(SpriteManager* ths);

//writing a local function with a this argument removes overhead, since this function isn't needed in SpriteManager.h
HRESULT loadbitMapfromFileTarget(SpriteManager* ths, ID2D1RenderTarget* pRenderTarget, const char* uri, D2D1_RECT_F destinationRect,
    D2D1_RECT_F sourceRect);

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
    if (length < 10) {
        printf_s("THIS IS DEFINATELY WRONG. FILE NOT FOUND!\n");
    }
    BYTE* buffer = new BYTE[length - 3];
    const char* c_str;
    str = str.substr(3, str.length());
    c_str = str.c_str();

    str = base64_decode(c_str, str.size());
    c_str = str.c_str();
    for (int i = 0; i < str.size(); i++) {
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

    delete[] buffer;

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
        D2D1::RectF(0.0f, 0.0f, BufferTileSize* 40, BufferTileSize),
        //this will make sure where the original image will be cut. Only important if there are "blank" spaces to be skipped.
        //If number is higher than resolution, will just use max.
        D2D1::RectF(0.0f, 46.0f, 1350.0f, 86.0f)
    );
    
    if (SUCCEEDED(hr)) {
        printf_s("SUCCEEDED loading Sprite to anim Buffer!\n");
    }
    

    return hr;
}

HRESULT SpriteManager::loadInGameBackgroundToStaticBuffer()
{

    HRESULT hr = CB_OKAY;
    hr = LoadBitmapFromFileTrgt(
        this->pstaticBufferTarget,
        "Dwarpo_Sprites/Structures/ground/rock_background1.txt",
        D2D1::RectF(0.0f, 0.0f, BufferTileSize, BufferTileSize),
        D2D1::RectF(0.0f, 0.0f, 640.0f, 640.0f)
    );
    
    if (SUCCEEDED(hr)) {
        LoadBitmapFromFileTrgt(
            this->pstaticBufferTarget,
            "Dwarpo_Sprites/Structures/ground/rock_background2.txt",
            D2D1::RectF(BufferTileSize, 0.0f, BufferTileSize * 2, BufferTileSize),
            D2D1::RectF(0.0f, 0.0f, 640.0f, 640.0f)
        );
    }

    if (SUCCEEDED(hr)) {
        LoadBitmapFromFileTrgt(
            this->pstaticBufferTarget,
            "Dwarpo_Sprites/Structures/ground/rock_background3.txt",
            D2D1::RectF(BufferTileSize *2 , 0.0f, BufferTileSize * 3, BufferTileSize),
            D2D1::RectF(0.0f,0.0f, 640.0f,640.0f)
        );
    }

    if (SUCCEEDED(hr)) {
        LoadBitmapFromFileTrgt(
            this->pstaticBufferTarget,
            "Dwarpo_Sprites/Structures/ground/rock_background4.txt",
            D2D1::RectF(BufferTileSize * 3, 0.0f, BufferTileSize * 4, BufferTileSize),
            D2D1::RectF(0.0f, 0.0f,640.0f,640.0f)
        );
    }
    if (SUCCEEDED(hr)) {
        LoadBitmapFromFileTrgt(
            this->pstaticBufferTarget,
            "Dwarpo_Sprites/Structures/ground/background_Cave_pixelate1.txt",
            D2D1::RectF(BufferTileSize * 4, 0.0f, BufferTileSize * 5, BufferTileSize),
            D2D1::RectF(0.0f, 0.0f, 640.0f, 640.0f)
        );
    }
    if (SUCCEEDED(hr)) {
        LoadBitmapFromFileTrgt(
            this->pstaticBufferTarget,
            "Dwarpo_Sprites/Structures/ground/background_Cave_pixelate2.txt",
            D2D1::RectF(BufferTileSize * 5, 0.0f, BufferTileSize * 6, BufferTileSize),
            D2D1::RectF(0.0f, 0.0f, 640.0f, 640.0f)
        );
    }
    if (SUCCEEDED(hr)) {
        LoadBitmapFromFileTrgt(
            this->pstaticBufferTarget,
            "Dwarpo_Sprites/Structures/ground/background_Cave_pixelate3.txt",
            D2D1::RectF(BufferTileSize * 6, 0.0f, BufferTileSize * 7, BufferTileSize),
            D2D1::RectF(0.0f, 0.0f, 640.0f, 640.0f)
        );
    }
    if (SUCCEEDED(hr)) {
        LoadBitmapFromFileTrgt(
            this->pstaticBufferTarget,
            "Dwarpo_Sprites/Structures/ground/background_Cave_pixelate4.txt",
            D2D1::RectF(BufferTileSize * 7, 0.0f, BufferTileSize * 8, BufferTileSize),
            D2D1::RectF(0.0f, 0.0f, 640.0f, 640.0f)
        );
    }


    ID2D1SolidColorBrush* brush = NULL;
    //adjust brightness
    pstaticBufferTarget->BeginDraw();

    if (SUCCEEDED(hr)) {
        hr = pstaticBufferTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f,0.0f,0.2f,0.125f), &brush);

    }
   
    if (SUCCEEDED(hr)) {
       pstaticBufferTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f, 4*BufferTileSize, BufferTileSize), brush);
    }

    if (SUCCEEDED(hr)) {
        hr = pstaticBufferTarget->EndDraw();
    }


    if (SUCCEEDED(hr)) {
        printf_s("SUCCEEDED loading Grass-Sprite to static buffer!\n");
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

    hr = loadInGameBackgroundToStaticBuffer();

    if (SUCCEEDED(hr)) {
        hr = loadDwarfStructures(this);
    }
    return hr;
}

HRESULT loadDwarfStructures(SpriteManager* ths)
{
    HRESULT hr = CB_OKAY;

    hr = loadbitMapfromFileTarget(ths, ths->pstaticBufferTarget, "Dwarpo_Sprites/Structures/Dwarf/Dwarf_BaseHouse_px9.txt",
        D2D1::RectF(BufferTileSize, BufferTileSize, BufferTileSize + 4 * BufferTileSize, BufferTileSize +5* BufferTileSize), D2D1::RectF(140.0f, 55.0f, 510.0f, 580.0f));

    return hr;
}

HRESULT loadbitMapfromFileTarget(SpriteManager* ths, ID2D1RenderTarget* pRenderTarget, const char* uri, D2D1_RECT_F destinationRect, D2D1_RECT_F sourceRect)
{
    return ths->LoadBitmapFromFileTrgt(pRenderTarget, uri, destinationRect, sourceRect);
}
