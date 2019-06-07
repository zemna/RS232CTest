// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "rs232ctest.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic

CMyStatic::CMyStatic()
{
	m_crBackColor = RGB(255,255,255);
	m_crTextColor = RGB(0,0,0);
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers

void CMyStatic::SetTextColor(COLORREF color)
{
	m_crTextColor = color;
}

void CMyStatic::SetBackColor(COLORREF color)
{
	m_crBackColor = color;
}

void CMyStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);

	CBrush brush;
	brush.CreateSolidBrush(m_crBackColor);
	CBrush* pOldBrush;

	pOldBrush = dc.SelectObject(&brush);

	dc.Rectangle(&rect);

	dc.SelectObject(pOldBrush);

	brush.DeleteObject();
	pOldBrush->DeleteObject();

	CFont font;
	CFont* pOldFont;
	font.CreateFont(20,10,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,NULL);

	pOldFont = dc.SelectObject(&font);
	dc.SetTextColor(m_crTextColor);

	dc.SetBkMode(TRANSPARENT);

	dc.DrawText("A",&rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);

	dc.SelectObject(pOldFont);

	font.DeleteObject();
	pOldFont->DeleteObject();

	// Do not call CStatic::OnPaint() for painting messages
}
