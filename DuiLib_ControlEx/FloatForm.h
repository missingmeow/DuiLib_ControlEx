#pragma once
#include "../ControlEx/FloatWinBase.h"

class CFloatForm : public FloatWinBase
{
public:
    CFloatForm();
    ~CFloatForm();

    CDuiString GetSkinFile();
    LPCTSTR GetWindowClassName() const;

    void SetEditText(CDuiString& str);

    void InitWindow();
    void Notify(TNotifyUI& msg);

    void OnClick(TNotifyUI& msg);
private:

};
