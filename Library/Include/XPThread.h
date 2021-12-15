// $Author: Zhangxp $
// $Date: 00-05-23 10:49 $
// $Revision: 7 $
// $Workfile: XPThread.h $
#if !defined(AFX_XPTHREAD_H__B842D96F_F0D7_11D3_B110_0010B5046BFD__INCLUDED_)
#define AFX_XPTHREAD_H__B842D96F_F0D7_11D3_B110_0010B5046BFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxmt.h>

class CXPCritSec
{
friend class CXPWatchDog;
    CXPCritSec(const CXPCritSec &refCritSec);
    CXPCritSec &operator=(const CXPCritSec &refCritSec);
	
	CRITICAL_SECTION m_CritSec;
	operator CRITICAL_SECTION(){
	return m_CritSec;
	}
public:
	CXPCritSec() {
	InitializeCriticalSection(&m_CritSec);
    };

    ~CXPCritSec() {
	DeleteCriticalSection(&m_CritSec);
    };
	
};
class CXPWatchDog
{
	CXPWatchDog();
    CXPWatchDog(const CXPWatchDog &refDog);
    CXPWatchDog &operator=(const CXPWatchDog &refDog);

	CRITICAL_SECTION m_CritSec;
public:
	CXPWatchDog(CXPCritSec &refCritSec){
	m_CritSec = refCritSec;
	EnterCriticalSection(&m_CritSec);
	}
	~CXPWatchDog(){
	LeaveCriticalSection(&m_CritSec);
    };
};

class CXPEvent : public CEvent
{
public:
	CXPEvent():CEvent(FALSE,TRUE,NULL,NULL){}
	BOOL Check(){return Wait(0);};
	BOOL Wait(){return Wait(INFINITE);}
	BOOL Wait(DWORD dwMilliseconds)
		{return ::WaitForSingleObject(m_hObject,dwMilliseconds)== WAIT_OBJECT_0;}
	operator HANDLE (){return m_hObject;}
};

enum THREAD_STATUS {THREAD_INIT, THREAD_START,THREAD_STOP};
class CXPStatus : public CXPEvent
{
public:
	int	m_iError;
	THREAD_STATUS	m_Status;
	CXPStatus():m_iError(0){
		SetEvent();
	};
	void Set(THREAD_STATUS status){
		m_Status = status;
		SetEvent();
	};
	void Clear(){ 
		m_iError = 0;
		ResetEvent();
	};
	THREAD_STATUS Get(){return m_Status;};
};

#define XPWATCHDOG CXPWatchDog dog(m_CritSec)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPTHREAD_H__B842D96F_F0D7_11D3_B110_0010B5046BFD__INCLUDED_)
