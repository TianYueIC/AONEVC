#if !defined(AFX_ROMSETUP_H__3A2A42B6_5DBA_4EEF_B9C8_99EE4743B24E__INCLUDED_)
#define AFX_ROMSETUP_H__3A2A42B6_5DBA_4EEF_B9C8_99EE4743B24E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RomSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CROMSetupDlg dialog

class CROMSetupDlg : public CDialog
{
// Construction
public:
	CROMSetupDlg(CWnd* pParent = NULL);   // standard constructor
	int		m_iRows;
	BOOL	m_bNEC;
	BOOL    m_bH;
// Dialog Data
	//{{AFX_DATA(CROMSetupDlg)
	enum { IDD = IDD_ROMSETUP };
	int		m_iColGap;
	int		m_iDHigh;
	int		m_iDWidth;
	int		m_iGndGap;
	int		m_iRowGap;
	int		m_iYGap;
	CString	m_csCaseSelect;
	int		m_iROMBlocks;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROMSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void GetRegistry(CString &strCase);
	void WriteRegistry();
	// Generated message map functions
	//{{AFX_MSG(CROMSetupDlg)
	virtual void OnOK();
	afx_msg void OnSelchangeCaseselect();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROMSETUP_H__3A2A42B6_5DBA_4EEF_B9C8_99EE4743B24E__INCLUDED_)
