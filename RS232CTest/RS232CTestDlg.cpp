// RS232CTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RS232CTest.h"
#include "RS232CTestDlg.h"

#pragma comment(lib,"../Lib/CHighTimer.lib")
#pragma comment(lib,"../Lib/CComm.lib")

#include <malloc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRS232CTestDlg dialog

CRS232CTestDlg::CRS232CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRS232CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRS232CTestDlg)
	m_nReptTime = 1000;
	m_strData = _T("");
	m_strStx = _T("");
	m_strEtx = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nPort = 0;
	m_nBaudRate = 8;
	m_nDatabit = 3;
	m_nLimitCnt = 30;
	m_nLimitTime = 30;
	m_nMode = 0;
	m_nParity = 0;
	m_nStopbit = 0;
	m_strEndCode = _T("5");

	// List Box
	/*
	enum Color { Black, White,	Maroon,	Green,	Olive, 
				 Navy,	Purple, Teal,	Silver, Gray,
				 Red,   Lime,	Yellow,	Blue,	Fuschia, 
				 Aqua };*/
	m_nSndText = 3;
	m_nSndBck = 1;
	m_nRecvText = 13;
	m_nRecvBck = 1;

}

void CRS232CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRS232CTestDlg)
	DDX_Control(pDX, IDC_CHECK_HEXRECEIVE, m_ctrlChkReceive);
	DDX_Control(pDX, IDC_BUTTON_RECV_COLOR, m_ctrlRecvColorBtn);
	DDX_Control(pDX, IDC_BUTTON_SEND_COLOR, m_ctrlSendColorBtn);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_ctrlButtonSave);
	DDX_Control(pDX, IDC_BUTTON_RECONNECT, m_ctrlButtonReconnect);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_ctrlButtonClear);
	DDX_Control(pDX, IDC_EDITENDCODE, m_ctrlEdtEtx);
	DDX_Control(pDX, IDC_EDIT_STARTCODE, m_ctrlEdtStx);
	DDX_Control(pDX, IDC_EDIT_REPEAT, m_ctrlEdtRept);
	DDX_Control(pDX, IDC_EDIT_DATA, m_ctrlEdtData);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_ctrlBtnSend);
	DDX_Control(pDX, IDC_CHECK_REPEAT, m_ctrlChkRept);
	DDX_Control(pDX, IDC_LIST_SHOW, m_ctrlListShow);
	DDX_Text(pDX, IDC_EDIT_REPEAT, m_nReptTime);
	DDX_Text(pDX, IDC_EDIT_DATA, m_strData);
	DDX_Text(pDX, IDC_EDIT_STARTCODE, m_strStx);
	DDX_Text(pDX, IDC_EDITENDCODE, m_strEtx);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRS232CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CRS232CTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RECONNECT, OnButtonReconnect)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_REPEAT, OnCheckRepeat)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SEND_COLOR, OnButtonSendColor)
	ON_BN_CLICKED(IDC_BUTTON_RECV_COLOR, OnButtonRecvColor)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECEIVE_COMM,OnReceive_Comm)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRS232CTestDlg message handlers

BOOL CRS232CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// Serial Port Setting
	LoadConfig();

	OnButtonReconnect();

	CRect rc;
	GetClientRect(rc);

	SendMessage(WM_SIZE,SIZE_RESTORED,MAKELPARAM(rc.Width(), rc.Height()));

	m_ctrlListShow.SetContextMenuId(IDR_XLISTBOX);

	m_ctrlEdtData.SetFocus();
	m_ctrlEdtData.SetSel(0,m_strData.GetLength());

	UpdateData(FALSE);

	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRS232CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRS232CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRS232CTestDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (myTimer.IsTimerStarted())
		myTimer.EndTimer();

	CDialog::OnClose();
}

//프로그램 종료시
void CRS232CTestDlg::OnDestroy() 
{
	UpdateData();
	
	//레지스트리에 값 저장
	AfxGetApp()->WriteProfileInt("Settings","ASCii Receive Mode",(int)m_ctrlChkReceive.GetCheck());
	AfxGetApp()->WriteProfileInt("Settings","Repeat Interval",m_nReptTime);

	SaveConfig();

	CDialog::OnDestroy();	
}

void CRS232CTestDlg::OnButtonReconnect() 
{
	unsigned char chPortName[10] = {0x00};
	BOOL bResult;

	UINT nBaudRate;
	UINT nParity;
	UINT nStopBit;
	UINT nDataBit;
	unsigned char *pEndCode = NULL;

	m_settingDlg = new CSettingDlg;

	m_settingDlg->SetData(m_nPort,m_nBaudRate,m_nParity,m_nStopbit,m_nDatabit,m_nMode,m_nLimitTime,m_nLimitCnt,m_strEndCode);

	if(m_settingDlg->DoModal() == IDOK)
	{
		m_settingDlg->GetData(&m_nPort,&m_nBaudRate,&m_nParity,&m_nStopbit,&m_nDatabit,&m_nMode,&m_nLimitTime,&m_nLimitCnt,&m_strEndCode);
		m_Comm.ClosePort();

		sprintf((char*)chPortName,"\\\\.\\COM%d",m_nPort+1);

		switch(m_nBaudRate) {
		case 0: nBaudRate = CBR_110 ; break;
		case 1:	nBaudRate = CBR_300 ; break;
		case 2: nBaudRate = CBR_600 ; break;
		case 3: nBaudRate = CBR_1200 ; break;
		case 4: nBaudRate = CBR_2400 ; break;
		case 5: nBaudRate = CBR_4800 ; break;
		case 6: nBaudRate = CBR_9600 ; break;
		case 7: nBaudRate = CBR_14400 ; break;
		case 8: nBaudRate = CBR_19200 ; break;
		case 9: nBaudRate = CBR_38400 ; break;
		case 10: nBaudRate = CBR_56000 ; break;
		case 11: nBaudRate = CBR_57600 ; break;
		case 12: nBaudRate = CBR_115200 ; break;
		case 13: nBaudRate = CBR_128000 ; break;
		case 14: nBaudRate = CBR_256000 ; break;
		}

		switch(m_nParity) {
		case 0: nParity = NOPARITY ; break;
		case 1: nParity = ODDPARITY ; break;
		case 2: nParity = EVENPARITY ; break;
		case 3: nParity = MARKPARITY ; break;
		case 4: nParity = SPACEPARITY ; break;
		}

		switch(m_nStopbit) {
		case 0:	nStopBit = ONESTOPBIT; break;
		case 1: nStopBit = ONE5STOPBITS; break;
		case 2: nStopBit = TWOSTOPBITS; break;
		}

		switch(m_nDatabit) {
		case 0: nDataBit = 5; break;
		case 1: nDataBit = 6; break;
		case 2: nDataBit = 7; break;
		case 3: nDataBit = 8; break;
		}

		switch(m_nMode) {
		case 0:		// End Code
			pEndCode = (PUCHAR)malloc(m_strEndCode.GetLength());
			memset(pEndCode, 0x00 ,m_strEndCode.GetLength());
			memcpy(pEndCode, m_strEndCode, m_strEndCode.GetLength());
			bResult = m_Comm.OpenPort(this, (LPCSTR)chPortName, nBaudRate, nParity, nDataBit, nStopBit,m_nMode,(LPVOID)pEndCode, m_strEndCode.GetLength());
			break;
		case 1:		// Time Limit
			bResult = m_Comm.OpenPort(this, (LPCSTR)chPortName, nBaudRate, nParity, nDataBit, nStopBit,m_nMode,(LPVOID)&m_nLimitTime, 0);
			break;
		case 2:		// Count Limit
			bResult = m_Comm.OpenPort(this, (LPCSTR)chPortName, nBaudRate, nParity, nDataBit, nStopBit,m_nMode,(LPVOID)&m_nLimitCnt, 0);
			break;
		}

		if(!bResult){
			delete m_settingDlg;
			OnButtonReconnect();
			return;
		}
	}

	if (pEndCode) {
		free(pEndCode);
		pEndCode = NULL;
	}
	delete m_settingDlg;
	CString temp;
	temp.Format("RC232C Test Program - Port : COM%d",m_nPort+1);
	this->SetWindowText(temp);
}

void CRS232CTestDlg::OnButtonSend() 
{
	unsigned char *chSendData;			//보내려는 데이터를 저장할 문자열 포인터 변수
	unsigned char *chSentData;			//보내진 데이터를 저장할 문자열 포인터 변수
	CString strConvData;				//Hex 모드시 변환된 데이터를 저장할 변수
	DWORD	dwResult;					//SendData 함수의 반환값
	DWORD	dwToWrite = 0;

	UpdateData(TRUE);

	if(m_strData.IsEmpty())				//Data가 비었는지 확인
	{
		AfxMessageBox("Please input data");
		m_ctrlEdtData.SetFocus();
		return;
	}

	dwToWrite = strlen(m_strStx) + strlen(m_strData) + strlen(m_strEtx);
	chSendData = new UCHAR[dwToWrite];			//메모리 크기 선언
	memset(chSendData, 0x00, dwToWrite);		//메모리 초기화
	if ( m_strStx.GetLength() > 0 )
		memcpy(chSendData, m_strStx, m_strStx.GetLength());

	memcpy(chSendData+m_strStx.GetLength(), m_strData, m_strData.GetLength());

	if ( m_strEtx.GetLength() > 0)
		memcpy(chSendData+m_strStx.GetLength()+m_strData.GetLength(), m_strEtx, m_strEtx.GetLength());

	chSentData = new UCHAR[dwToWrite];
	memset(chSentData, 0x00, dwToWrite);

	dwResult = m_Comm.SendData(chSendData, dwToWrite, chSentData, dwToWrite);			// in : chSendData , out : chSentData

	if (!dwResult) {

		AfxMessageBox("Error occured while send data.");

	} else {

		if(!m_ctrlChkReceive.GetCheck())
			strConvData.Format("Sending  Data [H E X] : %s",ConvASCii2HexString(chSentData,dwResult));
		else
			strConvData.Format("Sending  Data [ASCii] : %s",ConvASCii(chSentData,dwResult));

		m_ctrlListShow.SetRedraw(FALSE);
		m_ctrlListShow.AddLine((CXListBox::Color)m_nSndText,(CXListBox::Color)m_nSndBck, strConvData);
		m_ctrlListShow.SetRedraw(TRUE);

	}

	delete chSendData;
	delete chSentData;

	m_ctrlEdtData.SetFocus();
	m_ctrlEdtData.SetSel(0,m_strData.GetLength());
}

//Clear버튼 클릭시...
void CRS232CTestDlg::OnButtonClear()
{
	m_ctrlListShow.ResetContent();
}

//Save버튼 클릭시...
void CRS232CTestDlg::OnButtonSave()
{
	CFileDialog fDlg(FALSE, "txt", "*.txt", OFN_OVERWRITEPROMPT, "TEXT Files (*.txt)|*.txt|");

	CString strFilePath;
	if(fDlg.DoModal() == IDOK)
	{
		// FilePath 얻기
		strFilePath = fDlg.GetPathName();
		CFile file;
		file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite);

		// Parameter Save
		for(int i=0; i<m_ctrlListShow.GetCount(); i++)
		{
			CString str;
			m_ctrlListShow.GetText(i, str);
			str += "\n";
			file.Write(str, str.GetLength());
		}
		file.Close();
		MessageBox(strFilePath + "\nFile Save Completed");
	}
}

//Repeat모드 버튼 누를때 실행되는 함수...
void CRS232CTestDlg::OnCheckRepeat()
{
	if(m_ctrlChkRept.GetCheck())	// Repeat ON
	{
		m_ctrlBtnSend.EnableWindow(FALSE);
		m_ctrlEdtData.EnableWindow(FALSE);
		m_ctrlEdtRept.EnableWindow(FALSE);
		m_ctrlEdtStx.EnableWindow(FALSE);
		m_ctrlEdtEtx.EnableWindow(FALSE);
		m_ctrlChkRept.SetWindowText("Repeat &ON");
		OnButtonSend();
		UpdateData();
		myTimer.SetTimerInfo(this, m_nReptTime);
		myTimer.StartTimer(TimerThread);
	}
	else							// Repeat OFF
	{
		myTimer.EndTimer();
		m_ctrlChkRept.SetWindowText("Repeat &OFF");
		m_ctrlBtnSend.EnableWindow(TRUE);
		m_ctrlEdtData.EnableWindow(TRUE);
		m_ctrlEdtRept.EnableWindow(TRUE);
		m_ctrlEdtStx.EnableWindow(TRUE);
		m_ctrlEdtEtx.EnableWindow(TRUE);
	}
}

//시리얼포트에서 값을 Receive 받았을때...
void CRS232CTestDlg::OnReceive_Comm(WPARAM wParam, LPARAM lParam)
{
	CString strData;
	unsigned char chRecvData[1024] = {0x00};
	DWORD dwRet;

	dwRet = m_Comm.GetRecvData(chRecvData, 1024);

	if(m_ctrlChkReceive.GetCheck()) {		//ASCii Receive 모드가 체크 되어있을경우
		strData.Format("Received Data [ASCii] : %s",chRecvData);
	} else {
		strData.Format("Received Data [H E X] : %s",ConvASCii2HexString(chRecvData, dwRet));
	}

	m_ctrlListShow.AddLine((CXListBox::Color)m_nRecvText,(CXListBox::Color)m_nRecvBck, strData);
}

// ASCii 문자를 Hexa 코드로 변환
CString CRS232CTestDlg::ConvASCii2HexString(const unsigned char* pszSource, DWORD& nLength)
{
	UINT i;
	CString strResult;
	CString strTemp;

	for(i=0; i<nLength; i++) {
		strTemp.Format("0x%02x ",pszSource[i]);
		strResult += strTemp;
	}

	return strResult;
}

CString CRS232CTestDlg::ConvASCii(const unsigned char* pszSource, DWORD& nLength)
{
	UINT i;
	CString strResult;
	CString strTemp;

	for(i=0; i<nLength; i++) {
		if (pszSource[i] == 0x00)
			strTemp = " ";
		else
			strTemp.Format("%c", pszSource[i]);
		strResult += strTemp;
	}

	return strResult;
}

//키보드 단축키처리...
BOOL CRS232CTestDlg::PreTranslateMessage(MSG* pMsg) 
{
	CString temp;

	if(pMsg->message==WM_SYSKEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case 'D':
			m_ctrlEdtData.SetFocus();
			m_ctrlEdtData.SetSel(0,m_strData.GetLength());
			return TRUE;
			break;
		case 'S':
			temp.Format("%d",m_strStx);
			m_ctrlEdtStx.SetFocus();
			m_ctrlEdtStx.SetSel(0,temp.GetLength());
			return TRUE;
			break;
		case 'E':
			temp.Format("%d",m_strEtx);
			m_ctrlEdtEtx.SetFocus();
			m_ctrlEdtEtx.SetSel(0,temp.GetLength());
			return TRUE;
			break;
		}
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}

//Send Color Button을 눌렀을 경우
void CRS232CTestDlg::OnButtonSendColor() 
{
	m_colorSelectDlg = new CColorSelectDlg;
	m_colorSelectDlg->SetColor(m_nSndText,m_nSndBck);

	if(m_colorSelectDlg->DoModal() == IDOK)
	{
		m_nSndText = m_colorSelectDlg->m_nTextColor;
		m_nSndBck = m_colorSelectDlg->m_nBackColor;
		m_ctrlSendColorBtn.SetForeColor((CColorPickerButton::Color)m_nSndText);
		m_ctrlSendColorBtn.SetBackColor((CColorPickerButton::Color)m_nSndBck);

		Invalidate();
	}
}

//Receive Color Button을 눌렀을 경우
void CRS232CTestDlg::OnButtonRecvColor() 
{
	m_colorSelectDlg = new CColorSelectDlg;
	m_colorSelectDlg->SetColor(m_nRecvText,m_nRecvBck);

	if(m_colorSelectDlg->DoModal() == IDOK)
	{
		m_nRecvText = m_colorSelectDlg->m_nTextColor;
		m_nRecvBck = m_colorSelectDlg->m_nBackColor;
		m_ctrlRecvColorBtn.SetForeColor((CColorPickerButton::Color)m_nRecvText);
		m_ctrlRecvColorBtn.SetBackColor((CColorPickerButton::Color)m_nRecvBck);
		Invalidate();
	}
}

void CRS232CTestDlg::LoadConfig()
{
	CFile file;
	if(file.Open("config.cfg",CFile::modeRead))
	{
		CArchive archive(&file,CArchive::load);

		archive >> m_nPort >> m_nBaudRate >> m_nParity >> m_nStopbit >> m_nDatabit >> m_nMode >> m_nLimitTime >> m_nLimitCnt >> m_strEndCode;
		archive >> m_nSndText >> m_nSndBck >> m_nRecvText >> m_nRecvBck;
		archive >> m_strStx >> m_strData >> m_strEtx;
		archive >> m_nReptTime;

		archive.Close();

		file.Close();
	}

	UpdateData(FALSE);
	Invalidate();

	m_ctrlSendColorBtn.SetForeColor((CColorPickerButton::Color)m_nSndText);
	m_ctrlSendColorBtn.SetBackColor((CColorPickerButton::Color)m_nSndBck);
	m_ctrlRecvColorBtn.SetForeColor((CColorPickerButton::Color)m_nRecvText);
	m_ctrlRecvColorBtn.SetBackColor((CColorPickerButton::Color)m_nRecvBck);

	//레지스트리에서 기존 작업환경 불러오기
	m_ctrlChkReceive.SetCheck(AfxGetApp()->GetProfileInt("Settings","ASCii Receive Mode",0));
	m_nReptTime = AfxGetApp()->GetProfileInt("Settings","Repeat Interval",1000);
}

void CRS232CTestDlg::SaveConfig()
{
	CFile file;
	if(file.Open("config.cfg",CFile::modeCreate | CFile::modeWrite))
	{
		CArchive archive(&file,CArchive::store);

		archive << m_nPort << m_nBaudRate << m_nParity << m_nStopbit << m_nDatabit << m_nMode << m_nLimitTime << m_nLimitCnt << m_strEndCode;
		archive << m_nSndText << m_nSndBck << m_nRecvText << m_nRecvBck;
		archive << m_strStx << m_strData << m_strEtx;
		archive << m_nReptTime;

		archive.Close();

		file.Close();
	}
}

void CRS232CTestDlg::TimerThread(LPVOID lParam)
{
	CRS232CTestDlg* pDlg = (CRS232CTestDlg*)lParam;
	pDlg->SendMessage(WM_COMMAND,MAKEWPARAM(IDC_BUTTON_SEND,BN_CLICKED),0);
}

void CRS232CTestDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (GetDlgItem(IDC_BUTTON_RECONNECT)->GetSafeHwnd())
		GetDlgItem(IDC_BUTTON_RECONNECT)->MoveWindow(10,5,100,25);

	if (GetDlgItem(IDC_BUTTON_SAVE)->GetSafeHwnd())
		GetDlgItem(IDC_BUTTON_SAVE)->MoveWindow(cx-260,5,120,25);

	if (GetDlgItem(IDC_BUTTON_CLEAR)->GetSafeHwnd())
		GetDlgItem(IDC_BUTTON_CLEAR)->MoveWindow(cx-130,5,120,25);

	if (GetDlgItem(IDC_CHECK_HEXRECEIVE)->GetSafeHwnd())
		GetDlgItem(IDC_CHECK_HEXRECEIVE)->MoveWindow(20,50,400,20);	

	if (GetDlgItem(IDC_LIST_SHOW)->GetSafeHwnd())
		GetDlgItem(IDC_LIST_SHOW)->MoveWindow(20,75,cx-40,cy-190);	

	if (GetDlgItem(IDC_STATIC_STX)->GetSafeHwnd())
		GetDlgItem(IDC_STATIC_STX)->MoveWindow(20,cy-80,(cx-40)/8,20);	

	if (GetDlgItem(IDC_STATIC_DATA)->GetSafeHwnd())
		GetDlgItem(IDC_STATIC_DATA)->MoveWindow(25+((cx-40)/8),cy-80,(cx-40)/8,20);	

	if (GetDlgItem(IDC_STATIC_ETX)->GetSafeHwnd())
		GetDlgItem(IDC_STATIC_ETX)->MoveWindow(cx-((cx-40)/8)-20,cy-80,(cx-40)/8,20);	

	if (GetDlgItem(IDC_EDIT_STARTCODE)->GetSafeHwnd())
		GetDlgItem(IDC_EDIT_STARTCODE)->MoveWindow(20,cy-60,(cx-40)/8,20);	

	if (GetDlgItem(IDC_EDIT_DATA)->GetSafeHwnd())
		GetDlgItem(IDC_EDIT_DATA)->MoveWindow(25+((cx-40)/8),cy-60,(((cx-40)/8)*6)-5,20);	

	if (GetDlgItem(IDC_EDIT_ENDCODE)->GetSafeHwnd())
		GetDlgItem(IDC_EDIT_ENDCODE)->MoveWindow(cx-((cx-40)/8)-20,cy-60,(cx-40)/8,20);	

	if (GetDlgItem(IDC_CHECK_REPEAT)->GetSafeHwnd())
		GetDlgItem(IDC_CHECK_REPEAT)->MoveWindow(cx-210,cy-35,90,25);	

	if (GetDlgItem(IDC_BUTTON_SEND)->GetSafeHwnd())
		GetDlgItem(IDC_BUTTON_SEND)->MoveWindow(cx-110,cy-35,90,25);	

	if (GetDlgItem(IDC_STATIC_REPEATPER)->GetSafeHwnd())
		GetDlgItem(IDC_STATIC_REPEATPER)->MoveWindow(cx-400,cy-35,70,25);	

	if (GetDlgItem(IDC_STATIC_MSEC)->GetSafeHwnd())
		GetDlgItem(IDC_STATIC_MSEC)->MoveWindow(cx-260,cy-35,40,25);	

	if (GetDlgItem(IDC_EDIT_REPEAT)->GetSafeHwnd())
		GetDlgItem(IDC_EDIT_REPEAT)->MoveWindow(cx-320,cy-35,50,25);	

	if (GetDlgItem(IDC_FRAME_DATA)->GetSafeHwnd() != NULL)
		GetDlgItem(IDC_FRAME_DATA)->MoveWindow(10,35,cx-20,cy-140);

	if (GetDlgItem(IDC_FRAME_SEND)->GetSafeHwnd() != NULL)
		GetDlgItem(IDC_FRAME_SEND)->MoveWindow(10, cy-100, cx-20, 95);
}
