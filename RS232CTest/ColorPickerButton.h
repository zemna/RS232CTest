#if !defined(AFX_COLORPICKERBUTTON_H__453F8642_D7DF_408B_B16C_44DD7BCA98F1__INCLUDED_)
#define AFX_COLORPICKERBUTTON_H__453F8642_D7DF_408B_B16C_44DD7BCA98F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorPickerButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorPickerButton window

class CColorPickerButton : public CButton
{
// Construction
public:
	CColorPickerButton();

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
	//{{AFX_VIRTUAL(CColorPickerButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBackColor(Color color);
	void SetForeColor(Color color);
	virtual ~CColorPickerButton();

	// Generated message map functions
protected:
	int m_crBack;
	int m_crFore;
	//{{AFX_MSG(CColorPickerButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPICKERBUTTON_H__453F8642_D7DF_408B_B16C_44DD7BCA98F1__INCLUDED_)
