// ColorSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "rs232ctest.h"
#include "ColorSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorSelectDlg dialog
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

CColorSelectDlg::CColorSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorSelectDlg)
	m_nTextColor = 0;
	m_nBackColor = 0;
	//}}AFX_DATA_INIT

	//Create(CColorSelectDlg::IDD,pParent);
}


void CColorSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorSelectDlg)	
	DDX_Control(pDX, IDC_STATIC_DEMO, m_ctrlStaticDemo);
	DDX_Control(pDX, IDC_BUTTON1, m_ctrlTextColorButton[0]);
	DDX_Control(pDX, IDC_BUTTON2, m_ctrlTextColorButton[1]);
	DDX_Control(pDX, IDC_BUTTON3, m_ctrlTextColorButton[2]);
	DDX_Control(pDX, IDC_BUTTON4, m_ctrlTextColorButton[3]);
	DDX_Control(pDX, IDC_BUTTON5, m_ctrlTextColorButton[4]);
	DDX_Control(pDX, IDC_BUTTON6, m_ctrlTextColorButton[5]);
	DDX_Control(pDX, IDC_BUTTON7, m_ctrlTextColorButton[6]);
	DDX_Control(pDX, IDC_BUTTON8, m_ctrlTextColorButton[7]);
	DDX_Control(pDX, IDC_BUTTON9, m_ctrlTextColorButton[8]);
	DDX_Control(pDX, IDC_BUTTON10, m_ctrlTextColorButton[9]);
	DDX_Control(pDX, IDC_BUTTON11, m_ctrlTextColorButton[10]);
	DDX_Control(pDX, IDC_BUTTON12, m_ctrlTextColorButton[11]);
	DDX_Control(pDX, IDC_BUTTON13, m_ctrlTextColorButton[12]);
	DDX_Control(pDX, IDC_BUTTON14, m_ctrlTextColorButton[13]);
	DDX_Control(pDX, IDC_BUTTON15, m_ctrlTextColorButton[14]);
	DDX_Control(pDX, IDC_RADIO16, m_ctrlBackColorButton[0]);
	DDX_Control(pDX, IDC_RADIO17, m_ctrlBackColorButton[1]);
	DDX_Control(pDX, IDC_RADIO18, m_ctrlBackColorButton[2]);
	DDX_Control(pDX, IDC_RADIO19, m_ctrlBackColorButton[3]);
	DDX_Control(pDX, IDC_RADIO20, m_ctrlBackColorButton[4]);
	DDX_Control(pDX, IDC_RADIO21, m_ctrlBackColorButton[5]);
	DDX_Control(pDX, IDC_RADIO22, m_ctrlBackColorButton[6]);
	DDX_Control(pDX, IDC_RADIO23, m_ctrlBackColorButton[7]);
	DDX_Control(pDX, IDC_RADIO24, m_ctrlBackColorButton[8]);
	DDX_Control(pDX, IDC_RADIO25, m_ctrlBackColorButton[9]);
	DDX_Control(pDX, IDC_RADIO26, m_ctrlBackColorButton[10]);
	DDX_Control(pDX, IDC_RADIO27, m_ctrlBackColorButton[11]);
	DDX_Control(pDX, IDC_RADIO28, m_ctrlBackColorButton[12]);
	DDX_Control(pDX, IDC_RADIO29, m_ctrlBackColorButton[13]);
	DDX_Control(pDX, IDC_RADIO30, m_ctrlBackColorButton[14]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CColorSelectDlg)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorSelectDlg message handlers

void CColorSelectDlg::OnChangeColor(int group,int index) 
{
	if(group == 0){
		m_nTextColor = index;
		m_ctrlStaticDemo.SetTextColor(ColorTable[index]);
	} else {
		m_nBackColor = index;
		m_ctrlStaticDemo.SetBackColor(ColorTable[index]);
	}
	Invalidate();
}

void CColorSelectDlg::SetColor(int nTextColor, int nBackColor)
{
	m_nTextColor = nTextColor;
	m_nBackColor = nBackColor;
}

BOOL CColorSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for(int i=0;i<15;i++)
	{
		m_ctrlTextColorButton[i].SetParent(this);
		m_ctrlTextColorButton[i].SetColor((CMyColorButton::Color)i);
		m_ctrlTextColorButton[i].m_nIndex = i;
		m_ctrlTextColorButton[i].m_nGroup = 0;

		m_ctrlBackColorButton[i].SetParent(this);
		m_ctrlBackColorButton[i].SetColor((CMyColorButton::Color)i);
		m_ctrlBackColorButton[i].m_nIndex = i;
		m_ctrlBackColorButton[i].m_nGroup = 1;
	}

	m_ctrlStaticDemo.SetTextColor(ColorTable[m_nTextColor]);
	m_ctrlStaticDemo.SetBackColor(ColorTable[m_nBackColor]);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CColorSelectDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(232,232,232));
	}

	if(nCtlColor == CTLCOLOR_DLG)
		hbr = CreateSolidBrush(RGB(232,232,232));
	
	return hbr;
}

void CColorSelectDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CDialog::OnLButtonDown(nFlags, point);

	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x,point.y));
}
