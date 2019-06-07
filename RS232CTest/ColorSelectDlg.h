#if !defined(AFX_COLORSELECTDLG_H__F45DE9C5_5354_4677_8F44_AD315D12E75F__INCLUDED_)
#define AFX_COLORSELECTDLG_H__F45DE9C5_5354_4677_8F44_AD315D12E75F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorSelectDlg.h : header file
//
#include "MyColorButton.h"
#include "MyStatic.h"
/////////////////////////////////////////////////////////////////////////////
// CColorSelectDlg dialog

class CColorSelectDlg : public CDialog
{
// Construction
public:
	int m_nTextColor;
	int m_nBackColor;
	void SetColor(int nTextColor, int nBackColor);
	CColorSelectDlg(CWnd* pParent = NULL);   // standard constructor
	void OnChangeColor(int group,int index);
	
	enum Color { Black,  White, Maroon,  Green,
				 Olive,  Navy,  Purple,  Teal,
				 Silver, Gray,  Red,     Lime,
				 Yellow, Blue,  Fuschia, Aqua };

// Dialog Data
	//{{AFX_DATA(CColorSelectDlg)
	enum { IDD = IDD_DIALOG_COLOR };
	CMyStatic	m_ctrlStaticDemo;
	CMyColorButton m_ctrlTextColorButton[15];
	CMyColorButton m_ctrlBackColorButton[15];
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorSelectDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSELECTDLG_H__F45DE9C5_5354_4677_8F44_AD315D12E75F__INCLUDED_)
