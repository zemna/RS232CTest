// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RS232CTest.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_nMode = 0;
	m_strEndCode = _T("5");
	m_nLimitCnt = 30;
	m_nLimitTime = 30;
	//}}AFX_DATA_INIT
	m_nPort = 0;
	m_nBaudRate = 8;
	m_nParity = 0;
	m_nStopbit = 0;
	m_nDatabit = 3;
	m_nMode = 0;
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Control(pDX, IDC_EDIT_COUNT, m_ctrlEtxCnt);
	DDX_Control(pDX, IDC_EDIT_ETX, m_ctrlEdtEtx);
	DDX_Control(pDX, IDC_EDIT_LIMIT, m_ctrlEdtTime);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, m_comboStopbit);
	DDX_Control(pDX, IDC_COMBO_PORT, m_comboPort);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_comboParity);
	DDX_Control(pDX, IDC_COMBO_FLOW, m_comboFlow);
	DDX_Control(pDX, IDC_COMBO_DATABIT, m_comboDatabit);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_comboBaud);
	DDX_Radio(pDX, IDC_RADIO_ETX, m_nMode);
	DDX_Text(pDX, IDC_EDIT_ETX, m_strEndCode);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_nLimitCnt);
	DDX_Text(pDX, IDC_EDIT_LIMIT, m_nLimitTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_BN_CLICKED(IDC_RADIO_ETX, OnRadioMode)
	ON_BN_CLICKED(IDC_RADIO_TIME, OnRadioMode)
	ON_BN_CLICKED(IDC_RADIO_COUNT, OnRadioMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

BOOL CSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comboPort.SetCurSel(m_nPort);
	m_comboBaud.SetCurSel(m_nBaudRate);
	m_comboParity.SetCurSel(m_nParity);
	m_comboDatabit.SetCurSel(m_nDatabit);
	m_comboStopbit.SetCurSel(m_nStopbit);
	m_comboFlow.SetCurSel(0);

	UpdateData(FALSE);

	OnRadioMode();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg::OnOK()
{
	// TODO: Add extra validation here
	UpdateData();

	m_nPort		= m_comboPort.GetCurSel();			// Com Port
	m_nBaudRate = m_comboBaud.GetCurSel();			// BaudRate
	m_nParity	= m_comboParity.GetCurSel();		// Parity
	m_nStopbit	= m_comboStopbit.GetCurSel();		// Stop Bit
	m_nDatabit	= m_comboDatabit.GetCurSel();		// Data Bit

	CDialog::OnOK();
}

void CSettingDlg::SetData(UINT nPort, UINT nBaudRate, UINT nParity, UINT nStopBit, UINT nDataBit, UINT nMode, UINT nLimitTime, UINT nLimitCnt, CString strEndCode)
{
	m_nPort = nPort;
	m_nBaudRate = nBaudRate;
	m_nParity = nParity;
	m_nStopbit = nStopBit;
	m_nDatabit = nDataBit;
	m_nMode = nMode;
	m_nLimitTime = nLimitTime;
	m_nLimitCnt = nLimitCnt;
	m_strEndCode = strEndCode;
}

void CSettingDlg::GetData(UINT *nPort, UINT *nBaudRate, UINT *nParity, UINT *nStopBit, UINT *nDataBit, UINT *nMode, UINT *nLimitTime, UINT *nLimitCnt, CString *strEndCode)
{
	*nPort = m_nPort;
	*nBaudRate = m_nBaudRate;
	*nParity = m_nParity;
	*nStopBit = m_nStopbit;
	*nDataBit = m_nDatabit;
	*nMode = m_nMode;
	*nLimitTime = m_nLimitTime;
	*nLimitCnt = m_nLimitCnt;
	*strEndCode = m_strEndCode;
}

void CSettingDlg::OnRadioMode() 
{

	UpdateData();

	switch(m_nMode)	{
	case 0:
		m_ctrlEdtEtx.EnableWindow(TRUE);
		m_ctrlEdtTime.EnableWindow(FALSE);
		m_ctrlEtxCnt.EnableWindow(FALSE);
		break;
	case 1:
		m_ctrlEdtEtx.EnableWindow(FALSE);
		m_ctrlEdtTime.EnableWindow(TRUE);
		m_ctrlEtxCnt.EnableWindow(FALSE);
		break;
	case 2:
		m_ctrlEdtEtx.EnableWindow(FALSE);
		m_ctrlEdtTime.EnableWindow(FALSE);
		m_ctrlEtxCnt.EnableWindow(TRUE);
		break;
	}
}
