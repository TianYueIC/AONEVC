// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__4440C031_84B0_451A_A124_05E843DD04D3__INCLUDED_)
#define AFX_MAINFRM_H__4440C031_84B0_451A_A124_05E843DD04D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Include\ViewBar.h"
#include "..\Include\MessageBar.h"
class CDSPMap;
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CViewBar      m_WatchBar;
	CViewBar      m_RegisterBar;
	CViewBar      m_MemeryBar;
	CMessageBar   m_MessageBar;

	CDSPMap		* m_pMap;
	CDSPMap		* m_pOldMap;
	CMainFrame();
	int			m_iOutListType;
	CString		m_strProjectName;
	CString		m_strPathName;

	char		*m_pTraceOut;
	int			*m_pTraceIP;
	int			m_iTracePos;
// Attributes
public:

// Operations
public:
	void AddMessage(CString &strMsg);
	void ClearMessage();
	void CompileAllFile();
	void LinkAllFile();
	void SendErrorMsg(CString & strMsg);
	void SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut);
	void OpenAllFiles();
	void UpdateDocFile();
	
	void UpdateTitle();
	void UpdateProjectName(LPCTSTR lpszPathName);
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
	afx_msg void OnMenuWatch();
	afx_msg void OnUpdateMenuWatch(CCmdUI* pCmdUI);
	afx_msg void OnMenuCompile();
	afx_msg void OnMenuLink();
	afx_msg void OnUpdateMenuCompile(CCmdUI* pCmdUI);
	afx_msg void OnMenuBreak();
	afx_msg void OnUpdateMenuBreak(CCmdUI* pCmdUI);
	afx_msg void OnMenuClearAllbreakpoint();
	afx_msg void OnUpdateMenuClearAllbreakpoint(CCmdUI* pCmdUI);
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
	afx_msg void OnUpdateMenuLink(CCmdUI* pCmdUI);
	afx_msg void OnMenuConfig();
	afx_msg void OnUpdateMenuConfig(CCmdUI* pCmdUI);
	afx_msg void OnMenuStopEmulator();
	afx_msg void OnUpdateMenuStopEmulator(CCmdUI* pCmdUI);
	afx_msg void OnMenuEmulatorConfig();
	afx_msg void OnUpdateMenuEmulatorConfig(CCmdUI* pCmdUI);
	afx_msg void OnMenuInterrupt();
	afx_msg void OnUpdateMenuInterrupt(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4440C031_84B0_451A_A124_05E843DD04D3__INCLUDED_)
