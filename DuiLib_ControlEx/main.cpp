#include "stdafx.h"
#include "MainFrame.h"

#if defined(WIN32) && !defined(UNDER_CE)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nCmdShow)
#endif
{
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("\skin"));

#if defined(WIN32) && !defined(UNDER_CE)
    HRESULT Hr = ::CoInitialize(NULL);
#else
    HRESULT Hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
    if (FAILED(Hr)) return 0;

    CMainFrame* pFrame = new CMainFrame();
    if (pFrame == NULL) return 0;
#if defined(WIN32) && !defined(UNDER_CE)
    pFrame->Create(NULL, _T("MainFrame"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 800);
#else
    pFrame->Create(NULL, _T("MainFrame"), UI_WNDSTYLE_FRAME, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif
    pFrame->CenterWindow();
    ::ShowWindow(*pFrame, SW_SHOW);

    CPaintManagerUI::MessageLoop();

    return 0;
}
