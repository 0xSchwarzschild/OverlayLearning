#include "framework.h"
#include "OverlayLeaning.h"
#include "draw.h"

#define MAX_LOADSTRING 100


HINSTANCE hInst;                                
WCHAR szTitle[100] = L"Overlay"; 
int width, height;
HWND OverlayHWND , targetHWND;
LPCSTR targetTitle = "Rainbow Six";
Draw draw = Draw();


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    

   

    MyRegisterClass(hInstance);

    targetHWND = FindWindowA(0, targetTitle);

    if (targetHWND)
    {
        RECT rect;
        GetWindowRect(targetHWND, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;


    }
    else
    {
        return FALSE;
    }
        


    
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    draw = Draw(OverlayHWND, targetHWND, width, height);

    

    MSG msg;

    
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            RECT rect;
            GetWindowRect(targetHWND, &rect);
            width = rect.right - rect.left;
            height = rect.bottom - rect.top;

            MoveWindow(OverlayHWND, rect.left, rect.top, width, height, true);
        
    }

    return (int) msg.wParam;
}



//

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = 0;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName   = szTitle;
    wcex.lpszClassName  = szTitle;


    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED , szTitle, szTitle, WS_POPUP,
      1, 1, width , height ,  nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    case WM_PAINT:
      draw.render();


       
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



