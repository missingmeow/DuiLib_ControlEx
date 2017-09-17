#include "FloatForm.h"


CFloatForm::CFloatForm()
{
}

CFloatForm::~CFloatForm()
{
}

CDuiString CFloatForm::GetSkinFile()
{
    return _T("float.xml");
}

LPCTSTR CFloatForm::GetWindowClassName() const
{
    return _T("FloatFrame");
}

void CFloatForm::OnClick(TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("close"))
    {
        Close(0);
    }
    else if (msg.pSender->GetName() == _T("clickMe"))
    {
        SetFloatOut(false);
        MessageBox(NULL, _T("你点击了我"), _T("提示"), 0);
    }
}

void CFloatForm::InitWindow()
{

}

void CFloatForm::Notify(TNotifyUI& msg)
{
    if (msg.sType == DUI_MSGTYPE_CLICK)
    {
        OnClick(msg);
    }

    __super::Notify(msg);
}

void CFloatForm::SetEditText(CDuiString& str)
{
    CRichEditUI* pEdit = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("richedit")));
    pEdit->SetText(str);
    pEdit->SetEnabled(true);
    LONG style = pEdit->GetWinStyle();
    style |= ES_DISABLENOSCROLL | WS_VSCROLL;
    pEdit->SetWinStyle(style);
    CButtonUI* pBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("clickMe")));
    pBtn->SetVisible(false);
}