// CComm.h : main header file for the CCOMM DLL
//

#if !defined(AFX_CCOMM_H__938A2871_FC50_4FCF_BFB4_99D05240E327__INCLUDED_)
#define AFX_CCOMM_H__938A2871_FC50_4FCF_BFB4_99D05240E327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCCommApp
// See CComm.cpp for the implementation of this class
//

class CCCommApp : public CWinApp
{
public:
	CCCommApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCCommApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCCommApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCOMM_H__938A2871_FC50_4FCF_BFB4_99D05240E327__INCLUDED_)
