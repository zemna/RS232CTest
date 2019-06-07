// Comm.cpp: implementation of the CComm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#define CCOMMAPI_EXPORTS
#include "Comm.h"

//#include <malloc.h>

#pragma comment(lib,"../Lib/AscHexConv.lib")
#pragma comment(lib,"../Lib/CHighTimer.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////
// Constructor / Destructor
/////////////////////////////////////////////////////////////

// Constructor
CComm::CComm()
{
	m_nMode = COMM_RMODE_ENDCODE;			// 기본으로 End Code 방식으로 셋팅
	m_bRecvTimer = FALSE;	
	m_nDelay = 0;
	m_pOwner = NULL;
	m_pThread = NULL;
	m_hComm = NULL;
	m_bConnected = FALSE;
	m_nLimitTime = 30;
	m_nLimitCnt = 0;
	m_pszEndCode = NULL;
	m_pszData = NULL;
	m_pszTmpData = NULL;
	m_pszPortName = NULL;
	m_Asc2HexConv.SetHexChar('#',',');
	m_nLastErrNum = 0;
	m_bHasTransfered = TRUE;
	m_nEndCodeLen = 0;
	m_nDataLen = 0;
	m_nTmpDataLen = 0;
}

// Destructor
CComm::~CComm()
{
	ClosePort();

	SAFE_DELETE(m_pszPortName);
	SAFE_DELETE(m_pszEndCode);
	SAFE_DELETE(m_pszData);
	SAFE_DELETE(m_pszTmpData);

	m_pThread = NULL;
	m_pOwner = NULL;
}

/////////////////////////////////////////////////////////////
// Getter / Setter
/////////////////////////////////////////////////////////////

// 현재의 COM 포트의 핸들값 반환
HANDLE CComm::GetCommHandle()
{
	return m_hComm;
}

// 현재 COM 포트와 연결되었는지를 반환
BOOL CComm::IsConnected()
{
	return m_bConnected;
}

// 현재의 포트번호를 반환
void CComm::GetPortName(LPSTR pszPortName, UINT nBufLen)
{
	if (strlen(m_pszPortName) > nBufLen-1) {
		m_nLastErrNum = COMM_ERROR_BUFFER_OVERFLOW;
		return;
	}

	memset(pszPortName, 0x00, nBufLen);
	memcpy(pszPortName, m_pszPortName, strlen(m_pszPortName));
}

// 데이터 체크 타이머 실행여부를 반환
BOOL CComm::IsTimerEnabled()
{
	return m_bRecvTimer;
}

// 타이머의 Enable/Disable 여부를 설정
void CComm::SetTimerEnable(BOOL bEnable)
{
	m_bRecvTimer = bEnable;
}

// 현재 Delay된 시간을 반환
UINT CComm::GetCurrentDelayTime()
{
	return m_nDelay;
}

// 설정되어있는 Delay 한도를 반환
UINT CComm::GetLimitDelayTime()
{
	return m_nLimitTime;
}

// 현재 Delay 수치를 변환
void CComm::SetCurrentDelayTime(UINT nDelayTime)
{
	m_nDelay = nDelayTime;
}

// 소유자 윈도우의 포인터를 반환
CWnd* CComm::GetOwnerWnd()
{
	return m_pOwner;
}

// Receive 된 데이터를 반환
DWORD CComm::GetRecvData(PUCHAR pszData, UINT nBufLen)
{
	if (!m_pszData) {
		
		memset(pszData, 0x00, nBufLen);
		return 0;

	} else {

		if (m_nDataLen > nBufLen-1) {
			m_nLastErrNum = COMM_ERROR_BUFFER_OVERFLOW;
			return 0;
		}

		memset(pszData, 0x00, nBufLen);
		memcpy(pszData, m_pszData, m_nDataLen);

		SAFE_DELETE(m_pszData);

		m_bHasTransfered = TRUE;

		return m_nDataLen;

	}
}

// 현재의 모드를 반환
UINT CComm::GetMode()
{
	return m_nMode;
}

// Set Read Mode
BOOL CComm::SetMode(UINT nMode, LPVOID paramData, UINT nParamSize)
{
	PUCHAR pszParam;
	BYTE pBuff[80] = {0x00};
	UINT nByteWritten=0;

	if ((nMode < COMM_RMODE_ENDCODE) || (nMode > COMM_RMODE_COUNTLIMIT)) {
		m_nLastErrNum = COMM_ERROR_RMODE_INCORRECT;
		return FALSE;
	}

	m_nMode = nMode;

	switch(nMode) 
	{
	case COMM_RMODE_ENDCODE:							//End Code Mode
		pszParam = (PUCHAR)malloc(nParamSize);
		memset(pszParam, 0x00, nParamSize);
		memcpy(pszParam, paramData, nParamSize);

		m_Asc2HexConv.ConvAsc2Hex(pszParam, nParamSize, pBuff, 80, &nByteWritten);

		SAFE_DELETE(pszParam);
		SAFE_DELETE(m_pszEndCode);

		m_pszEndCode = (PUCHAR)malloc(nByteWritten);
		memset(m_pszEndCode, 0x00, nByteWritten);
		memcpy(m_pszEndCode, pBuff, nByteWritten);
		m_nEndCodeLen = nByteWritten;
		break;
	case COMM_RMODE_TIMELIMIT:							//Time Limit 방식일 경우
		m_nLimitTime = *((UINT*)paramData);
		break;
	case COMM_RMODE_COUNTLIMIT:							//Count Limit 방식일 경우
		m_nLimitCnt = *((UINT*)paramData);
		break;
	};

	return TRUE;
}

UINT CComm::GetLastCommError()
{
	return m_nLastErrNum;
}

/////////////////////////////////////////////////////////////
// Operations
/////////////////////////////////////////////////////////////

// 현재 Delay 수치를 1 증가시킴
void CComm::IncreaseCurrentDelay()
{
	m_nDelay++;
}

// 포트 열기
BOOL CComm::OpenPort(CWnd* pPortOwner, LPCSTR pszPortName, DWORD dwBaud, BYTE parity, BYTE bytesize, BYTE stopbit, UINT nMode, LPVOID paramData, UINT nParamSize)
{
	COMMTIMEOUTS	timeouts;
	DCB				PortDCB;
	PortDCB.DCBlength = sizeof(DCB);

	m_pOwner = pPortOwner;

	//Read OVERLAPPED 구조체 초기화
	memset(&m_osRead, 0x00, sizeof(m_osRead));
	if (!(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))		//완료시 발생할 이벤트 설정
	{
		TRACE1("Failed while init Read OVERLAPPED structure :%d\n",GetLastError());
		ASSERT(0);
		return FALSE;
	}
	TRACE0("Success Read OVERLAPPED structure\n");

	//Write OVERLAPPED 구조체 초기화
	memset(&m_osWrite, 0x00, sizeof(m_osWrite));
	if (!(m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))		//완료시 발생할 이벤트 설정
	{
		TRACE1("Error occured while init Write OVERLAPPED structure :%d\n",GetLastError());
		ASSERT(0);
		return FALSE;
	}
	TRACE0("Success Write OVERLAPPED structure\n");

	Sleep(50);

	// Save port name
	SAFE_DELETE(m_pszPortName);
	m_pszPortName = (LPSTR)malloc(strlen(pszPortName)+1);
	memset(m_pszPortName, 0x00, strlen(pszPortName)+1);
	memcpy(m_pszPortName, pszPortName, strlen(pszPortName));

	m_hComm = CreateFile(m_pszPortName,						//포트 이름
						 GENERIC_READ | GENERIC_WRITE,		//열기/쓰기 가능
						 0,									//무조건 0 (Share Mode)
						 NULL,								//무조건 NULL (SecurityAttributes)
						 OPEN_EXISTING,						//무조건 OPEN_EXISTING
						 FILE_FLAG_OVERLAPPED,				//OVERLAPPED 방식 설정
						 NULL);								//무조건 NULL

	if (m_hComm==INVALID_HANDLE_VALUE)
	{
		m_nLastErrNum = COMM_ERROR_OPENPORT;
		TRACE1("Error occured while open Port :%d\n",GetLastError());
		m_bConnected=FALSE;
		return FALSE;
	}
	TRACE1("Success Port open HANDLE:%d\n",m_hComm);

	if (!SetMode(nMode,paramData,nParamSize)) {						//Receive Mode Setting
		m_nLastErrNum = COMM_ERROR_RMODE_INCORRECT;
		TRACE("Error occured while setting Mode :%d\n",GetLastError());
		m_bConnected = FALSE;
		return FALSE;
	}
	TRACE0("Success SetMode function\n");
	
	//Set COM port Event Mask
	if (! ::SetCommMask( m_hComm, EV_RXCHAR)) {
		TRACE1("Failed SetCommMask function :%d\n",GetLastError());
		ASSERT(0);
		return FALSE;
	}
	TRACE0("SetCommMask Success\n");

	// InQueue, OutQueue 크기 설정
	if(! ::SetupComm( m_hComm, 100000, 100000)) {
		TRACE1("Failed SetComm Function :%d\n",GetLastError());
		ASSERT(0);
		return FALSE;
	}
	TRACE0("SetComm Success\n");

	// 포트 비우기
	if (! ::PurgeComm( m_hComm,	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR)) {
		TRACE1("Failed PurgeComm Function :%d\n",GetLastError());
		ASSERT(0);
		return FALSE;
	}
	TRACE0("PurgeComm Success\n");

	// Set timeouts
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 500;
	timeouts.ReadTotalTimeoutConstant = 500;
	timeouts.WriteTotalTimeoutMultiplier = 2 * dwBaud / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 500;

	if (! ::SetCommTimeouts(m_hComm, &timeouts)) {
		TRACE1("Failed SetCommTimeouts Function :%d\n",GetLastError());
		ASSERT(0);
		return FALSE;
	}
	TRACE0("SetCommTimeouts Success\n");
	
	if (! ::GetCommState(m_hComm,&PortDCB)) {
		TRACE1("Failed GetCommState Function :%d\n",GetLastError());
		ASSERT(0);
		return FALSE;
	}
	TRACE0("GetCommState Success\n");

	// Set DCB
	PortDCB.BaudRate = dwBaud;			// Current baud 
	PortDCB.ByteSize = bytesize;
	PortDCB.fParity = FALSE;			// Enable parity checking 
	PortDCB.Parity = parity;
	PortDCB.StopBits = stopbit;
	/*PortDCB.fBinary = TRUE;				// Binary mode; no EOF check 
	PortDCB.fOutxCtsFlow = FALSE;
	PortDCB.fOutxDsrFlow = FALSE;
	PortDCB.fDtrControl = TRUE;
	PortDCB.fDsrSensitivity = FALSE;
	PortDCB.fTXContinueOnXoff = FALSE;
	PortDCB.fOutX = FALSE;				// 여기를 FALSE로 놓아야지 0x00데이터가 들어온다.
	PortDCB.fInX = FALSE;					// No XON/XOFF in flow control 
	PortDCB.fErrorChar = FALSE;
	PortDCB.fNull = FALSE;
	PortDCB.fRtsControl = TRUE;
	PortDCB.fAbortOnError = FALSE;
	PortDCB.fDummy2 = FALSE;
	PortDCB.wReserved = FALSE;
	PortDCB.XonLim = 100;
	PortDCB.XoffLim = 100;
	PortDCB.XonChar = FALSE;
	PortDCB.XoffChar = FALSE;
	PortDCB.EofChar = 0;
	PortDCB.EvtChar = 0;
	PortDCB.wReserved1 = 0;*/
	
	if (! ::SetCommState(m_hComm, &PortDCB)) {
		TRACE1("Failed SetCommState function :%d\n",GetLastError());
		ASSERT(0);
		return FALSE;
	}
	TRACE0("SetCommState Success\n");

	m_bConnected = TRUE;								// 포트 상태 설정

	m_pThread = AfxBeginThread(CommThread, this, THREAD_PRIORITY_HIGHEST);
	TRACE0("Start CommThread \n");

	if (m_highTimer.IsTimerStarted())
		m_highTimer.EndTimer();

	m_highTimer.SetTimerInfo(this,1);
	m_highTimer.StartTimer(TimerThread);

	return TRUE;
}

// 포트 닫기
void CComm::ClosePort()
{
	DWORD dwExitCode = 0;

	if(m_highTimer.IsTimerStarted())
		m_highTimer.EndTimer();
	
	if(m_pThread) {
		GetExitCodeThread(m_pThread,&dwExitCode);
		TerminateThread(m_pThread->m_hThread, dwExitCode);
		m_pThread->Delete();
		m_pThread = NULL;
	}
	
	if(m_hComm != INVALID_HANDLE_VALUE)
		CloseHandle(m_hComm);
	m_hComm = NULL;
}

//Serial 포트로부터 데이터를 읽어오는 함수
BOOL CComm::ReadData()
{
	BYTE buffer[MAX_BUFF_SIZE] = {0x00};				//데이터를 저장할 Character Buffer 선언
	DWORD dwRead = 0;									//읽을 바이트 수
	DWORD dwErrorFlags = 0;								//ClearCommError 함수가 반환하는 에러 Flag
	DWORD dwWrite = 0;									//읽은 바이트 수
	PUCHAR chPrevData = NULL;
	DWORD dwPrevBufLen = 0;

	if (!ClearCommError(m_hComm, &dwErrorFlags, &m_comstat))	//현재 시리얼디바이스의 에러정보 및 상태를 반환
		return FALSE;

	dwRead = m_comstat.cbInQue;							//Serial Provider에 의해 받아진 바이트 수 (ReadFile() function에 의해 읽히기전)
	TRACE1("받은 큐의 크기:%d\n",dwRead);

	if(dwRead > 0)
	{
		if (!ReadFile(m_hComm, (LPVOID)buffer, dwRead, &dwWrite, &m_osRead))
			return FALSE;

		if (!m_pszTmpData) {
			m_pszTmpData = new UCHAR[dwRead];
			memset(m_pszTmpData, 0x00, dwRead);
		} else {
			dwPrevBufLen = m_nTmpDataLen;
			chPrevData = m_pszTmpData;
			m_pszTmpData = new UCHAR[dwPrevBufLen + dwRead];
			memset(m_pszTmpData, 0x00, dwPrevBufLen + dwRead);
			memcpy(m_pszTmpData, chPrevData, dwPrevBufLen);
			SAFE_DELETE(chPrevData);
		}

		memcpy(m_pszTmpData+dwPrevBufLen, buffer, dwRead);
		m_nTmpDataLen += dwRead;

		if (m_nMode == COMM_RMODE_TIMELIMIT)
			m_bRecvTimer = TRUE;
		
	}

	return TRUE;
}

// Process of 'End Code' Mode
void CComm::RModeEndCode()
{
	BOOL bValid = TRUE;
	UINT i = 0, j = 0;
	PUCHAR pszPrevData = NULL;

	for (i=0;i < m_nTmpDataLen; i++) {
		if (m_pszTmpData[i] == m_pszEndCode[0]) {
			bValid = TRUE;
			for (j=0; j < m_nEndCodeLen;j++) {
				if ((i+j) >= m_nTmpDataLen) {
					bValid = FALSE;
					break;
				}
				if (m_pszTmpData[i+j] != m_pszEndCode[j]) {
					bValid = FALSE;
					break;
				}
			}
			if (bValid) {
				m_pszData = new UCHAR[i+j-1];
				memset(m_pszData, 0x00, i+j-1);
				memcpy(m_pszData, m_pszTmpData, i+j-1);
				m_nDataLen = i+j-1;
				if (m_nTmpDataLen == (i+j)) {
					SAFE_DELETE(m_pszTmpData);
					m_nTmpDataLen = 0;
					m_pOwner->SendMessage(WM_RECEIVE_COMM);
					break;
				} else if (m_nTmpDataLen > (i+j)) {
					if ((i+j-1) != 0 ) {
						pszPrevData = m_pszTmpData;
						m_nTmpDataLen -= i+j;
						m_pszTmpData = new UCHAR[m_nTmpDataLen];
						memset(m_pszTmpData, 0x00, m_nTmpDataLen);
						memcpy(m_pszTmpData, pszPrevData+(i+j), m_nTmpDataLen);
						SAFE_DELETE(pszPrevData);
					} else {
						SAFE_DELETE(m_pszTmpData);
						m_nTmpDataLen = 0;
					}
					m_pOwner->SendMessage(WM_RECEIVE_COMM);
				}
			}
		}
	}
}

// Process of 'Time Limit' Mode
void CComm::RModeTimeLimit()
{
	m_pszData = m_pszTmpData;

	m_nDataLen = m_nTmpDataLen;
	m_nTmpDataLen = 0;

	m_pszTmpData = NULL;

	m_pOwner->SendMessage(WM_RECEIVE_COMM);

	SetCurrentDelayTime(0);

	m_bRecvTimer = FALSE;
}

// Process of 'Count Limit' Mode
void CComm::RModeCountLimit()
{
	PUCHAR chPrevData = NULL;
	UINT nMemSize = 0;

	m_bHasTransfered = FALSE;

	if (nMemSize == m_nLimitCnt) {
		m_pszData = new UCHAR[m_nLimitCnt];
		memset(m_pszData, 0x00, m_nLimitCnt);
		memcpy(m_pszData, m_pszTmpData, m_nLimitCnt);
		SAFE_DELETE(m_pszTmpData);
		m_nTmpDataLen = 0;
		m_pOwner->SendMessage(WM_RECEIVE_COMM);
	} else if (nMemSize > m_nLimitCnt) {
		chPrevData = m_pszTmpData;
		m_pszData = new UCHAR[m_nLimitCnt];
		memset(m_pszData, 0x00, m_nLimitCnt);
		memcpy(m_pszData, chPrevData, m_nLimitCnt);
		m_nDataLen = m_nLimitCnt;

		m_nTmpDataLen -= m_nLimitCnt;

		m_pszTmpData = new UCHAR[m_nTmpDataLen];
		memset(m_pszTmpData, 0x00, m_nTmpDataLen);
		memcpy(m_pszTmpData, chPrevData+m_nLimitCnt, m_nTmpDataLen);

		SAFE_DELETE(chPrevData);

		m_pOwner->SendMessage(WM_RECEIVE_COMM);
	}	
}

//////////////////////////////////////////////////////////////////////////
// SendData Function
//
// Send the data to the connected COM port
//////////////////////////////////////////////////////////////////////////

DWORD CComm::SendData(LPCVOID pSendData, DWORD nNumberOfByteToWrite, PUCHAR pszSentData, DWORD dwOutBufLen)
{
	BYTE	pBuff[MAX_BUFF_SIZE] = {0x00};		//보내질 데이터가 바이트단위로 저장되는 변수
	DWORD	nNumberOfByteWritten=0;				//WriteFile에 의해 보내진 바이트수가 저장되는 변수
	UINT	nBuffByte=0;						//ConvAsc2Hexa에 의해 pBuff에 기록된 바이트수가 저장되는 변수

	if (nNumberOfByteToWrite > MAX_BUFF_SIZE) {
		m_nLastErrNum = COMM_ERROR_BUFFER_OVERFLOW;
		return 0;
	}

	if (!m_Asc2HexConv.ConvAsc2Hex((PUCHAR)pSendData, nNumberOfByteToWrite, pBuff, MAX_BUFF_SIZE, &nBuffByte))
		return 0;

	if (!WriteFile(m_hComm, pBuff, nBuffByte, &nNumberOfByteWritten, &m_osWrite)) {
		if (GetLastError() != ERROR_IO_PENDING)
			return 0;
	}

	if (nBuffByte >= dwOutBufLen)
		return 0;

	memset(pszSentData, 0x00, dwOutBufLen);
	memcpy(pszSentData, pBuff, nBuffByte);

	return nBuffByte;
}

//////////////////////////////////////////////////////////////
// Thread													//
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// COMM Thread
//
// Check the data received from the connected com port
// If the connection is ended, the thread exits the while loop and terminated
//////////////////////////////////////////////////////////////////////////

UINT CComm::CommThread(LPVOID lParam)
{
	CComm *pComm = (CComm*)lParam;
	DWORD dwEvent = 0;	// 이값이 1이면 RXCHAR이다 

	while(pComm->IsConnected())
	{
		WaitCommEvent(pComm->GetCommHandle(), &dwEvent, NULL);
		if(dwEvent == EV_RXCHAR)
		{
			pComm->ReadData();
		}
		Sleep(1);
	} // while

	return 1;
}

//////////////////////////////////////////////////////////////////////////
// Timer Thread
//
// Check the received data from the connected COM port
// This timer is repeated for 1ms
// 
//////////////////////////////////////////////////////////////////////////

void CComm::TimerThread(LPVOID lParam)
{	
	CComm *pComm = (CComm*)lParam;

	switch(pComm->GetMode())
	{
	case COMM_RMODE_ENDCODE:
		if (pComm->m_pszTmpData) {
			pComm->RModeEndCode();
		}
		break;

	case COMM_RMODE_TIMELIMIT:
		//Data End Check Timer가 실행중인지
		if(pComm->IsTimerEnabled())							
		{
			// m_nSetRXTime동안 Data가 들어오지 않으면 Data Recv 완료
			if((pComm->GetCurrentDelayTime()) >= (pComm->GetLimitDelayTime()))
				pComm->RModeTimeLimit();
			else
				pComm->IncreaseCurrentDelay();
		}
		break;

	case COMM_RMODE_COUNTLIMIT:
		if (pComm->m_pszTmpData) {
			if ((pComm->m_nTmpDataLen >= pComm->m_nLimitCnt) && (pComm->m_bHasTransfered))
				pComm->RModeCountLimit();
		}
		break;
	}
}