// ProtocolTest.h : main header file for the PROTOCOLTEST application
//

#if !defined(AFX_PROTOCOLTEST_H__A88A2F57_3A36_4D72_9D54_62FBA6C7B7AE__INCLUDED_)
#define AFX_PROTOCOLTEST_H__A88A2F57_3A36_4D72_9D54_62FBA6C7B7AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProtocolTestApp:
// See ProtocolTest.cpp for the implementation of this class
//

class CProtocolTestApp : public CWinApp
{
public:
	CProtocolTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProtocolTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOLTEST_H__A88A2F57_3A36_4D72_9D54_62FBA6C7B7AE__INCLUDED_)
