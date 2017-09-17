#pragma once
#include "../ControlEx/Winbase.h"

class CMainFrame : public WinBase
{
public:
    CMainFrame();
    ~CMainFrame();

    virtual CDuiString GetSkinFile();
    virtual LPCTSTR GetWindowClassName(void) const;

    virtual void InitWindow();
    virtual void OnClick(TNotifyUI& msg);
    virtual void Notify(TNotifyUI& msg);
    virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    DUI_DECLARE_MESSAGE_MAP()
    virtual void OnSelectChanged(TNotifyUI &msg);
};