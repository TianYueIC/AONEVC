// dspcoreconfigdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\DSPCore.h"
#include "..\include\dspcoreconfigdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreConfigDlg dialog


CDSPCoreConfigDlg::CDSPCoreConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDSPCoreConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDSPCoreConfigDlg)
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


void CDSPCoreConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDSPCoreConfigDlg)
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


BEGIN_MESSAGE_MAP(CDSPCoreConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CDSPCoreConfigDlg)
	ON_EN_CHANGE(IDC_SOURCEPATHNAME, OnChangeSourcePathName)
	ON_EN_CHANGE(IDC_PROJECTNAME, OnChangeProjectName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreConfigDlg message handlers
void CDSPCoreConfigDlg::Set(CString& path,CString& name,int type)
{
	m_strPathName = path; 
	m_strProjectName = name;
	m_bCheck1 = (m_iType & 1) != 0;//������
	m_bCheck3 = (m_iType & 2) != 0;//�м�
	m_bCheck2 = (m_iType & 4) != 0;//��β
	m_bCheck4 = (m_iType & 8) != 0;//��ַ
	UpdateFileNames();
}
void CDSPCoreConfigDlg::OnOK() 
{
	UpdateData(TRUE);
	m_iType = 0;
	if(m_bCheck1) m_iType |= 1;//������
	if(m_bCheck3) m_iType |= 2;//�м�
	if(m_bCheck2) m_iType |= 4;//��β
	if(m_bCheck4) m_iType |= 8;//��ַ
	CDialog::OnOK();
}

void CDSPCoreConfigDlg::UpdateFileNames()
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


void CDSPCoreConfigDlg::OnChangeSourcePathName() 
{
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}

void CDSPCoreConfigDlg::OnChangeProjectName() 
{
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}
