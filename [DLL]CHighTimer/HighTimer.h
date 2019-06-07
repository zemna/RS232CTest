//////////////////////////////////////////////////////////////////////
// HighTimer.h: interface for the CHighTimer class.
//
// CPU Timer를 이용한 고성능 타이머
//
// 사용방법
// 1. 사용할 클래스에 UINT 함수이름(LPVOID lParam); 형식의 함수를 선언
// 2. 타이머 이벤트를 발생시킬 시점에서 StartTimer(Interval, 함수이름) 을 실행
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
	CWinThread		*m_pThread;			// TimerThread 핸들
	LARGE_INTEGER	m_liLastTime;		// 현재의 Count 값
	UINT			m_nInterval;		// 이벤트를 발생시킬 Interval 값
	PFNCB			m_pFNCB;			// Callback Function
	LPVOID			m_lpParent;			// The pointer of parent class
	BOOL			m_bTerminateThread;
	BOOL			m_bPause;

// Getter , Setter
public:
	BOOL		IsTimerStarted();
	UINT		GetInterval();							//설정된 Interval 값을 반환
	LONGLONG	GetLastTime();							//현재의 Count 값 얻기
	void		SetLastTime(LONGLONG& llLastTime);		//LastTime 설정
	PFNCB		GetTimerProc();							//콜백함수 포인터 반환
	CWinThread	*GetThreadHandle();
	LPVOID		GetParentClass();
	BOOL		IsPaused();

// Operations
public:
	void		Pause();
	void		Resume();
	void		EndTimer();									//실행중인 TimerThread 종료하기
	void		SetTimerInfo(LPVOID lpParent, UINT nInterval);
	void		StartTimer(PFNCB pFNCB);	//TimerThread 시작하기

	static UINT TimerThread(LPVOID lParam);
};

#endif // !defined(AFX_HIGHTIMER_H__9AD8F882_E18C_41F6_A72D_D5D09C171295__INCLUDED_)
