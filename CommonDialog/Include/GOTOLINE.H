#if !defined(AFX_GOTOLINE_H__19589FA9_6629_4D72_9365_3A20E09BB6DC__INCLUDED_)
#define AFX_GOTOLINE_H__19589FA9_6629_4D72_9365_3A20E09BB6DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gotoline.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGotoLine dialog
#include "Common.h"
class CGotoLine : public CDialog
{
// Construction
public:
	CGotoLine(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGotoLine)
	enum { IDD = IDD_GOTOLINE_DIALOG };
	int		m_iLineNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGotoLine)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGotoLine)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTOLINE_H__19589FA9_6629_4D72_9365_3A20E09BB6DC__INCLUDED_)
