// corethread.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\XPThread.h"
#include "..\include\corethread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoreThread

IMPLEMENT_DYNCREATE(CCoreThread, CWinThread)

CCoreThread::CCoreThread():CWinThread()
{
	m_bAutoDelete = FALSE;
	m_hWaitEvents[0] = m_eEndEvent;
	m_hWaitEvents[1] = m_eStartEvent;
	m_hWaitEvents[2] = m_eStopEvent;
	m_eStatus.Set(THREAD_INIT);
	if(CreateThread(CREATE_SUSPENDED))
		SetThreadPriority(THREAD_PRIORITY_NORMAL);//THREAD_PRIORITY_HIGHEST
	else ASSERT(0);
	ResumeThread();
}

CCoreThread::~CCoreThread()
{
}

BOOL	CCoreThread::IsStoped()
{
	return m_eStatus.Get() == THREAD_STOP || 
		   m_eStopEvent.Check() ||
		   m_eEndEvent.Check();
}

BOOL	CCoreThread::IsRunning()
{
	return m_eStatus.Get() == THREAD_START || m_eStartEvent.Check() == TRUE;
}

int CCoreThread::Start()
{
	//ASSERT(IsStarted() == FALSE);
	ASSERT(m_eStatus.Get() != THREAD_INIT);
	//ASSERT(m_eStatus.Check());

	m_eStatus.Clear();
	m_eStartEvent.SetEvent();
	return 0;
}

int CCoreThread::Stop()
{
	//ASSERT(IsStoped() == FALSE);
	ASSERT(m_eStatus.Get() != THREAD_INIT);
	//ASSERT(m_eStatus.Check());
	
	m_eStatus.Clear();
	m_eStopEvent.SetEvent();
	m_eStatus.Wait();
	return m_eStatus.m_iError;
}

BOOL CCoreThread::InitInstance()
{
	m_eStatus.Set(THREAD_STOP);
	DWORD dw;
	while(1)
	{
		dw = ::WaitForMultipleObjects(3,m_hWaitEvents,FALSE,INFINITE);
		if(dw == WAIT_OBJECT_0)	return FALSE;	// 结束线程
		else if(dw == WAIT_OBJECT_0+1)			// 开始任务
		{
			m_eStartEvent.ResetEvent();
			m_eStatus.Set(THREAD_START);
			m_eStatus.m_iError = Process();
			m_eStatus.Set(THREAD_STOP);
		}
		else if(dw == WAIT_OBJECT_0+2)			// 结束任务
		{
			m_eStopEvent.ResetEvent();
			m_eStatus.Set(THREAD_STOP);
		}
	}
	return FALSE;
}

int CCoreThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

void CCoreThread::Delete()
{
	CWinThread::Delete();
	m_eDeadEvent.SetEvent();
}

void CCoreThread::KillThread()
{
	if(m_hThread)
	{
		m_eEndEvent.SetEvent();
		if(m_eStatus.Get() != THREAD_INIT)
		{
			m_eDeadEvent.Wait();
			WaitForSingleObject(m_hThread, INFINITE);
		}
	}
	delete this;
}

BEGIN_MESSAGE_MAP(CCoreThread, CWinThread)
	//{{AFX_MSG_MAP(CCoreThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoreThread message handlers
