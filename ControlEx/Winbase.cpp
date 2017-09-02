#include "Winbase.h"
#include "UICircleProgress.h"

WinBase::WinBase()
{

}

WinBase::~WinBase()
{

}

CDuiString WinBase::GetSkinFolder()
{
    return _T("");
}

CControlUI* WinBase::CreateControl(LPCTSTR pstrClass)
{
    if (_tcscmp(pstrClass, DUI_CTR_CIRCLEPROGRESS) == 0)
        return new CCirecleProgressUI();
    return __super::CreateControl(pstrClass);
}

LRESULT WinBase::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    PostQuitMessage(0L);

    bHandled = FALSE;
    return 0;
}
