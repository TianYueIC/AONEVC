// SSX16A.h : main header file for the SSX16A application
//

#if !defined(AFX_SSX16A_H__5D528425_3F7D_45B2_AF64_AF3BEC505B53__INCLUDED_)
#define AFX_SSX16A_H__5D528425_3F7D_45B2_AF64_AF3BEC505B53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSSX16AApp:
// See SSX16A.cpp for the implementation of this class
//

class CSSX16AApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pDocTemplate;
	CSSX16AApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSX16AApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSSX16AApp)
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

#endif // !defined(AFX_SSX16A_H__5D528425_3F7D_45B2_AF64_AF3BEC505B53__INCLUDED_)
