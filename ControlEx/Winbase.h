#pragma once
#include "stdafx.h"

class WinBase : public WindowImplBase
{
public:
    WinBase();
    ~WinBase();

    virtual CDuiString GetSkinFile() = 0;
    virtual CDuiString GetSkinFolder();
    virtual LPCTSTR GetWindowClassName(void) const = 0;

    virtual CControlUI* CreateControl(LPCTSTR pstrClass);

    virtual void OnFinalMessage(HWND hWnd);
    virtual LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
};
