// CHighTimerTest.h : main header file for the CHIGHTIMERTEST application
//

#if !defined(AFX_CHIGHTIMERTEST_H__4FB0D724_D0D4_48D2_9099_3C02C1CF7B38__INCLUDED_)
#define AFX_CHIGHTIMERTEST_H__4FB0D724_D0D4_48D2_9099_3C02C1CF7B38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCHighTimerTestApp:
// See CHighTimerTest.cpp for the implementation of this class
//

class CCHighTimerTestApp : public CWinApp
{
public:
	CCHighTimerTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHighTimerTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCHighTimerTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHIGHTIMERTEST_H__4FB0D724_D0D4_48D2_9099_3C02C1CF7B38__INCLUDED_)
