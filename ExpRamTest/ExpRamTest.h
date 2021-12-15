// ExpRamTest.h : main header file for the EXPRAMTEST application
//

#if !defined(AFX_EXPRAMTEST_H__0465A088_FEDF_4C63_9E27_FF610DEA15E5__INCLUDED_)
#define AFX_EXPRAMTEST_H__0465A088_FEDF_4C63_9E27_FF610DEA15E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExpRamTestApp:
// See ExpRamTest.cpp for the implementation of this class
//

class CExpRamTestApp : public CWinApp
{
public:
	CExpRamTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpRamTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExpRamTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPRAMTEST_H__0465A088_FEDF_4C63_9E27_FF610DEA15E5__INCLUDED_)
