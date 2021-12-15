#if !defined(AFX_ROMDIALOG_H__1495CBDE_A47E_48DE_A604_19D4520543AC__INCLUDED_)
#define AFX_ROMDIALOG_H__1495CBDE_A47E_48DE_A604_19D4520543AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// romdialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ROMDialog dialog
#include "Common.h"
#include "ROMEData.h"
class ROMDialog : public CDialog
{
// Construction
public:
	ROMDialog(CWnd* pParent = NULL);   // standard constructor

	BOOL	m_bSetup;
	FILE	*m_fpData;
	FILE	*m_fpVerilog;
	FILE	*m_fpLayout;
	CROMEData m_cROM;
// Dialog Data
	//{{AFX_DATA(ROMDialog)
	enum { IDD = IDD_ROM_DIALOG };
	CString	m_strDataFileName;
	CString	m_strLayoutFileName;
	CString	m_strMessage;
	CString	m_strVerilogFileName;
	BOOL	m_bNEC;
	CString	m_strModuleName;
	BOOL	m_bHead;
	//}}AFX_DATA

	void	Message(CString & str);
	BOOL	OpenOutFiles();
	void	UpdateFileNames();
	BOOL	OpenDataFile(BOOL bRead = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ROMDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ROMDialog)
	afx_msg void OnOpenCodeFile();
	afx_msg void OnGenerate();
	afx_msg void OnCheckNec();
	afx_msg void OnChangeDatafilename();
	afx_msg void OnCheckHead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROMDIALOG_H__1495CBDE_A47E_48DE_A604_19D4520543AC__INCLUDED_)
