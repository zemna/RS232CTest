#if !defined(AFX_SETTINGDLG_H__A52CC534_36D6_4495_AA1E_C22C735AF5B8__INCLUDED_)
#define AFX_SETTINGDLG_H__A52CC534_36D6_4495_AA1E_C22C735AF5B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

class CSettingDlg : public CDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);

private:
	UINT	m_nPort;				// 포트 번호
	UINT	m_nBaudRate;			// Baud Rate
	UINT	m_nParity;				// Parity Bit
	UINT	m_nStopbit;				// Stop Bit
	UINT	m_nDatabit;				// Data Bit

public:
	void GetData(UINT* nPort, UINT* nBaudRate, UINT* nParity, UINT* nStopBit, UINT* nDataBit, UINT* nMode, UINT* nLimitTime, UINT* nLimitCnt, CString* strEndCode);
	void SetData(UINT nPort,UINT nBaudRate, UINT nParity, UINT nStopBit, UINT nDataBit, UINT nMode, UINT nLimitTime, UINT nLimitCnt, CString strEndCode);

	// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_DIALOG_SETTING };
	CEdit		m_ctrlEtxCnt;
	CEdit		m_ctrlEdtEtx;
	CEdit		m_ctrlEdtTime;
	CComboBox	m_comboStopbit;
	CComboBox	m_comboPort;
	CComboBox	m_comboParity;
	CComboBox	m_comboFlow;
	CComboBox	m_comboDatabit;
	CComboBox	m_comboBaud;
	int			m_nMode;
	CString		m_strEndCode;
	UINT		m_nLimitCnt;
	UINT		m_nLimitTime;
	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__A52CC534_36D6_4495_AA1E_C22C735AF5B8__INCLUDED_)
