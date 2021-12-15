#if !defined(AFX_ROMEDLG_H__1F20E647_4D44_4045_ABFD_5706641DD612__INCLUDED_)
#define AFX_ROMEDLG_H__1F20E647_4D44_4045_ABFD_5706641DD612__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ROMEDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CROMHashDlg dialog

class CROMHashDlg : public CDialog
{
// Construction
public:
	CROMHashDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL	m_bSetup;
	FILE	*m_fpData;
	FILE	*m_fpVerilog;
	FILE	*m_fpVerilog2;
	FILE	*m_fpLayout;
	FILE	*m_fpLayout2;
	CROMHashData m_cROM;

// Dialog Data
	//{{AFX_DATA(CROMHashDlg)
	enum { IDD = IDD_ROME_DIALOG };
	CString	m_strDataFileName;
	CString	m_strLayoutFileName;
	CString	m_strLayoutFileName2;
	CString	m_strMessage;
	CString	m_strVerilogFileName;
	CString	m_strVerilog2FileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROMHashDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void	Message(CString & str);
	BOOL	OpenOutFiles();
	void	UpdateFileNames();
	BOOL	OpenDataFile(BOOL bRead = TRUE);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CROMHashDlg)
	afx_msg void OnChangeDataFileName();
	afx_msg void OnGenerate();
	afx_msg void OnOpenCodeFile();
	afx_msg void OnWriteData();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROMEDLG_H__1F20E647_4D44_4045_ABFD_5706641DD612__INCLUDED_)
