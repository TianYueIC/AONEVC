#if !defined(AFX_EMULATORCONFIGDLG_H__8CDF9A77_F4A9_4404_A8AB_2A666FC3C06F__INCLUDED_)
#define AFX_EMULATORCONFIGDLG_H__8CDF9A77_F4A9_4404_A8AB_2A666FC3C06F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// emulatorconfigdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmulatorConfigDlg dialog

class CEmulatorConfigDlg : public CDialog
{
// Construction
public:
	CEmulatorConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmulatorConfigDlg)
	enum { IDD = IDD_DSPEMULATOR_CONFIG };
	CString	m_strDescription;
	int		m_iConfig;
	BOOL	m_bRegDump;
	int		m_iAddr;
	int		m_iValue;
	BOOL	m_bBreakPoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmulatorConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmulatorConfigDlg)
	virtual void OnOK();
	afx_msg void OnCloseupRpList();
	afx_msg void OnCloseupConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMULATORCONFIGDLG_H__8CDF9A77_F4A9_4404_A8AB_2A666FC3C06F__INCLUDED_)
