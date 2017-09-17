#include "MainFrame.h"
#include "FloatForm.h"

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
    CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listview")));
    for(int i = 0; i< 4; i++)
    {
        CListTextElementUI* pItem = new CListTextElementUI();
        pList->Add(pItem);
        pItem->SetTag(i);
        CDuiString str;
        str.Format(_T("%d"), i);
        pItem->SetText(0, str);
        str.Format(_T("标题%d"), i);
        pItem->SetText(1, str);
        pItem->SetText(2, _T("这是内容填充，重要的是要长。这是内容填充，重要的是要长。这是内容填充，重要的是要长。"));
    }
}

void CMainFrame::Notify(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_ITEMACTIVATE)
    {
        CListTextElementUI* pItem = static_cast<CListTextElementUI*>(msg.pSender);
//         int nTag = pItem->GetTag();
//         CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listview")));
//         for (int i = 0; i < pList->GetCount(); i++)
//         {
//             CListTextElementUI* p = static_cast<CListTextElementUI*>(pList->GetItemAt(i));
//             if (p->GetTag() == nTag)
//             {
//                 break;
//             }
//         }
        RECT rect = pItem->GetPos();
        POINT ptWnd = { rect.left, rect.top };
        ::ClientToScreen(GetHWND(), &ptWnd);
        int nWidth = rect.right - rect.left;
        rect.left = ptWnd.x;
        rect.right = ptWnd.x + nWidth;
        int nHeight = rect.bottom - rect.top;
        rect.top = ptWnd.y + nHeight;
        rect.bottom = rect.top + nHeight + 60;
        CDuiString str;
        str.Format(_T("序号：%s \n标题：%s\n内容：%s"), pItem->GetText(0), pItem->GetText(1), pItem->GetText(2));

        CFloatForm* pForm = new CFloatForm();
        pForm->Create(GetHWND(), pItem);
        pForm->SetWindowRect(rect);
        pForm->SetEditText(str);
    }

    __super::Notify(msg);
}

void CMainFrame::OnClick(TNotifyUI& msg)
{
    CDuiString sName = msg.pSender->GetName();
    if (sName == _T("start_progress"))
    {
        SetTimer(GetHWND(), 0, 250, 0);
        msg.pSender->SetVisible(false);
        static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("stop_progress")))->SetVisible(true);
        return;
    }
    else if (sName == _T("stop_progress"))
    {
        KillTimer(GetHWND(), 0);
        msg.pSender->SetVisible(false);
        static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("start_progress")))->SetVisible(true);
        return;
    }
    else if (sName == _T("float_form_btn"))
    {
        CButtonUI* pBtn = (CButtonUI*)msg.pSender;
        RECT rect = pBtn->GetPos();
        int nHeight = rect.bottom - rect.top;
        int nWidth = rect.right - rect.left;
        CFloatForm* pForm = new CFloatForm();
        pForm->Create(GetHWND(), msg.pSender);
        pForm->SetWindowSize(SIZE{ 200,110 });
        return;
    }
    else if (sName == _T("closebtn"))
    {
        ::PostQuitMessage(0);
        return;
    }
    
    __super::OnClick(msg);
}

void CMainFrame::OnSelectChanged(TNotifyUI &msg)
{
    CTabLayoutUI* pTabSwitch = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_switch")));
    if (msg.pSender->GetName().CompareNoCase(_T("circle_progress_tab")) == 0) 
        pTabSwitch->SelectItem(0);
    else if (msg.pSender->GetName().CompareNoCase(_T("float_form_tab")) == 0)
        pTabSwitch->SelectItem(1);
}

LRESULT CMainFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
            bHandled = true;
            
            return 0;
        }
    }

    return __super::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
}
