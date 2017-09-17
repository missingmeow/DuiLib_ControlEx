#pragma once
#include "UIlib.h"

#define TIMER_FLOAT_IN  (WM_USER + 2591)
#define TIMER_FLOAT_OUT (WM_USER + 2592)

using namespace DuiLib;

class FloatWinBase : public CWindowWnd, public INotifyUI, public IDialogBuilderCallback
{
public:
    FloatWinBase();
    ~FloatWinBase();

    virtual LPCTSTR GetWindowClassName() const = 0;
    virtual CDuiString GetSkinFile() = 0;
    virtual CDuiString GetSkinFolder();

    void SetWindowRect(RECT rect);
    void SetWindowSize(SIZE size);
    void SetFloatOut(bool b);

public:
    HWND Create(RECT rect);
    HWND Create(HWND hwndParent, CControlUI* pControl);
private:
    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
    HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
    HWND CreateDuiWindow(HWND hwndParent, LPCTSTR pstrWindowName, DWORD dwStyle = 0, DWORD dwExStyle = 0);

public:
    virtual void InitWindow(){ }

    virtual void Notify(TNotifyUI& msg);
    virtual CControlUI* CreateControl(LPCTSTR pstrClass);

    virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
    CPaintManagerUI m_PaintManager;
private:
    bool        m_bFloatOut;   // 是否需要动态消失
    int         m_nOffset;
    RECT        m_rcClient;
    CControlUI* m_pControl = nullptr;
};
