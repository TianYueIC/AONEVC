// HashCore.h : main header file for the HASHCORE application
//

#if !defined(AFX_HASHCORE_H__FCD3771E_C73E_4841_BC48_6A97C2365DFB__INCLUDED_)
#define AFX_HASHCORE_H__FCD3771E_C73E_4841_BC48_6A97C2365DFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHashCoreApp:
// See HashCore.cpp for the implementation of this class
//

class CHashCoreApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pDocTemplate;
	CHashCoreApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHashCoreApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHashCoreApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HASHCORE_H__FCD3771E_C73E_4841_BC48_6A97C2365DFB__INCLUDED_)
