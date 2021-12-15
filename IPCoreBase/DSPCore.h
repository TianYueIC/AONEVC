// DSPCore.h : main header file for the DSPCORE application
//

#if !defined(AFX_DSPCORE_H__5D528425_3F7D_45B2_AF64_AF3BEC505B53__INCLUDED_)
#define AFX_DSPCORE_H__5D528425_3F7D_45B2_AF64_AF3BEC505B53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreApp:
// See DSPCore.cpp for the implementation of this class
//

class CDSPCoreApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pDocTemplate;
	CDSPCoreApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPCoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDSPCoreApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnMenuReport();
	afx_msg LONG OnReceiveSim(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPCORE_H__5D528425_3F7D_45B2_AF64_AF3BEC505B53__INCLUDED_)
