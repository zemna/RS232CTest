// ColorPickerButton.cpp : implementation file
//

#include "stdafx.h"
#include "rs232ctest.h"
#include "ColorPickerButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorPickerButton
static COLORREF ColorTable[16] = { RGB(  0,   0,   0),		// Black
								   RGB(255, 255, 255),		// White
								   RGB(128,   0,   0),		// Maroon
								   RGB(  0, 128,   0),		// Green
								   RGB(128, 128,   0),		// Olive
								   RGB(  0,   0, 128),		// Navy
								   RGB(128,   0, 128),		// Purple
								   RGB(  0, 128, 128),		// Teal
								   RGB(192, 192, 192),		// Silver
								   RGB(128, 128, 128),		// Gray
								   RGB(255,   0,   0),		// Red
								   RGB(  0, 255,   0),		// Lime
								   RGB(255, 255,   0),		// Yellow
								   RGB(  0,   0, 255),		// Blue
								   RGB(255,   0, 255),		// Fuschia
								   RGB(  0, 255, 255) };	// Aqua

CColorPickerButton::CColorPickerButton()
{
	m_crFore = Black;
	m_crBack = White;
}

CColorPickerButton::~CColorPickerButton()
{
}


BEGIN_MESSAGE_MAP(CColorPickerButton, CButton)
	//{{AFX_MSG_MAP(CColorPickerButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPickerButton message handlers

void CColorPickerButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;

	CBrush brush;
	CBrush* pOldBrush;
	brush.CreateSolidBrush(ColorTable[m_crBack]);

	pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(&rect);

	pDC->SelectObject(pOldBrush);

	pDC->SetTextColor(ColorTable[m_crFore]);
	pDC->SetBkMode(TRANSPARENT);

	pDC->DrawText("A",&rect,DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	brush.DeleteObject();
	pOldBrush->DeleteObject();
	
}

void CColorPickerButton::SetForeColor(Color color)
{
	m_crFore = color;
}

void CColorPickerButton::SetBackColor(Color color)
{
	m_crBack = color;
}
