// RomSetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Afxwin.h"
#include "..\include\romdialog.h"
#include "..\include\RomSetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROMSetupDlg dialog


CROMSetupDlg::CROMSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CROMSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CROMSetupDlg)
	m_iColGap = 0;
	m_iDHigh = 0;
	m_iDWidth = 0;
	m_iGndGap = 0;
	m_iRowGap = 0;
	m_iYGap = 0;
	m_csCaseSelect = _T("");
	m_iROMBlocks = 0;
	//}}AFX_DATA_INIT
	CWinApp* pApp = AfxGetApp();
	m_csCaseSelect = pApp->GetProfileString("ROMSETUP","CaseSelect","ROMA");
	GetRegistry(m_csCaseSelect);
	char c = m_csCaseSelect[3];
	if(c > 'C' || c < 'A') c = 'A';
	int i = c - 'A';
	m_iRows = 8 << i;
	m_bNEC = m_bH = false;
}


void CROMSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CROMSetupDlg)
	DDX_Text(pDX, IDC_COLGAP, m_iColGap);
	DDX_Text(pDX, IDC_DHIGH, m_iDHigh);
	DDX_Text(pDX, IDC_DWIDTH, m_iDWidth);
	DDX_Text(pDX, IDC_GNDGAP, m_iGndGap);
	DDX_Text(pDX, IDC_ROWGAP, m_iRowGap);
	DDX_Text(pDX, IDC_YGAP, m_iYGap);
	DDX_CBString(pDX, IDC_CASESELECT, m_csCaseSelect);
	DDX_Text(pDX, IDC_ROMSIZE, m_iROMBlocks);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CROMSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CROMSetupDlg)
	ON_CBN_SELCHANGE(IDC_CASESELECT, OnSelchangeCaseselect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROMSetupDlg message handlers

void CROMSetupDlg::OnOK() 
{
	UpdateData(TRUE);
	char c = m_csCaseSelect[3];
	if(c > 'C' || c < 'A') c = 'A';
	int i = c - 'A';
	m_iRows = 8 << i;
	if(m_csCaseSelect.GetLength() > 5) 
	{	
		c = m_csCaseSelect[5];
		if(c == 'N') m_bNEC = true;
		else m_bNEC = false;
		if(c == 'h') m_bH = true;
		else m_bH = false;
	}
	WriteRegistry();
	CDialog::OnOK();
}

void CROMSetupDlg::OnSelchangeCaseselect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str = m_csCaseSelect;
	GetRegistry(str);
	UpdateData(FALSE);
}

void CROMSetupDlg::GetRegistry(CString &strCase)
{
	CWinApp* pApp = AfxGetApp();
	CString str;
	str = "DepWidth_";
	str += strCase;
	m_iDWidth = pApp->GetProfileInt("ROMSETUP",str,14);
	str = "DepHigh_";
	str += strCase;
	m_iDHigh = pApp->GetProfileInt("ROMSETUP",str,10);
	str = "ColumGap_";
	str += strCase;
	m_iColGap = pApp->GetProfileInt("ROMSETUP",str,0);
	str = "RowGap_";
	str += strCase;
	m_iRowGap = pApp->GetProfileInt("ROMSETUP",str,0);
	str = "GroundGap_";
	str += strCase;
	m_iGndGap = pApp->GetProfileInt("ROMSETUP",str,42);
	str = "YOutputGap_";
	str += strCase;
	m_iYGap = pApp->GetProfileInt("ROMSETUP",str,10);
	str = "ROMBlocks_";
	str += strCase;
	m_iROMBlocks = pApp->GetProfileInt("ROMSETUP",str,1);
}
void CROMSetupDlg::WriteRegistry()
{
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileString("ROMSETUP","CaseSelect",m_csCaseSelect);
	CString str;
	str = "DepWidth_";
	str += m_csCaseSelect;
	pApp->WriteProfileInt("ROMSETUP", str, m_iDWidth);
	str = "DepHigh_";
	str += m_csCaseSelect;
	pApp->WriteProfileInt("ROMSETUP", str, m_iDHigh);
	str = "ColumGap_";
	str += m_csCaseSelect;
	pApp->WriteProfileInt("ROMSETUP",str,m_iColGap);
	str = "RowGap_";
	str += m_csCaseSelect;
	pApp->WriteProfileInt("ROMSETUP",str,m_iRowGap);
	str = "GroundGap_";
	str += m_csCaseSelect;
	pApp->WriteProfileInt("ROMSETUP",str,m_iGndGap);
	str = "YOutputGap_";
	str += m_csCaseSelect;
	pApp->WriteProfileInt("ROMSETUP",str,m_iYGap);
	str = "ROMBlocks_";
	str += m_csCaseSelect;
	pApp->WriteProfileInt("ROMSETUP",str,m_iROMBlocks);
}


void CROMSetupDlg::OnCancel() 
{

	CDialog::OnOK();
}
