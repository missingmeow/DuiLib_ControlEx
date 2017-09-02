#include "UICircleProgress.h"

#define RotationAngle 3.6

CCirecleProgressUI::CCirecleProgressUI()
    : m_dwForeColor(0)
    , m_pBkImage(nullptr)
    , m_pForeImage(nullptr)
    , m_nRadius(0)
    , m_nInnerRadius(0)
    , m_nAngle(0)
    , m_fOriginalAngle(0)
{
}

CCirecleProgressUI::~CCirecleProgressUI()
{
    DeleteBkImage();
    DeleteForeImage();
}

LPCTSTR CCirecleProgressUI::GetClass() const
{
    return DUI_CTR_CIRCLEPROGRESS;
}

LPVOID CCirecleProgressUI::GetInterface(LPCTSTR pstrName)
{
    if (_tcscmp(pstrName, DUI_CTR_CIRCLEPROGRESS) == 0)
        return static_cast<CCirecleProgressUI*>(this);
    return CLabelUI::GetInterface(pstrName);
}

DWORD CCirecleProgressUI::GetForeColor() const
{
    return m_dwForeColor;
}

void CCirecleProgressUI::SetForeColor(DWORD dwForeColor)
{
    m_dwForeColor = dwForeColor;
}

void CCirecleProgressUI::SetBkImage(LPCTSTR pStrImage)
{
    if (m_diBk.sDrawString == pStrImage) return;
    m_diBk.Clear();
    m_diBk.sDrawString = pStrImage;
    DeleteForeImage();
    Invalidate();
}

void CCirecleProgressUI::SetForeImage(LPCTSTR pStrImage)
{
    if (m_diFore.sDrawString == pStrImage) return;
    m_diFore.Clear();
    m_diFore.sDrawString = pStrImage;
    DeleteForeImage();
    Invalidate();
}

void CCirecleProgressUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    if (_tcscmp(pstrName, _T("forecolor")) == 0)
    {
        while (*pstrValue > _T('\0') && *pstrValue <= _T(' ')) pstrValue = ::CharNext(pstrValue);
        if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        LPTSTR pstr = NULL;
        DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
        SetForeColor(clrColor);
    }
    else if (_tcscmp(pstrName, _T("radius")) == 0)
        m_nRadius = _ttoi(pstrValue);
    else if (_tcscmp(pstrName, _T("innerradius")) == 0)
        m_nInnerRadius = _ttoi(pstrValue);
    else if (_tcscmp(pstrName, _T("originalangle")) == 0)
        m_fOriginalAngle = (float)_ttof(pstrValue);
    else if (_tcscmp(pstrName, _T("angle")) == 0)
        m_nAngle = _ttoi(pstrValue);
    else __super::SetAttribute(pstrName, pstrValue);
}

void CCirecleProgressUI::PaintBkColor(HDC hDC)
{
    RECT rcItem = m_rcItem;
    int iWidth = rcItem.right - rcItem.left;
    int iHeight = rcItem.bottom - rcItem.top;
    Gdiplus::PointF centerPos((REAL)rcItem.left + iWidth / 2, (REAL)rcItem.top + iHeight / 2);
    if (m_nRadius == 0)
        m_nRadius = iWidth > iHeight ? iHeight / 2 : iWidth / 2;

    if (m_dwBackColor != 0 )
    {
        Gdiplus::Graphics g(hDC);

        if(m_nInnerRadius == 0)
        {
            Gdiplus::SolidBrush brush(m_dwBackColor);
            g.FillPie(&brush, centerPos.X - m_nRadius, centerPos.Y - m_nRadius, (REAL)2 * m_nRadius, (REAL)2 * m_nRadius, 0, 360);
        }
        else
        {
            vector<Gdiplus::Point> vec;
            GetPaintPoint(vec, 360);

            Gdiplus::Color ellipseColor(m_dwBackColor);
            Gdiplus::SolidBrush ellipseBrush(ellipseColor);

            Gdiplus::GraphicsPath gpath;
            gpath.AddCurve(&vec[0], vec.size());

            g.FillPath(&ellipseBrush, &gpath);
        }

        g.ReleaseHDC(hDC);
    }

    if (m_dwForeColor != 0)
    {
        Gdiplus::Graphics g(hDC);

        if (m_nInnerRadius == 0)
        {
            Gdiplus::SolidBrush brush(m_dwForeColor);
            if(m_nAngle < 90)
                g.FillPie(&brush, (REAL)centerPos.X - m_nRadius, (REAL)centerPos.Y - m_nRadius, (REAL)2 * m_nRadius, (REAL)2 * m_nRadius, (REAL)m_nAngle + 270, (REAL)360.0 * m_nValue / (m_nMax - m_nMin));
            else
                g.FillPie(&brush, (REAL)centerPos.X - m_nRadius, (REAL)centerPos.Y - m_nRadius, (REAL)2 * m_nRadius, (REAL)2 * m_nRadius, (REAL)m_nAngle - 90, (REAL)360.0 * m_nValue / (m_nMax - m_nMin));
        }
        else
        {
            vector<Gdiplus::Point> vec;
            GetPaintPoint(vec);

            Gdiplus::Color ellipseColor(m_dwForeColor);
            Gdiplus::SolidBrush ellipseBrush(ellipseColor);

            Gdiplus::GraphicsPath gpath;
            gpath.AddCurve(&vec[0], vec.size());

            g.FillPath(&ellipseBrush, &gpath);
        }

        g.ReleaseHDC(hDC);
    }
}

void CCirecleProgressUI::PaintBkImage(HDC hDC)
{
    if (m_pBkImage == nullptr)
        m_pBkImage = GdiplusLoadImage(GetBkImage());

    if (m_pBkImage == nullptr)
        return;

    RECT rcItem = m_rcItem;
    int iWidth = rcItem.right - rcItem.left;
    int iHeight = rcItem.bottom - rcItem.top;
    Gdiplus::PointF centerPos((REAL)rcItem.left + iWidth / 2, (REAL)rcItem.top + iHeight / 2);

    Gdiplus::Graphics graphics(hDC);
    graphics.TranslateTransform(centerPos.X, centerPos.Y);
    graphics.RotateTransform((REAL)m_nAngle);
    graphics.TranslateTransform(-centerPos.X, -centerPos.Y);
    graphics.DrawImage(m_pForeImage, rcItem.left, rcItem.top, iWidth, iHeight);
}

void CCirecleProgressUI::PaintStatusImage(HDC hDC)
{
    if (m_pForeImage == nullptr)
        m_pForeImage = GdiplusLoadImage(GetForeImage());

    if (m_pForeImage == nullptr)
        return;

    RECT rcItem = m_rcItem;
    int iWidth = rcItem.right - rcItem.left;
    int iHeight = rcItem.bottom - rcItem.top;
    Gdiplus::PointF centerPos((REAL)rcItem.left + iWidth / 2, (REAL)rcItem.top + iHeight / 2);

    Gdiplus::Graphics graphics(hDC);

    double angle = 360.0 * m_nValue / (m_nMax - m_nMin);

    if (angle > 0)
    {
        graphics.TranslateTransform(centerPos.X, centerPos.Y);
        graphics.RotateTransform((REAL)m_nAngle);
        graphics.TranslateTransform(-centerPos.X, -centerPos.Y);
        graphics.DrawImage(m_pForeImage, rcItem.left, rcItem.top, iWidth, iHeight);
    }

    angle -= m_fOriginalAngle;

    for (; angle > RotationAngle;)
    {
        angle -= RotationAngle;
        graphics.TranslateTransform(centerPos.X, centerPos.Y);
        graphics.RotateTransform((REAL)RotationAngle + m_nAngle);
        graphics.TranslateTransform(-centerPos.X, -centerPos.Y);
        graphics.DrawImage(m_pForeImage, rcItem.left, rcItem.top, iWidth, iHeight);
    }

    if(angle > 0)
    {
        graphics.TranslateTransform(centerPos.X, centerPos.Y);
        graphics.RotateTransform((REAL)angle + m_nAngle);
        graphics.TranslateTransform(-centerPos.X, -centerPos.Y);
        graphics.DrawImage(m_pForeImage, rcItem.left, rcItem.top, iWidth, iHeight);
    }
}

void CCirecleProgressUI::GetPaintPoint(vector<Gdiplus::Point>& vec, int angle /* = 0 */)
{
    RECT rcItem = m_rcItem;
    int iWidth = rcItem.right - rcItem.left;
    int iHeight = rcItem.bottom - rcItem.top;
    Gdiplus::Point ptCenter(rcItem.left + iWidth / 2, rcItem.top + iHeight / 2);

    if(angle == 0)
        angle = (int)360.0 * m_nValue / (m_nMax - m_nMin);

    int i = 0;
    for (; i <= angle; i++) // 外环每个圆上的点坐标
    {
        Gdiplus::Point pt;
        pt.X = ptCenter.X + m_nRadius * cos((i - 90 + m_nAngle) * 3.141592 / 180);
        pt.Y = ptCenter.Y + m_nRadius * sin((i - 90 + m_nAngle) * 3.141592 / 180);
        vec.push_back(pt);
    }

    if (m_nInnerRadius == 0)
    {
        vec.push_back(ptCenter);
        return;
    }

    int nInner = m_nRadius - m_nInnerRadius;

    for (; i >= 0; i--) // 内环每个圆上的点坐标
    {
        Gdiplus::Point pt;
        pt.X = ptCenter.X + nInner * cos((i - 90 + m_nAngle) * 3.141592 / 180);
        pt.Y = ptCenter.Y + nInner * sin((i - 90 + m_nAngle) * 3.141592 / 180);
        vec.push_back(pt);
    }
}

void CCirecleProgressUI::DeleteBkImage()
{
    if (m_pBkImage != nullptr)
    {
        delete m_pBkImage;
        m_pBkImage = nullptr;
    }
}

void CCirecleProgressUI::DeleteForeImage()
{
    if (m_pForeImage != nullptr)
    {
        delete m_pForeImage;
        m_pForeImage = nullptr;
    }
}

Gdiplus::Image* CCirecleProgressUI::GdiplusLoadImage(LPCTSTR pstrPath)
{
    LPBYTE pData = NULL;
    DWORD dwSize = 0;

    do
    {
        CDuiString sFile = CPaintManagerUI::GetResourcePath();
        if (CPaintManagerUI::GetResourceZip().IsEmpty()) {
            sFile += pstrPath;
            HANDLE hFile = ::CreateFile(sFile.GetData(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, \
                FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE) break;
            dwSize = ::GetFileSize(hFile, NULL);
            if (dwSize == 0) break;

            DWORD dwRead = 0;
            pData = new BYTE[dwSize];
            ::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
            ::CloseHandle(hFile);

            if (dwRead != dwSize) {
                delete[] pData;
                pData = NULL;
                break;
            }
        }

    } while (0);

    while (!pData)
    {
        //读不到图片, 则直接去读取bitmap.m_lpstr指向的路径
        HANDLE hFile = ::CreateFile(pstrPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) break;
        dwSize = ::GetFileSize(hFile, NULL);
        if (dwSize == 0) break;

        DWORD dwRead = 0;
        pData = new BYTE[dwSize];
        ::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
        ::CloseHandle(hFile);

        if (dwRead != dwSize) {
            delete[] pData;
            pData = NULL;
        }
        break;
    }

    Gdiplus::Image* pImage = NULL;
    if (pData != NULL) {
        HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
        BYTE* pMem = (BYTE*)::GlobalLock(hMem);
        memcpy(pMem, pData, dwSize);
        IStream* pStm = NULL;
        ::CreateStreamOnHGlobal(hMem, TRUE, &pStm);
        pImage = Gdiplus::Image::FromStream(pStm);
        if (!pImage || pImage->GetLastStatus() != Gdiplus::Ok)
        {
            pStm->Release();
            ::GlobalUnlock(hMem);
            return 0;
        }
        delete[] pData;
        pData = NULL;
    }
    return pImage;
}