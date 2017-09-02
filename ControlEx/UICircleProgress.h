#pragma once
#include "stdafx.h"

#define DUI_CTR_CIRCLEPROGRESS _T("CircleProgress")

class CCirecleProgressUI : public CProgressUI
{
public:
    CCirecleProgressUI();
    ~CCirecleProgressUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    DWORD GetForeColor() const;
    void SetForeColor(DWORD dwForeColor);
    void SetBkImage(LPCTSTR pStrImage);
    void SetForeImage(LPCTSTR pStrImage);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    virtual void PaintBkColor(HDC hDC);
    virtual void PaintBkImage(HDC hDC);
    virtual void PaintStatusImage(HDC hDC);

private:
    void GetPaintPoint(vector<Gdiplus::Point>& vec, int angle = 0);
    void DeleteBkImage();
    void DeleteForeImage();
    Gdiplus::Image* GdiplusLoadImage(LPCTSTR pstrPath);

private:
    DWORD m_dwForeColor;
    Gdiplus::Image* m_pBkImage;
    Gdiplus::Image* m_pForeImage;
    int m_nRadius;
    int m_nInnerRadius;
    int m_nAngle;
    float m_fOriginalAngle;
};
