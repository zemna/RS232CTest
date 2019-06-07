// RS232CTestDlg.h : header file
//

#if !defined(AFX_RS232CTESTDLG_H__CA42F6D8_FE18_43D8_AA2A_C850661DD1A3__INCLUDED_)
#define AFX_RS232CTESTDLG_H__CA42F6D8_FE18_43D8_AA2A_C850661DD1A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Include/Comm.h"
#include "SettingDlg.h"
#include "ColorSelectDlg.h"
#include "XListBox.h"
#include "ColorPickerButton.h"
#include "../Include/HighTimer.h"

/////////////////////////////////////////////////////////////////////////////
// CRS232CTestDlg dialog

class CRS232CTestDlg : public CDialog
{
// Construction
public:
	CRS232CTestDlg(CWnd* pParent = NULL);	// standard constructor

// public 함수
	void SaveConfig();
	void LoadConfig();

// Dialog Data
	//{{AFX_DATA(CRS232CTestDlg)
	enum { IDD = IDD_RS232CTEST_DIALOG };
	CButton				m_ctrlChkReceive;
	CColorPickerButton	m_ctrlRecvColorBtn;
	CColorPickerButton	m_ctrlSendColorBtn;
	CButton				m_ctrlButtonSave;
	CButton				m_ctrlButtonReconnect;
	CButton				m_ctrlButtonClear;
	CEdit				m_ctrlEdtEtx;
	CEdit				m_ctrlEdtStx;
	CEdit				m_ctrlEdtRept;
	CEdit				m_ctrlEdtData;
	CButton				m_ctrlBtnSend;
	CButton				m_ctrlChkRept;
	CXListBox			m_ctrlListShow;
	CComm				m_Comm;
	int					m_nReptTime;
	CString				m_strData;
	CString				m_strStx;
	CString				m_strEtx;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRS232CTestDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRS232CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonReconnect();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonSave();
	afx_msg void OnClose();
	afx_msg void OnCheckRepeat();
	afx_msg void OnDestroy();
	afx_msg void OnButtonSendColor();
	afx_msg void OnButtonRecvColor();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnReceive_Comm(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	CSettingDlg			*m_settingDlg;				// 셋팅 Dialog 포인터 변수
	CColorSelectDlg		*m_colorSelectDlg;			// Color Select Dialog 포인터 변수

	CHighTimer myTimer;

	UINT	m_nPort;								// 포트 번호
	UINT	m_nBaudRate;							// Baud Rate
	UINT	m_nParity;								// Parity Bit
	UINT	m_nStopbit;								// Stop Bit
	UINT	m_nDatabit;								// Data Bit
	UINT	m_nMode;								// Receive Mode
	UINT	m_nLimitTime;							// Time Limit
	UINT	m_nLimitCnt;							// Count Limit
	CString m_strEndCode;							// End Code

	int		m_nSndText;								//보내는 데이터 색상
	int		m_nSndBck;								//보내는 데이터 배경 색상
	int		m_nRecvText;							//받은 데이터 색상
	int		m_nRecvBck;								//받은 데이터 배경 색상

	CString ConvASCii2HexString(const unsigned char* pszSource, DWORD& nLength);	// ASCii 값을 Hexa 값으로 변환하는 함수
	CString ConvASCii(const unsigned char* pszSource, DWORD& nLength);

	static void TimerThread(LPVOID lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RS232CTESTDLG_H__CA42F6D8_FE18_43D8_AA2A_C850661DD1A3__INCLUDED_)
