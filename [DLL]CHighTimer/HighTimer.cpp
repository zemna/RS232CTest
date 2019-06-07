// HighTimer.cpp: implementation of the CHighTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#define CHIGHTIMER_EXPORTS
#include "HighTimer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHighTimer::CHighTimer()
{
	m_nInterval = 0;
	m_liLastTime.QuadPart = 0;
	m_pFNCB = NULL;
	m_pThread = NULL;
	m_bTerminateThread = FALSE;
	m_bPause = FALSE;
}

CHighTimer::~CHighTimer()
{
	EndTimer();
}

///////////////////////////////////////////////////////////////////////////
// Getter / Setter
///////////////////////////////////////////////////////////////////////////

//마지막으로 이벤트를 발생시켰던 Time 값 반환 
LONGLONG CHighTimer::GetLastTime()
{	
	return m_liLastTime.QuadPart;
}

//마지막으로 발생시킨 이벤트의 Time 값 설정
void CHighTimer::SetLastTime(LONGLONG& llLastTime)
{
	m_liLastTime.QuadPart = llLastTime;
}

//현재의 Interval 반환 
UINT CHighTimer::GetInterval()
{
	return m_nInterval;
}

//실행중인 스레드의 핸들 반환
CWinThread* CHighTimer::GetThreadHandle()
{
	return m_pThread;
}

PFNCB CHighTimer::GetTimerProc()
{
	return m_pFNCB;
}

LPVOID CHighTimer::GetParentClass()
{
	return m_lpParent;
}

BOOL CHighTimer::IsTimerStarted()
{
	return (m_pThread != NULL);
}

BOOL CHighTimer::IsPaused()
{
	return m_bPause;
}
///////////////////////////////////////////////////////////////////////////
// Operations
///////////////////////////////////////////////////////////////////////////

// 부모 클래스의 정보와 Interval 설정
void CHighTimer::SetTimerInfo(LPVOID lpParent, UINT nInterval)
{
	m_lpParent = lpParent;
	m_nInterval = nInterval;
}

//타이머 시작
void CHighTimer::StartTimer(PFNCB pFNCB)
{
	m_pFNCB = pFNCB;
	m_bTerminateThread = FALSE;
	m_pThread = AfxBeginThread(TimerThread,this,THREAD_PRIORITY_HIGHEST);
}

//타이머 종료
void CHighTimer::EndTimer()
{
	DWORD dwResult = 0;

	if (AfxIsValidAddress(m_pThread, sizeof(CWinThread), 0))
	{
		m_bTerminateThread = TRUE;

		dwResult = ::WaitForSingleObject(m_pThread->m_hThread,1000);

		if (dwResult == WAIT_OBJECT_0) {
			// Do nothing
		}
		else if (dwResult == WAIT_TIMEOUT) {
			DWORD dwExitCode=0;
			GetExitCodeThread(m_pThread->m_hThread,&dwExitCode);
			TerminateThread(m_pThread->m_hThread,dwExitCode);
		}

		m_pThread=NULL;
	}
}

void CHighTimer::Pause()
{
	m_bPause = TRUE;
}

void CHighTimer::Resume()
{
	m_bPause = FALSE;
}

///////////////////////////////////////////////////////////////////////////
// Thread
///////////////////////////////////////////////////////////////////////////

UINT CHighTimer::TimerThread(LPVOID lParam)
{
	CHighTimer		*pHighTimer = (CHighTimer*)lParam;
	LARGE_INTEGER	liValue;
	LARGE_INTEGER	liFreq;
	BOOL			bContinue = TRUE;
	DWORD			iEvent = 0;

	QueryPerformanceFrequency(&liFreq);
	TRACE1("Frequency : %d\n", liFreq);

	QueryPerformanceCounter(&liValue);
	pHighTimer->SetLastTime(liValue.QuadPart);
	
	while (bContinue)
	{
		if (pHighTimer->m_bTerminateThread)
			break;

		Sleep(1);
		QueryPerformanceCounter(&liValue);

		if (!pHighTimer->IsPaused()) {
			
			if (liValue.QuadPart >= (pHighTimer->GetInterval() * liFreq.QuadPart)/1000 + pHighTimer->GetLastTime()) {
				TRACE2("OCCURED~~!!. StartValue=%d, CurrentValue=%d ,",pHighTimer->GetLastTime(),liValue.QuadPart);
				TRACE1("ELAPSED TIME : %d\n",((liValue.QuadPart - pHighTimer->GetLastTime())*1000)/liFreq.QuadPart);
				pHighTimer->SetLastTime(liValue.QuadPart);
				(*(pHighTimer->GetTimerProc()))(pHighTimer->GetParentClass());
			}

		}
	}

	pHighTimer = NULL;
	return 0;
}