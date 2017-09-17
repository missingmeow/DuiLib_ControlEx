#include "stdafx.h"
#include "FloatWinBase.h"

FloatWinBase::FloatWinBase()
    : m_nOffset(0)
    , m_bFloatOut(true)
{
}

FloatWinBase::~FloatWinBase()
{
}

CDuiString FloatWinBase::GetSkinFolder()
{
    return _T("");
}

HWND FloatWinBase::Create(RECT rect)
{
    m_rcClient = rect;
    return Create(NULL, _T("FloatWinBase"), WS_POPUP | WS_VISIBLE, WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST, m_rcClient);
}

HWND FloatWinBase::Create(HWND hwndParent, CControlUI* pControl)
{
    m_pControl = pControl;
    RECT rcConrol = pControl->GetPos();
    POINT ptWnd = { rcConrol.left, rcConrol.top };
    ::ClientToScreen(hwndParent, &ptWnd);
    m_rcClient.left = ptWnd.x;
    m_rcClient.right = ptWnd.x + rcConrol.right - rcConrol.left;
    m_rcClient.top = ptWnd.y;
    m_rcClient.bottom = ptWnd.y + rcConrol.bottom - rcConrol.top;
    return Create(hwndParent, _T("FloatWinBase"), WS_POPUP | WS_VISIBLE, WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST, m_rcClient);
}

HWND FloatWinBase::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu)
{
    return __super::Create(hwndParent, pstrName, dwStyle, dwExStyle, rc, hMenu);
}

HWND FloatWinBase::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int cx, int cy, HMENU hMenu)
{
    return __super::Create(hwndParent, pstrName, dwStyle, dwExStyle, x, y, cx, cy, hMenu);
}

HWND FloatWinBase::CreateDuiWindow(HWND hwndParent, LPCTSTR pstrWindowName, DWORD dwStyle, DWORD dwExStyle)
{
    return __super::CreateDuiWindow(hwndParent, pstrWindowName, dwStyle, dwExStyle);
}

void FloatWinBase::SetWindowRect(RECT rect)
{
    m_rcClient = rect;
    if (m_pControl)
    {
        RECT rcConrol = m_pControl->GetPos();
        POINT ptWnd = { rcConrol.left, rcConrol.top };
        ::ClientToScreen(GetParent(*this), &ptWnd);
        if (ptWnd.x != rect.left || ptWnd.y != rect.top)
            m_pControl = nullptr;
    }
}

void FloatWinBase::SetWindowSize(SIZE size)
{
    m_rcClient.right = m_rcClient.left + size.cx;
    m_rcClient.bottom = m_rcClient.top + size.cy;
}

void FloatWinBase::SetFloatOut(bool b)
{
    m_bFloatOut = b;
}

void FloatWinBase::Notify(TNotifyUI& msg)
{

}

CControlUI* FloatWinBase::CreateControl(LPCTSTR pstrClass)
{
    return nullptr;
}

LRESULT FloatWinBase::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
    styleValue &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    m_PaintManager.Init(m_hWnd);

    CDialogBuilder builder;
    CDuiString strResourcePath = m_PaintManager.GetResourcePath();
    if (strResourcePath.IsEmpty())
    {
        strResourcePath = m_PaintManager.GetInstancePath();
        strResourcePath += GetSkinFolder().GetData();
    }
    m_PaintManager.SetResourcePath(strResourcePath.GetData());

    CControlUI* pRoot = NULL;
    pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, this, &m_PaintManager);
    ASSERT(pRoot);
    if (pRoot == NULL)
    {
        MessageBox(NULL, _T("加载资源文件失败"), _T("Duilib"), MB_OK | MB_ICONERROR);
        ExitProcess(1);
        return 0;
    }
    m_PaintManager.AttachDialog(pRoot);
    m_PaintManager.AddNotifier(this);

    InitWindow();

    return 0;
}

LRESULT FloatWinBase::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (wParam == TIMER_FLOAT_IN)
    {
        int iWidth = m_rcClient.right - m_rcClient.left;
        int iHeight = m_rcClient.bottom - m_rcClient.top;

        if (m_nOffset + 20 > iHeight)
        {
            m_nOffset = iHeight;
            KillTimer(GetHWND(), TIMER_FLOAT_IN);
        }
        else
        {
            m_nOffset += 20;
        }

        ::MoveWindow(*this, m_rcClient.left, m_rcClient.top, iWidth, m_nOffset, TRUE);
    }
    else if (wParam == TIMER_FLOAT_OUT)
    {
        int iWidth = m_rcClient.right - m_rcClient.left;
        int iHeight = m_rcClient.bottom - m_rcClient.top;

        RECT rcConrol = m_pControl->GetPos();
        POINT ptWnd = { rcConrol.left, rcConrol.top };
        ::ClientToScreen(GetParent(m_hWnd), &ptWnd);

        m_nOffset -= 20;
        if (m_nOffset <= 0 || (m_rcClient.left != ptWnd.x || m_rcClient.top != ptWnd.y))
        {
            m_nOffset = 0;
            KillTimer(GetHWND(), TIMER_FLOAT_OUT);
            Close(0);
        }

        ::MoveWindow(*this, ptWnd.x, ptWnd.y, iWidth, m_nOffset, TRUE);
    }

    return 0;
}

LRESULT FloatWinBase::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (m_pControl && m_bFloatOut)
    {
        KillTimer(GetHWND(), TIMER_FLOAT_IN);
        SetTimer(GetHWND(), TIMER_FLOAT_OUT, 20, NULL);
    }
    else
        Close(0);
    return 0;
}

LRESULT FloatWinBase::OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    SetTimer(GetHWND(), TIMER_FLOAT_IN, 20, NULL);
    return 0;
}

LRESULT FloatWinBase::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRes = 0;
    BOOL bHandled = TRUE;
    switch (uMsg)
    {
    case WM_CREATE:         lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
    case WM_TIMER:          lRes = OnTimer(uMsg, wParam, lParam, bHandled); break;
    case WM_KILLFOCUS:      lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); break;
    case WM_SHOWWINDOW:     lRes = OnShowWindow(uMsg, wParam, lParam, bHandled); break;
    default:                bHandled = FALSE; break;
    }
    if (bHandled) return lRes;
    if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
    return __super::HandleMessage(uMsg, wParam, lParam);
}