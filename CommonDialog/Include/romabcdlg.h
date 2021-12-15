// ASICUtilityDlg.h : header file
//

#if !defined(AFX_ASICUTILITYDLG_H__06DF59C6_AEFE_42CF_8C4F_3139CB058382__INCLUDED_)
#define AFX_ASICUTILITYDLG_H__06DF59C6_AEFE_42CF_8C4F_3139CB058382__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CROMabcDlg dialog
class CROMabcDlg : public CDialog
{
	CROMSetupDlg romset;
	BOOL	m_bNEC;
	BOOL	m_bH;
// Construction
public:
	CROMabcDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL	m_bSetup;
// Dialog Data
	//{{AFX_DATA(CROMabcDlg)
	enum { IDD = IDD_ROMABC_DLG };
	CString	m_csDataFileName;
	CString	m_csLayoutFileName;
	CString	m_csVerilogFileName;
	CString	m_csMessage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROMabcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	FILE	*m_fpData;
	FILE	*m_fpVerilog;
	FILE	*m_fpLayout;
	CString m_strModuleName;
	CROMData m_cROM;
	BOOL	OpenDataFile(BOOL bRead = TRUE);
	BOOL	OpenOutFiles();
	void	UpdateFileNames();
	void	Message(CString & str);
	BOOL	CheckSize();
	// Generated message map functions
	//{{AFX_MSG(CROMabcDlg)
	virtual void OnOK();
	afx_msg void OnGenerate();
	afx_msg void OnRomSetup();
	afx_msg void OnChangeDataFileName();
	afx_msg void OnBrowser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASICUTILITYDLG_H__06DF59C6_AEFE_42CF_8C4F_3139CB058382__INCLUDED_)
