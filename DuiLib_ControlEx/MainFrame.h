#pragma once
#include "stdafx.h"

class CMainFrame : public WindowImplBase
{
public:
    CMainFrame();
    ~CMainFrame();

    virtual CDuiString GetSkinFolder();
    virtual CDuiString GetSkinFile();
    virtual LPCTSTR GetWindowClassName(void) const;

    virtual void InitWindow();
    virtual void OnClick(TNotifyUI& msg);
    virtual void Notify(TNotifyUI& msg);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};