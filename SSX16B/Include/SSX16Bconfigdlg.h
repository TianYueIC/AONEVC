#if !defined(AFX_SSX16BCONFIGDLG_H__0C77C4E3_A6B5_4B63_BF3E_0310212466EC__INCLUDED_)
#define AFX_SSX16BCONFIGDLG_H__0C77C4E3_A6B5_4B63_BF3E_0310212466EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SSX16Bconfigdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSSX16BConfigDlg dialog

class CSSX16BConfigDlg : public CDialog
{
// Construction
public:
	CSSX16BConfigDlg(CWnd* pParent = NULL);   // standard constructor
void UpdateFileNames();
int	 GetType(){return m_iType;}
void GetProjectName(CString& path,CString& name)
	{path = m_strPathName; name = m_strProjectName;}
void Set(CString& path,CString& name,int type);
// Dialog Data
	//{{AFX_DATA(CSSX16BConfigDlg)
	enum { IDD = IDD_SSX16B_CONFIG };
	BOOL	m_bCheck1;
	BOOL	m_bCheck2;
	BOOL	m_bCheck3;
	BOOL	m_bCheck4;
	CString	m_strCodeFileName;
	CString	m_strDebugFileName;
	CString	m_strListFileName;
	CString	m_strProjectName;
	CString	m_strPathName;
	//}}AFX_DATA

	int		m_iType;
	CString m_strSourceFileName;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSX16BConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSSX16BConfigDlg)
	afx_msg void OnOK();
	afx_msg void OnChangeSourcePathName();
	afx_msg void OnChangeProjectName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSX16BCONFIGDLG_H__0C77C4E3_A6B5_4B63_BF3E_0310212466EC__INCLUDED_)
