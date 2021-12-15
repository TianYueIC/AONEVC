// ASICUtilityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\romdialog.h"
#include "..\include\RomSetupDlg.h"
#include "..\include\ROMDATA.h"
#include "..\include\ROMabcDlg.h"
#include "..\..\Library\include\Utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROMabcDlg dialog

CROMabcDlg::CROMabcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CROMabcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CROMabcDlg)
	m_csDataFileName = _T("");
	m_csLayoutFileName = _T("");
	m_csVerilogFileName = _T("");
	m_csMessage = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bNEC = FALSE;
	CWinApp* pWinApp = AfxGetApp();
	
	m_csDataFileName =pWinApp->GetProfileString("ROMABC","DataFileName","C:\\WORK");
	m_bSetup = FALSE;
	UpdateFileNames();

	m_cROM.m_iColGap      = romset.m_iColGap;
	m_cROM.m_iDHigh       = romset.m_iDHigh;
	m_cROM.m_iDWidth      = romset.m_iDWidth;
	m_cROM.m_iGndGap      = romset.m_iGndGap;
	m_cROM.m_iRowGap      = romset.m_iRowGap;
	m_cROM.m_iYGap        = romset.m_iYGap;
	m_cROM.m_iRows   	  = romset.m_iRows;
	m_cROM.m_iROMBlocks	  = romset.m_iROMBlocks;
	m_cROM.m_RomType	  = romset.m_csCaseSelect[3];
	m_bNEC = m_cROM.m_bNEC = romset.m_bNEC;
	m_cROM.GetMessage(m_csMessage);
}

void CROMabcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CROMabcDlg)
	DDX_Text(pDX, IDC_DATAFILENAME, m_csDataFileName);
	DDX_Text(pDX, IDC_LAYOUTFILENAME, m_csLayoutFileName);
	DDX_Text(pDX, IDC_VERILOGFILENAME, m_csVerilogFileName);
	DDX_Text(pDX, IDC_MESSAGE, m_csMessage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CROMabcDlg, CDialog)
	//{{AFX_MSG_MAP(CROMabcDlg)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	ON_BN_CLICKED(IDC_ROMSETUP, OnRomSetup)
	ON_EN_CHANGE(IDC_DATAFILENAME, OnChangeDataFileName)
	ON_BN_CLICKED(IDC_BROWSER, OnBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROMabcDlg message handlers


void CROMabcDlg::OnOK() 
{
	UpdateData(TRUE);
	CWinApp* pWinApp = AfxGetApp();

	pWinApp->WriteProfileString("ROMABC","DataFileName",m_csDataFileName);
	CDialog::OnOK();
}

void CROMabcDlg::OnGenerate() 
{
	UpdateData(TRUE);
	if(	m_bSetup == FALSE ) 
	{
		CString str="�����趨ROM����";
		Message(str);
		return ;
	}
	if(OpenDataFile())
	{
		m_cROM.Read(m_fpData);
		if(CheckSize() == FALSE) return;
		if(OpenOutFiles())
		{
			CWinApp* pWinApp = AfxGetApp();
			pWinApp->WriteProfileString("ROMABC","DataFileName",m_csDataFileName);
			CString str="�������ɰ�ͼ�ļ��������ļ�����";
			Message(str);
			m_cROM.SetModuleName(m_strModuleName);
			m_cROM.GenVerilog(m_fpVerilog);
			m_cROM.GenLayout(m_fpLayout);	
			str="���ɰ�ͼ�ļ��������ļ����";
			Message(str);
		}
	}
}

BOOL CROMabcDlg::OpenDataFile(BOOL bRead)
{
	UpdateData();
	CString str;
	if(bRead) m_fpData = fopen(m_csDataFileName,"rb");
	else m_fpData = fopen(m_csDataFileName,"wb");
	if(m_fpData == NULL)
	{
		if(bRead)str.Format("���ļ�'%s'����",m_csDataFileName);
		else str.Format("д�ļ�'%s'����",m_csDataFileName);
		MessageBox(str);
		return FALSE;
	}
	return TRUE;
}

BOOL	CROMabcDlg::OpenOutFiles()
{
	UpdateData();
	CString str;
	CString filename;
	filename =m_csVerilogFileName;
	m_fpVerilog = fopen(filename,"wb");
	if(m_fpVerilog == NULL)
	{
		str.Format("д�ļ�'%s'����",filename);
		MessageBox(str);
		return FALSE;
	}
	filename =m_csLayoutFileName;
	m_fpLayout = fopen(filename,"wb");
	if(m_fpLayout == NULL)
	{
		str.Format("д�ļ�'%s'����",filename);
		MessageBox(str);
		fclose(m_fpVerilog);
		return FALSE;
	}
	return TRUE;
}

void	CROMabcDlg::Message(CString & str)
{
	m_csMessage = str;
	UpdateData(FALSE);
}

BOOL	CROMabcDlg::CheckSize()
{
	CString str;
	int size = m_cROM.GetSize();
	int calSize = m_cROM.GetCalSize();
	BOOL rB = TRUE;
	if(calSize > size)
		str.Format("������龯�棺���ݴ�С%dС����������%d",size,calSize);
	else if(calSize == size)
		str.Format("�������ͨ�������ݴ�С%d������������%d",size,calSize);
	else 
	{
		str.Format("�������������ݴ�СΪ%d������������%d",size,calSize);
		rB = FALSE;
	}
	Message(str);
	return rB;
}

void CROMabcDlg::OnRomSetup() 
{
	int r = romset.DoModal();
	if(r == IDOK)
	{
		m_cROM.m_iColGap      = romset.m_iColGap;
		m_cROM.m_iDHigh       = romset.m_iDHigh;
		m_cROM.m_iDWidth      = romset.m_iDWidth;
		m_cROM.m_iGndGap      = romset.m_iGndGap;
		m_cROM.m_iRowGap      = romset.m_iRowGap;
		m_cROM.m_iYGap        = romset.m_iYGap;
		m_cROM.m_iRows   	  = romset.m_iRows;
		m_cROM.m_iROMBlocks	  = romset.m_iROMBlocks;
		m_cROM.m_RomType	  = romset.m_csCaseSelect[3];
		m_bNEC = m_cROM.m_bNEC= romset.m_bNEC;
		m_bH   = m_cROM.m_bH  = romset.m_bH;
		m_cROM.GetMessage(m_csMessage);
		UpdateFileNames();
		UpdateData(FALSE);
		m_bSetup = TRUE;
	}
}

void CROMabcDlg::UpdateFileNames()
{
	CString str;
	GetFileNamePrefix(str,m_csDataFileName);
	if(m_bNEC) str += "_NEC";
	m_csLayoutFileName = str;
	m_csLayoutFileName += ".cif";
	m_csVerilogFileName = str;
	m_csVerilogFileName += ".v";
	int pos = str.ReverseFind('\\');
	m_strModuleName = str.Mid(pos+1);
}

void CROMabcDlg::OnChangeDataFileName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}

void CROMabcDlg::OnBrowser() 
{
	CFileDialog dlg(TRUE,NULL,"*.cod",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.cod");
	if(dlg.DoModal() == IDOK)
	{
		m_csDataFileName = dlg.GetPathName();
		UpdateFileNames();
		UpdateData(FALSE);
	}
}
