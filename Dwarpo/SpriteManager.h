#pragma once
#include <windows.h>
#include <Windows.h>
#include <stdio.h>
#include <d2d1.h>
#include <d2d1_1.h> 
#include <d3d10_1.h>
#include <wincodec.h>

#pragma comment(lib, "d3d10_1.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d2d1")


#pragma comment(lib, "user32.lib")
class SpriteManager
{
public:

    IWICImagingFactory* pIWICFactory;
    ID2D1RenderTarget* pMainRenderTarget;

    UINT defaultWidth;
    UINT defaultHeight;


    HRESULT LoadBitmapFromFileTrgt(
        ID2D1RenderTarget* pRenderTarget,
        PCWSTR uri,
        UINT destinationWidth,
        UINT destinationHeight,
        ID2D1Bitmap** ppBitmap
    );

    HRESULT LoadBitmapFromFile(
        PCWSTR uri,
        UINT destinationWidth,
        UINT destinationHeight,
        ID2D1Bitmap** ppBitmap
    );

    void setRenderTarget(ID2D1RenderTarget* pMainTarget) {
        pMainRenderTarget = pMainTarget;
    }
};

