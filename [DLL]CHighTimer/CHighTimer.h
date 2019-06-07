// CHighTimer.h : main header file for the CHIGHTIMER DLL
//

#if !defined(AFX_CHIGHTIMER_H__380F9CAB_4F3C_4A74_83DD_71CC90DBD56D__INCLUDED_)
#define AFX_CHIGHTIMER_H__380F9CAB_4F3C_4A74_83DD_71CC90DBD56D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCHighTimerApp
// See CHighTimer.cpp for the implementation of this class
//

class CCHighTimerApp : public CWinApp
{
public:
	CCHighTimerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHighTimerApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCHighTimerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHIGHTIMER_H__380F9CAB_4F3C_4A74_83DD_71CC90DBD56D__INCLUDED_)
