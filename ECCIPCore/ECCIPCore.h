// ECCIPCore.h : main header file for the ECCIPCORE application
//

#if !defined(AFX_ECCIPCORE_H__6FC89364_0219_487C_BB6E_FF4A960186BB__INCLUDED_)
#define AFX_ECCIPCORE_H__6FC89364_0219_487C_BB6E_FF4A960186BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreApp:
// See ECCIPCore.cpp for the implementation of this class
//

class CECCIPCoreApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pDocTemplate;
	CECCIPCoreApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECCIPCoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CECCIPCoreApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg LONG OnReceiveSim(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECCIPCORE_H__6FC89364_0219_487C_BB6E_FF4A960186BB__INCLUDED_)
