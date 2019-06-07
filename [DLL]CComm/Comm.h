//////////////////////////////////////////////////////////////////////
// Comm.h: interface for the CComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMM_H__D8065BC9_25D2_49BA_ADC1_CB12B804F8DE__INCLUDED_)
#define AFX_COMM_H__D8065BC9_25D2_49BA_ADC1_CB12B804F8DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef CCOMMAPI_EXPORTS
	#define CCOMMAPI __declspec(dllexport)
#else
	#define CCOMMAPI __declspec(dllimport)
#endif

#include "../Include/AscToHexConv.h"
#include "../Include/HighTimer.h"

// User Defined MESSAGE
#define WM_RECEIVE_COMM		WM_USER + 100

// COMM Receive Mode
#define COMM_RMODE_ENDCODE		0x00		// End Code Mode
#define COMM_RMODE_TIMELIMIT	0x01		// Time Limit Mode
#define COMM_RMODE_COUNTLIMIT	0x02		// Count Limit Mode

#define MAX_BUFF_SIZE			1024		// Max buffer size

// Error Description
#define COMM_ERROR_BUFFER_OVERFLOW		0x01	// Buffer overflow
#define COMM_ERROR_RMODE_INCORRECT		0x02	// Receive Mode is incorrect
#define COMM_ERROR_OPENPORT				0x03	// Error occured while open port

#define SAFE_DELETE(p)	if(p){delete p;(p)=NULL;};

class CCOMMAPI CComm  
{

// Constructor, Destructor
public:
	CComm();
	virtual ~CComm();

// Attributes
public:
	UINT			m_nMode;				// Read 모드

	UINT			m_nDelay;				//현재의 Delay수치를 저장할 변수

	PUCHAR			m_pszEndCode;			// End Code 방식일때의 End Code 값
	UINT			m_nEndCodeLen;

	UINT			m_nLimitTime;			// Time Limit 방식일때의 Limit 값 (Default : 30ms)
	UINT			m_nLimitCnt;			// Count Limit 방식일때의 Limit 값

	BOOL			m_bRecvTimer;			// Recv check Start Flag. Set FALSE
	BOOL			m_bHasTransfered;		// 조건에 맞는 데이터가 전송 되었는지 확인하는 변수

	PUCHAR			m_pszData;				// The data read from port
	UINT			m_nDataLen;

	PUCHAR			m_pszTmpData;			// The temporary data for save before m_pszData has transferred.
	UINT			m_nTmpDataLen;

	CWnd			*m_pOwner;				// The pointer of parent window

	CWinThread		*m_pThread;				// CommThread pointer

	CHighTimer		m_highTimer;
	CAscToHexConv	m_Asc2HexConv;			// ASCii 값을 Hex값으로 변환하는 클래스

	UINT			m_nLastErrNum;

	/////////////////////////통신포트 정의///////////////
	OVERLAPPED		m_osRead, m_osWrite;	//포트 파일 Overlapped structure
	HANDLE			m_hComm;				//통신 포트 파일 핸들
	LPSTR			m_pszPortName;			//포트 이름 (COM1 ..)
	BOOL			m_bConnected;			//포트가 열렸는지 유무를 나타냄.
	COMSTAT			m_comstat;				//COM 포트의 상태정보 변수 ClearCommError() 함수에 의해 정보 읽음

// Getter , Setter
public:
	UINT	GetMode();
	BOOL	SetMode(IN UINT nMode, IN LPVOID paramData, IN UINT nParamSize);

	UINT	GetLimitDelayTime();

	UINT	GetCurrentDelayTime();
	void	SetCurrentDelayTime(IN UINT nDelayTime);

	BOOL	IsTimerEnabled();
	void	SetTimerEnable(BOOL bEnable);

	void	GetPortName(OUT LPSTR pszPortName, IN UINT nBufLen);

	HANDLE	GetCommHandle();

	UINT	GetLastCommError();

	CWnd*	GetOwnerWnd();

// Operations
public:
	DWORD	GetRecvData(OUT PUCHAR pszData, IN UINT nBufLen);
	void	IncreaseCurrentDelay();							//현재의 Delay 수치를 1증가시키는 함수
	BOOL	IsConnected();									//현재 COM 포트와 연결되어있는지여부를 반환

	// Open port
	BOOL OpenPort(IN	CWnd		*pPortOwner,				//포트 소유 윈도우
				  IN	LPCSTR		pPortName,					//포트 이름 (COM1 ..)
				  IN	DWORD		dwBaud,						//Baudrate
				  IN	BYTE		parity,						//Parity
				  IN	BYTE		bytesize,					//Byte Size
				  IN	BYTE		stopbit,					//StopBit
				  IN	UINT		nMode,						//통신방식
				  IN	LPVOID		paramData,					//통신방식에 따른 설정값
				  IN	UINT		nParamSize);				//ParamData의 사이즈
	
	void ClosePort();										//포트 닫기

	DWORD SendData(IN LPCVOID pSendData, IN DWORD nNumberOfByteToWrite, OUT PUCHAR pszSentData, IN DWORD dwOutBufLen);		//데이터 전송
	BOOL  ReadData();										//데이터 읽기

	void RModeEndCode();
	void RModeTimeLimit();
	void RModeCountLimit();

	static void TimerThread(LPVOID lParam);
	static UINT CommThread(LPVOID lParam);
};

#endif // !defined(AFX_COMM_H__D8065BC9_25D2_49BA_ADC1_CB12B804F8DE__INC