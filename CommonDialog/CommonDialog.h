// CommonDialog.h : main header file for the COMMONDIALOG application
//

#if !defined(AFX_COMMONDIALOG_H__939DD550_2943_443E_8A01_8C3F81D97F5C__INCLUDED_)
#define AFX_COMMONDIALOG_H__939DD550_2943_443E_8A01_8C3F81D97F5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogApp:
// See CommonDialog.cpp for the implementation of this class
//

class CCommonDialogApp : public CWinApp
{
public:
	CCommonDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommonDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCommonDialogApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMONDIALOG_H__939DD550_2943_443E_8A01_8C3F81D97F5C__INCLUDED_)
