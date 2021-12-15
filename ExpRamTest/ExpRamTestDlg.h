// ExpRamTestDlg.h : header file
//

#if !defined(AFX_EXPRAMTESTDLG_H__260BC6F6_C9A8_429B_84E8_F139E3709114__INCLUDED_)
#define AFX_EXPRAMTESTDLG_H__260BC6F6_C9A8_429B_84E8_F139E3709114__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExpRamTestDlg dialog

class CExpRamTestDlg : public CDialog
{
// Construction
public:
	CExpRamTestDlg(CWnd* pParent = NULL);	// standard constructor
	void SetList(bool isok,int index,const char * name);
// Dialog Data
	//{{AFX_DATA(CExpRamTestDlg)
	enum { IDD = IDD_EXPRAMTEST_DIALOG };
	CListBox	m_ListBox;
	CString	m_strDataFileName;
	CString	m_strParamFileName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpRamTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExpRamTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowser();
	virtual void OnOK();
	afx_msg void OnBrowserParam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPRAMTESTDLG_H__260BC6F6_C9A8_429B_84E8_F139E3709114__INCLUDED_)
