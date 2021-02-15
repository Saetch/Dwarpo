#pragma once
#include "BaseWindow.h"
#include <Windows.h>
#include <windows.h>
#include <d2d1.h>
#include <d2d1_1.h> 
#include <d3d10_1.h>

#pragma comment(lib, "d3d10_1.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "d2d1")



//object-oriented aproach
//template classes must be defined in header files or subsequent .h (CLASS-X_impl.h or CLASS-X.hpp) files
template <class DERIVED_TYPE>
class BaseWindow
{
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        //get the pointer to the object from Userdata pointer of the window
        DERIVED_TYPE* pThis = NULL;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->m_hwnd = hwnd;
        }
        else
        {
            pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }
        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    BaseWindow() : m_hwnd(NULL) { }

    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    )
    {
        WNDCLASS wc = { 0 };
        
        wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();
        wc.hCursor= LoadCursor(NULL, IDC_ARROW);


        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(
            dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
        );

        return (m_hwnd ? TRUE : FALSE);
    }

    HWND Window() const { return m_hwnd; }


    template <class T>
    static inline void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            (*ppT)->Release();
            *ppT = NULL;
        }
    }

protected:

    virtual const PCWSTR  ClassName() = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};