#if !defined(AFX_CORETHREAD_H__A0CD0300_8717_4FCC_A51D_F02FF0CC96A8__INCLUDED_)
#define AFX_CORETHREAD_H__A0CD0300_8717_4FCC_A51D_F02FF0CC96A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// corethread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCoreThread thread

class CCoreThread : public CWinThread
{
    CCoreThread(const CCoreThread &refThread);
    CCoreThread &operator=(const CCoreThread &refThread);

	DECLARE_DYNCREATE(CCoreThread)

	HANDLE		m_hWaitEvents[3];

	CXPEvent	m_eDeadEvent;
	CXPEvent	m_eEndEvent;
	CXPEvent	m_eStartEvent;
	CXPEvent	m_eStopEvent;
	CXPEvent	m_eBreakEvent;

	CXPStatus	m_eStatus;
	CXPCritSec	m_CritSec;

protected:
public:
	CCoreThread();           // protected constructor used by dynamic creation

// Attributes
void KillThread();

// Operations
public:

	BOOL	IsStoped();
	BOOL	IsRunning();
	int		Start();
	int		Stop();
	virtual int Process(){return 0;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoreThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCoreThread();
	void Delete();

	// Generated message map functions
	//{{AFX_MSG(CCoreThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CORETHREAD_H__A0CD0300_8717_4FCC_A51D_F02FF0CC96A8__INCLUDED_)
