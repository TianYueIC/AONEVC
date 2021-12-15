// romdialog.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\romdialog.h"
#include "..\..\Library\include\Utility.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ROMDialog dialog


ROMDialog::ROMDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ROMDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ROMDialog)
	m_strDataFileName = _T("");
	m_strLayoutFileName = _T("");
	m_strMessage = _T("");
	m_strVerilogFileName = _T("");
	m_bNEC = TRUE;
	m_bHead = TRUE;
	m_strModuleName = _T("");
	//}}AFX_DATA_INIT
	CWinApp* pWinApp = AfxGetApp();
	m_strDataFileName =pWinApp->GetProfileString("ROME","DataFileName","C:\\WORK");
}


void ROMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ROMDialog)
	DDX_Text(pDX, IDC_DATAFILENAME, m_strDataFileName);
	DDX_Text(pDX, IDC_LAYOUTFILENAME, m_strLayoutFileName);
	DDX_Text(pDX, IDC_MESSAGE, m_strMessage);
	DDX_Text(pDX, IDC_VERILOGFILENAME, m_strVerilogFileName);
	DDX_Check(pDX, IDC_CHECK_NEC, m_bNEC);
	DDX_Text(pDX, IDC_MODULENAME, m_strModuleName);
	DDX_Check(pDX, IDC_CHECK_HEAD, m_bHead);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ROMDialog, CDialog)
	//{{AFX_MSG_MAP(ROMDialog)
	ON_BN_CLICKED(IDC_OPEN_CODE_FILE, OnOpenCodeFile)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	ON_BN_CLICKED(IDC_CHECK_NEC, OnCheckNec)
	ON_EN_CHANGE(IDC_DATAFILENAME, OnChangeDatafilename)
	ON_BN_CLICKED(IDC_CHECK_HEAD, OnCheckHead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ROMDialog message handlers

void ROMDialog::OnOpenCodeFile()
{
	//CFileDialog dlg(TRUE,NULL,"*.cod",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.cod|*.cod|*.*|*.*||");
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.*|*.*||");
	if(dlg.DoModal() == IDOK)
	{
		m_strDataFileName = dlg.GetPathName();
		UpdateFileNames();
		UpdateData(FALSE);
	}
}

void ROMDialog::OnGenerate() 
{
	if(OpenDataFile())
	{
		m_cROM.ReadCode(m_fpData);
		if(OpenOutFiles())
		{
			CWinApp* pWinApp = AfxGetApp();
			pWinApp->WriteProfileString("ROME","DataFileName",m_strDataFileName);
			CString str="正在生成版图文件、仿真文件……";
			Message(str);
			if (FALSE == m_bHead)
			{
				m_cROM.WriteVerilogArray(m_fpVerilog);
				m_cROM.WriteLayout(m_fpLayout);	
			}
			else if(m_bNEC) 
			{
				m_cROM.WriteNECVerilog(m_fpVerilog);
				m_cROM.WriteNECLayout(m_fpLayout);	
			}
			else
			{
				m_cROM.WriteVerilog(m_fpVerilog);
				m_cROM.WriteLayout(m_fpLayout);	
			}
			str="生成版图文件、仿真文件完毕";
			Message(str);
		}
	}
}
BOOL ROMDialog::OpenOutFiles()
{
	UpdateData();
	CString str;
	CString filename;
	filename =m_strVerilogFileName;
	m_fpVerilog = fopen(filename,"wb");
	if(m_fpVerilog == NULL)
	{
		str.Format("写文件'%s'错误",filename);
		MessageBox(str);
		return FALSE;
	}
	filename =m_strLayoutFileName;
	m_fpLayout = fopen(filename,"wb");
	if(m_fpLayout == NULL)
	{
		str.Format("写文件'%s'错误",filename);
		MessageBox(str);
		fclose(m_fpVerilog);
		return FALSE;
	}
	return TRUE;
}
void ROMDialog::Message(CString & str)
{
	m_strMessage = str;
	UpdateData(FALSE);
}
BOOL ROMDialog::OpenDataFile(BOOL bRead)
{
	UpdateData();
	CString str;
	if(bRead) m_fpData = fopen(m_strDataFileName,"rb");
	else m_fpData = fopen(m_strDataFileName,"wb");
	if(m_fpData == NULL)
	{
		if(bRead)str.Format("读文件'%s'错误",m_strDataFileName);
		else str.Format("写文件'%s'错误",m_strDataFileName);
		MessageBox(str);
		return FALSE;
	}
	return TRUE;
}
void ROMDialog::UpdateFileNames()
{
	CString str;
	str = m_strDataFileName;
	int p1 = str.ReverseFind('.');
	int p0 = str.ReverseFind('\\');
	if(p0 < 0) p0 = 0;
	else p0 ++;
	if(p1 > p0) m_strModuleName = str.Mid(p0,p1-p0);
	else m_strModuleName = str.Mid(p0);
	GetFileNamePrefix(str,m_strDataFileName);
	if(m_bNEC) str += "_NEC";
	m_strLayoutFileName = str;
	m_strLayoutFileName += ".cif";
	m_strVerilogFileName = str;
	m_strVerilogFileName += ".v";
}

void ROMDialog::OnCheckNec() 
{
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}

void ROMDialog::OnChangeDatafilename() 
{
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}

void ROMDialog::OnCheckHead() 
{
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}
