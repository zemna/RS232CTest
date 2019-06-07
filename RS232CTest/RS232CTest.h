// RS232CTest.h : main header file for the RS232CTEST application
//

#if !defined(AFX_RS232CTEST_H__174AF838_FE8C_4626_BBFB_8EB56AB65460__INCLUDED_)
#define AFX_RS232CTEST_H__174AF838_FE8C_4626_BBFB_8EB56AB65460__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRS232CTestApp:
// See RS232CTest.cpp for the implementation of this class
//

class CRS232CTestApp : public CWinApp
{
public:
	CRS232CTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRS232CTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRS232CTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RS232CTEST_H__174AF838_FE8C_4626_BBFB_8EB56AB65460__INCLUDED_)
