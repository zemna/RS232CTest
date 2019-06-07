// AscHexConv.h : main header file for the ASCHEXCONV DLL
//

#if !defined(AFX_ASCHEXCONV_H__BF334A2F_327A_41FF_9400_6D217AD7B4C3__INCLUDED_)
#define AFX_ASCHEXCONV_H__BF334A2F_327A_41FF_9400_6D217AD7B4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAscHexConvApp
// See AscHexConv.cpp for the implementation of this class
//

class CAscHexConvApp : public CWinApp
{
public:
	CAscHexConvApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAscHexConvApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAscHexConvApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASCHEXCONV_H__BF334A2F_327A_41FF_9400_6D217AD7B4C3__INCLUDED_)
