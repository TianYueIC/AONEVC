// IPCoreconfigdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\IPCore.h"
#include "..\include\IPCoreconfigdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPCoreConfigDlg dialog


CIPCoreConfigDlg::CIPCoreConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPCoreConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPCoreConfigDlg)
	m_bCheck1 = FALSE;
	m_bCheck2 = FALSE;
	m_bCheck3 = FALSE;
	m_bCheck4 = FALSE;
	m_strCodeFileName = _T("");
	m_strDebugFileName = _T("");
	m_strListFileName = _T("");
	m_strProjectName = _T("");
	m_strPathName = _T("");
	//}}AFX_DATA_INIT
}


void CIPCoreConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPCoreConfigDlg)
	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
	DDX_Check(pDX, IDC_CHECK2, m_bCheck2);
	DDX_Check(pDX, IDC_CHECK3, m_bCheck3);
	DDX_Check(pDX, IDC_CHECK4, m_bCheck4);
	DDX_Text(pDX, IDC_CODEFILENAME, m_strCodeFileName);
	DDX_Text(pDX, IDC_DEBUGFILENAME, m_strDebugFileName);
	DDX_Text(pDX, IDC_LISTFILENAME, m_strListFileName);
	DDX_Text(pDX, IDC_PROJECTNAME, m_strProjectName);
	DDX_Text(pDX, IDC_SOURCEPATHNAME, m_strPathName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPCoreConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CIPCoreConfigDlg)
	ON_EN_CHANGE(IDC_SOURCEPATHNAME, OnChangeSourcePathName)
	ON_EN_CHANGE(IDC_PROJECTNAME, OnChangeProjectName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCoreConfigDlg message handlers
void CIPCoreConfigDlg::Set(CString& path,CString& name,int type)
{
	m_strPathName = path; 
	m_strProjectName = name;
	m_bCheck1 = (m_iType & 1) != 0;//二进制
	m_bCheck3 = (m_iType & 2) != 0;//行间
	m_bCheck2 = (m_iType & 4) != 0;//行尾
	m_bCheck4 = (m_iType & 8) != 0;//地址
	UpdateFileNames();
}
void CIPCoreConfigDlg::OnOK() 
{
	UpdateData(TRUE);
	m_iType = 0;
	if(m_bCheck1) m_iType |= 1;//二进制
	if(m_bCheck3) m_iType |= 2;//行间
	if(m_bCheck2) m_iType |= 4;//行尾
	if(m_bCheck4) m_iType |= 8;//地址
	CDialog::OnOK();
}

void CIPCoreConfigDlg::UpdateFileNames()
{
	CString str;
	str = m_strPathName;
	str += "\\";
	str += m_strProjectName;
	m_strSourceFileName = str;

	m_strListFileName = str;
	m_strListFileName += ".lst";
	m_strCodeFileName = str;
	m_strCodeFileName += ".cod";
	m_strDebugFileName = str;
	m_strDebugFileName += ".dbg";
}


void CIPCoreConfigDlg::OnChangeSourcePathName() 
{
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}

void CIPCoreConfigDlg::OnChangeProjectName() 
{
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}
