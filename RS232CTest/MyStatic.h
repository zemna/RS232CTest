#if !defined(AFX_MYSTATIC_H__B3F2BDCA_D2DB_4EBE_9049_B2BF910D2FC2__INCLUDED_)
#define AFX_MYSTATIC_H__B3F2BDCA_D2DB_4EBE_9049_B2BF910D2FC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CMyStatic : public CStatic
{
// Construction
public:
	CMyStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBackColor(COLORREF color);
	void SetTextColor(COLORREF color);
	COLORREF m_crBackColor;
	COLORREF m_crTextColor;
	virtual ~CMyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__B3F2BDCA_D2DB_4EBE_9049_B2BF910D2FC2__INCLUDED_)
