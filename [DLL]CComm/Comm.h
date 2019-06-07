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
	UINT			m_nMode;				// Read ���

	UINT			m_nDelay;				//������ Delay��ġ�� ������ ����

	PUCHAR			m_pszEndCode;			// End Code ����϶��� End Code ��
	UINT			m_nEndCodeLen;

	UINT			m_nLimitTime;			// Time Limit ����϶��� Limit �� (Default : 30ms)
	UINT			m_nLimitCnt;			// Count Limit ����϶��� Limit ��

	BOOL			m_bRecvTimer;			// Recv check Start Flag. Set FALSE
	BOOL			m_bHasTransfered;		// ���ǿ� �´� �����Ͱ� ���� �Ǿ����� Ȯ���ϴ� ����

	PUCHAR			m_pszData;				// The data read from port
	UINT			m_nDataLen;

	PUCHAR			m_pszTmpData;			// The temporary data for save before m_pszData has transferred.
	UINT			m_nTmpDataLen;

	CWnd			*m_pOwner;				// The pointer of parent window

	CWinThread		*m_pThread;				// CommThread pointer

	CHighTimer		m_highTimer;
	CAscToHexConv	m_Asc2HexConv;			// ASCii ���� Hex������ ��ȯ�ϴ� Ŭ����

	UINT			m_nLastErrNum;

	/////////////////////////�����Ʈ ����///////////////
	OVERLAPPED		m_osRead, m_osWrite;	//��Ʈ ���� Overlapped structure
	HANDLE			m_hComm;				//��� ��Ʈ ���� �ڵ�
	LPSTR			m_pszPortName;			//��Ʈ �̸� (COM1 ..)
	BOOL			m_bConnected;			//��Ʈ�� ���ȴ��� ������ ��Ÿ��.
	COMSTAT			m_comstat;				//COM ��Ʈ�� �������� ���� ClearCommError() �Լ��� ���� ���� ����

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
	void	IncreaseCurrentDelay();							//������ Delay ��ġ�� 1������Ű�� �Լ�
	BOOL	IsConnected();									//���� COM ��Ʈ�� ����Ǿ��ִ������θ� ��ȯ

	// Open port
	BOOL OpenPort(IN	CWnd		*pPortOwner,				//��Ʈ ���� ������
				  IN	LPCSTR		pPortName,					//��Ʈ �̸� (COM1 ..)
				  IN	DWORD		dwBaud,						//Baudrate
				  IN	BYTE		parity,						//Parity
				  IN	BYTE		bytesize,					//Byte Size
				  IN	BYTE		stopbit,					//StopBit
				  IN	UINT		nMode,						//��Ź��
				  IN	LPVOID		paramData,					//��Ź�Ŀ� ���� ������
				  IN	UINT		nParamSize);				//ParamData�� ������
	
	void ClosePort();										//��Ʈ �ݱ�

	DWORD SendData(IN LPCVOID pSendData, IN DWORD nNumberOfByteToWrite, OUT PUCHAR pszSentData, IN DWORD dwOutBufLen);		//������ ����
	BOOL  ReadData();										//������ �б�

	void RModeEndCode();
	void RModeTimeLimit();
	void RModeCountLimit();

	static void TimerThread(LPVOID lParam);
	static UINT CommThread(LPVOID lParam);
};

#endif // !defined(AFX_COMM_H__D8065BC9_25D2_49BA_ADC1_CB12B804F8DE__INC