#if !defined(AFX_MYCOLORBUTTON_H__946F6C4D_365D_42BF_BFF3_A5AB23A8ED19__INCLUDED_)
#define AFX_MYCOLORBUTTON_H__946F6C4D_365D_42BF_BFF3_A5AB23A8ED19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyColorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyColorButton window

class CMyColorButton : public CButton
{
// Construction
public:
	CMyColorButton();

// Attributes
public:
	enum Color { Black,  White, Maroon,  Green,
				 Olive,  Navy,  Purple,  Teal,
				 Silver, Gray,  Red,     Lime,
				 Yellow, Blue,  Fuschia, Aqua };
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyColorButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nGroup;
	CDialog* m_pDialog;
	void SetParent(CDialog* pDialog);
	int m_nColor;
	int m_nIndex;
	void SetColor(Color color);
	virtual ~CMyColorButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyColorButton)
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCOLORBUTTON_H__946F6C4D_365D_42BF_BFF3_A5AB23A8ED19__INCLUDED_)
