// CHighTimerTestDlg.h : header file
//

#if !defined(AFX_CHIGHTIMERTESTDLG_H__4B20627F_92CA_492E_912E_02E809EC3DF9__INCLUDED_)
#define AFX_CHIGHTIMERTESTDLG_H__4B20627F_92CA_492E_912E_02E809EC3DF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCHighTimerTestDlg dialog

#include "../Include/HighTimer.h"

class CCHighTimerTestDlg : public CDialog
{
// Construction
public:
	CCHighTimerTestDlg(CWnd* pParent = NULL);	// standard constructor

	CHighTimer m_highTimer;

	static void TimerProc();

// Dialog Data
	//{{AFX_DATA(CCHighTimerTestDlg)
	enum { IDD = IDD_CHIGHTIMERTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHighTimerTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCHighTimerTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHIGHTIMERTESTDLG_H__4B20627F_92CA_492E_912E_02E809EC3DF9__INCLUDED_)
