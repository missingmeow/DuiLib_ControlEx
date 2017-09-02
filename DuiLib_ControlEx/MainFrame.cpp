#include "MainFrame.h"

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{

}

DUI_BEGIN_MESSAGE_MAP(CMainFrame, WinBase)
DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
DUI_END_MESSAGE_MAP()

CDuiString CMainFrame::GetSkinFile()
{
    return _T("main.xml");
}

LPCTSTR CMainFrame::GetWindowClassName(void) const
{
    return _T("MainFrame");
}

void CMainFrame::InitWindow()
{

}

void CMainFrame::Notify(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_SELECTCHANGED)
    {

    }

    __super::Notify(msg);
}

void CMainFrame::OnClick(TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("start_progress"))
    {
        SetTimer(GetHWND(), 0, 250, 0);
        msg.pSender->SetVisible(false);
        static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("stop_progress")))->SetVisible(true);
        return;
    }
    else if (msg.pSender->GetName() == _T("stop_progress"))
    {
        KillTimer(GetHWND(), 0);
        msg.pSender->SetVisible(false);
        static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("start_progress")))->SetVisible(true);
        return;
    }
    __super::OnClick(msg);
}

void CMainFrame::OnSelectChanged(TNotifyUI &msg)
{
    CTabLayoutUI* pTabSwitch = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_switch")));
    if (msg.pSender->GetName().CompareNoCase(_T("circle_progress_tab")) == 0) 
        pTabSwitch->SelectItem(0);
    else if (msg.pSender->GetName().CompareNoCase(_T("test_tab")) == 0)
        pTabSwitch->SelectItem(1);
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_TIMER)
    {
        if (wParam == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                CDuiString str;
                str.Format(_T("cp%d"), i);
                CProgressUI* pcp = static_cast<CProgressUI*>(m_PaintManager.FindControl(str));
                int n = pcp->GetValue();
                n += 1;
                if (n > 100) n = 0;
                pcp->SetValue(n);
                str.Format(_T("%d%%"), n);
                pcp->SetText(str);
            }
        }
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}
