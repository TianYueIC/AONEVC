#if !defined(AFX_UECCIPCONFIGDLG_H__5CD7FD67_E19D_4024_8255_17278200DB89__INCLUDED_)
#define AFX_UECCIPCONFIGDLG_H__5CD7FD67_E19D_4024_8255_17278200DB89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// uECCIPConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CuECCIPConfigDlg dialog

class CuECCIPConfigDlg : public CDialog
{
// Construction
public:
	CuECCIPConfigDlg(CWnd* pParent = NULL);   // standard constructor
int	 GetType(){return m_iType;}
void GetProjectName(CString& path,CString& name)
	{path = m_strPathName; name = m_strProjectName;}
void SetName(CString& path,CString& name)
	{ m_strPathName = path; m_strProjectName = name;UpdateFileNames();}
	int		m_iType;
void SetType(int type)
{	
	m_bCheck1 = (type & 1) != 0;
	m_bCheck2 = (type & 2) != 0;
	m_bCheck3 = (type & 4) != 0;
	m_bCheck4 = (type & 8) != 0;
}
	CString m_strSourceFileName;
// Dialog Data
	//{{AFX_DATA(CuECCIPConfigDlg)
	enum { IDD = IDD_UECCIPCORE_CONFIG };
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

void UpdateFileNames();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CuECCIPConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CuECCIPConfigDlg)
	afx_msg void OnChangeSourcePathName();
	afx_msg void OnChangeProjectName();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UECCIPCONFIGDLG_H__5CD7FD67_E19D_4024_8255_17278200DB89__INCLUDED_)
