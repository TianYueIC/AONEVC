// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2A6ABB0A_8905_4920_8486_8F73C0A5ABE2__INCLUDED_)
#define AFX_MAINFRM_H__2A6ABB0A_8905_4920_8486_8F73C0A5ABE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Include\HashViewBar.h"
#include "..\Include\MessageBar.h"

class CHashMap;
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CHashMap		* m_pMap;
	CHashMap		* m_pOldMap;
	CMainFrame();

	char		*m_pTraceOut;
	int			*m_pTraceIP;
	int			m_iTracePos;

	int			m_iOutListType;
	CString		m_strProjectName;
	CString		m_strPathName;

	BOOL		m_bMode,m_bTest;
// Attributes
public:
	CHashViewBar  m_RegisterBar;
	CHashViewBar  m_MemeryBar;
	CMessageBar   m_MessageBar;

// Operations
public:
	void OpenAllFiles();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void UpdateTitle();
	void UpdateProjectName(LPCTSTR lpszPathName);

	void AddMessage(CString &strMsg);
	void ClearMessage();
	void SendErrorMsg(CString & strMsg);
	void SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut);

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMenuMemery();
	afx_msg void OnUpdateMenuMemery(CCmdUI* pCmdUI);
	afx_msg void OnMenuMessage();
	afx_msg void OnUpdateMenuMessage(CCmdUI* pCmdUI);
	afx_msg void OnMenuRegister();
	afx_msg void OnUpdateMenuRegister(CCmdUI* pCmdUI);
	afx_msg void OnMenuBreak();
	afx_msg void OnUpdateMenuBreak(CCmdUI* pCmdUI);
	afx_msg void OnMenuClearAllbreakpoint();
	afx_msg void OnUpdateMenuClearAllbreakpoint(CCmdUI* pCmdUI);
	afx_msg void OnMenuConfig();
	afx_msg void OnUpdateMenuConfig(CCmdUI* pCmdUI);
	afx_msg void OnMenuEmulatorConfig();
	afx_msg void OnUpdateMenuEmulatorConfig(CCmdUI* pCmdUI);
	afx_msg void OnMenuGo();
	afx_msg void OnUpdateMenuGo(CCmdUI* pCmdUI);
	afx_msg void OnMenuReset();
	afx_msg void OnUpdateMenuReset(CCmdUI* pCmdUI);
	afx_msg void OnMenuRestart();
	afx_msg void OnUpdateMenuRestart(CCmdUI* pCmdUI);
	afx_msg void OnMenuStepin();
	afx_msg void OnUpdateMenuStepin(CCmdUI* pCmdUI);
	afx_msg void OnMenuStepout();
	afx_msg void OnUpdateMenuStepout(CCmdUI* pCmdUI);
	afx_msg void OnMenuStepover();
	afx_msg void OnUpdateMenuStepover(CCmdUI* pCmdUI);
	afx_msg void OnMenuStopemulator();
	afx_msg void OnUpdateMenuStopemulator(CCmdUI* pCmdUI);
	afx_msg void OnMenuMode();
	afx_msg void OnUpdateMenuMode(CCmdUI* pCmdUI);
	afx_msg void OnMenuTest();
	afx_msg void OnUpdateMenuTest(CCmdUI* pCmdUI);
	afx_msg void OnMenuTool();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2A6ABB0A_8905_4920_8486_8F73C0A5ABE2__INCLUDED_)
