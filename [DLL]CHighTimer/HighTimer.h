//////////////////////////////////////////////////////////////////////
// HighTimer.h: interface for the CHighTimer class.
//
// CPU Timer�� �̿��� ���� Ÿ�̸�
//
// �����
// 1. ����� Ŭ������ UINT �Լ��̸�(LPVOID lParam); ������ �Լ��� ����
// 2. Ÿ�̸� �̺�Ʈ�� �߻���ų �������� StartTimer(Interval, �Լ��̸�) �� ����
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIGHTIMER_H__9AD8F882_E18C_41F6_A72D_D5D09C171295__INCLUDED_)
#define AFX_HIGHTIMER_H__9AD8F882_E18C_41F6_A72D_D5D09C171295__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef CHIGHTIMER_EXPORTS
	#define CHIGHTIMER_API __declspec(dllexport)
#else
	#define CHIGHTIMER_API __declspec(dllimport)
#endif

#define WM_ONHIGHTIMER	WM_USER + 101

typedef void FNCB(LPVOID);
typedef FNCB* PFNCB;

class CHIGHTIMER_API CHighTimer  
{
// Constructor , Destructor
public:
	CHighTimer();
	virtual ~CHighTimer();

// Attributes
private:
	CWinThread		*m_pThread;			// TimerThread �ڵ�
	LARGE_INTEGER	m_liLastTime;		// ������ Count ��
	UINT			m_nInterval;		// �̺�Ʈ�� �߻���ų Interval ��
	PFNCB			m_pFNCB;			// Callback Function
	LPVOID			m_lpParent;			// The pointer of parent class
	BOOL			m_bTerminateThread;
	BOOL			m_bPause;

// Getter , Setter
public:
	BOOL		IsTimerStarted();
	UINT		GetInterval();							//������ Interval ���� ��ȯ
	LONGLONG	GetLastTime();							//������ Count �� ���
	void		SetLastTime(LONGLONG& llLastTime);		//LastTime ����
	PFNCB		GetTimerProc();							//�ݹ��Լ� ������ ��ȯ
	CWinThread	*GetThreadHandle();
	LPVOID		GetParentClass();
	BOOL		IsPaused();

// Operations
public:
	void		Pause();
	void		Resume();
	void		EndTimer();									//�������� TimerThread �����ϱ�
	void		SetTimerInfo(LPVOID lpParent, UINT nInterval);
	void		StartTimer(PFNCB pFNCB);	//TimerThread �����ϱ�

	static UINT TimerThread(LPVOID lParam);
};

#endif // !defined(AFX_HIGHTIMER_H__9AD8F882_E18C_41F6_A72D_D5D09C171295__INCLUDED_)
