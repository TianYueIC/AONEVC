// IPCore.h : main header file for the IPCORE application
//

#if !defined(AFX_IPCORE_H__29FBFB41_1E08_4632_AEA1_B82DB5B44550__INCLUDED_)
#define AFX_IPCORE_H__29FBFB41_1E08_4632_AEA1_B82DB5B44550__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPCoreApp:
// See IPCore.cpp for the implementation of this class
//

class CIPCoreApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pDocTemplate;
	CIPCoreApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCoreApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CIPCoreApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCORE_H__29FBFB41_1E08_4632_AEA1_B82DB5B44550__INCLUDED_)
