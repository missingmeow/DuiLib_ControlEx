#include "MainFrame.h"

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{

}

CDuiString CMainFrame::GetSkinFile()
{
    return _T("main.xml");
}

CDuiString CMainFrame::GetSkinFolder()
{
    return _T("");
}

LPCTSTR CMainFrame::GetWindowClassName(void) const
{
    return _T("MainFrame");
}

void CMainFrame::InitWindow()
{

}

void CMainFrame::OnClick(TNotifyUI& msg)
{
    __super::OnClick(msg);
}

void CMainFrame::Notify(TNotifyUI& msg)
{
    __super::Notify(msg);
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return __super::HandleMessage(uMsg, wParam, lParam);
}
