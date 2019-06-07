// MyColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "rs232ctest.h"
#include "MyColorButton.h"

#include "ColorSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyColorButton
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

CMyColorButton::CMyColorButton()
{
	m_nColor = 1;
}

CMyColorButton::~CMyColorButton()
{
}


BEGIN_MESSAGE_MAP(CMyColorButton, CButton)
	//{{AFX_MSG_MAP(CMyColorButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyColorButton message handlers

void CMyColorButton::SetColor(Color color)
{
	m_nColor = color;
}

void CMyColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;

	CBrush brush;
	brush.CreateSolidBrush(ColorTable[m_nColor]);
	CBrush* pOldBrush;

	CPen pen;
	CPen* pOldPen;

	if(state & ODS_SELECTED)
		pen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	else
		pen.CreatePen(PS_SOLID,1,RGB(0,0,0));

	pOldBrush = pDC->SelectObject(&brush);
	pOldPen = pDC->SelectObject(&pen);

	pDC->Rectangle(&rect);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	brush.DeleteObject();
	pOldBrush->DeleteObject();

	pen.DeleteObject();
	pOldPen->DeleteObject();
}

void CMyColorButton::PreSubclassWindow() 
{
	ModifyStyle(SS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);
	
	CButton::PreSubclassWindow();
}

void CMyColorButton::OnClicked() 
{	
	((CColorSelectDlg*)m_pDialog)->OnChangeColor(m_nGroup,m_nIndex);
}

void CMyColorButton::SetParent(CDialog *pDialog)
{
	m_pDialog = pDialog;
}
