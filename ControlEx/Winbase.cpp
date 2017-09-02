#include "Winbase.h"

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
    return __super::CreateControl(pstrClass);
}

LRESULT WinBase::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    PostQuitMessage(0L);

    bHandled = FALSE;
    return 0;
}
