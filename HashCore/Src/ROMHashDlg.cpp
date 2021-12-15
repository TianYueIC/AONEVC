// ROMEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\hashcore.h"
#include "..\include\ROMHashData.h"
#include "..\include\ROMHashDlg.h"
#include "..\..\Library\include\Utility.h"
#include <afxdlgs.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROMHashDlg dialog


CROMHashDlg::CROMHashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CROMHashDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CROMHashDlg)
	m_strDataFileName = _T("");
	m_strLayoutFileName = _T("");
	m_strLayoutFileName2 = _T("");
	m_strMessage = _T("");
	m_strVerilogFileName = _T("");
	m_strVerilog2FileName = _T("");
	//}}AFX_DATA_INIT
	char cTmp[100];
	GetProfileString("ROMHASH","DataFileName","C:\\WORK",cTmp,100);
	m_strDataFileName = cTmp;
	m_bSetup = FALSE;
	UpdateFileNames();
}


void CROMHashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CROMHashDlg)
	DDX_Text(pDX, IDC_DATAFILENAME, m_strDataFileName);
	DDX_Text(pDX, IDC_LAYOUTFILENAME, m_strLayoutFileName);
	DDX_Text(pDX, IDC_LAYOUTFILENAME2, m_strLayoutFileName2);
	DDX_Text(pDX, IDC_MESSAGE, m_strMessage);
	DDX_Text(pDX, IDC_VERILOGFILENAME, m_strVerilogFileName);
	DDX_Text(pDX, IDC_VERILOG2FILENAME, m_strVerilog2FileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CROMHashDlg, CDialog)
	//{{AFX_MSG_MAP(CROMHashDlg)
	ON_EN_CHANGE(IDC_DATAFILENAME, OnChangeDataFileName)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	ON_BN_CLICKED(IDC_OPEN_CODE_FILE, OnOpenCodeFile)
	ON_BN_CLICKED(IDC_WRITEDATA, OnWriteData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROMHashDlg message handlers

void CROMHashDlg::UpdateFileNames()
{
	CString str;
	GetFileNamePrefix(str,m_strDataFileName);
	m_strLayoutFileName = str;
	m_strLayoutFileName += "_rom.cif";
	m_strLayoutFileName2 = str;
	m_strLayoutFileName2 += "_const.cif";
	m_strVerilogFileName = str;
	m_strVerilogFileName += "_rom";
	m_strVerilogFileName += ".v";
	m_strVerilog2FileName = str;
	m_strVerilog2FileName += "_const";
	m_strVerilog2FileName += ".v";

}

BOOL	CROMHashDlg::OpenOutFiles()
{
	UpdateData();
	CString str;
	CString filename;
	CString errfile;

	filename =m_strVerilogFileName;
	if((m_fpVerilog = fopen(filename,"wb")) == NULL)errfile = filename;
	filename =m_strVerilog2FileName;
	if((m_fpVerilog2 = fopen(filename,"wb")) == NULL)errfile = filename;
	filename =m_strLayoutFileName;
	if((m_fpLayout = fopen(filename,"wb")) == NULL)errfile = filename;
	filename =m_strLayoutFileName2;
	if((m_fpLayout2 = fopen(filename,"wb")) == NULL)errfile = filename;
	
	if(!errfile.IsEmpty())
	{
		str.Format("写文件'%s'错误",filename);
		MessageBox(str);
		if(m_fpVerilog == NULL) fclose(m_fpVerilog);
		if(m_fpVerilog2 == NULL) fclose(m_fpVerilog2);
		if(m_fpLayout == NULL) fclose(m_fpLayout);
		if(m_fpLayout2 == NULL) fclose(m_fpLayout2);
		return FALSE;
	}

	return TRUE;
}

void CROMHashDlg::OnChangeDataFileName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	UpdateFileNames();
	UpdateData(FALSE);
}

void	CROMHashDlg::Message(CString & str)
{
	m_strMessage = str;
	UpdateData(FALSE);
}

BOOL CROMHashDlg::OpenDataFile(BOOL bRead)
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

void CROMHashDlg::OnOpenCodeFile()
{
	CFileDialog dlg(TRUE,NULL,"*.cod",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.cod");
	if(dlg.DoModal() == IDOK)
	{
		m_strDataFileName = dlg.GetPathName();
		UpdateFileNames();
		UpdateData(FALSE);
	}
}

void CROMHashDlg::OnGenerate() 
{
	if(OpenDataFile())
	{
		m_cROM.Read(m_fpData);
		if(OpenOutFiles())
		{
			WriteProfileString("ROME","DataFileName",m_strDataFileName);
			CString str="正在生成版图文件、仿真文件……";
			Message(str);
			m_cROM.WriteVerilog(m_fpVerilog);
			m_cROM.WriteVerilog2(m_fpVerilog2);
			m_cROM.WriteLayout(m_fpLayout);	
			m_cROM.WriteLayout2(m_fpLayout2);	
			str="生成版图文件、仿真文件完毕";
			Message(str);
			//上述函数中已经fclose
			//fclose(m_fpVerilog);
			//fclose(m_fpLayout);
			//fclose(m_fpLayout2);
		}
	}
}

void CROMHashDlg::OnWriteData() 
{
	if(OpenDataFile(FALSE))
	{
		//m_cROM.WriteData(m_fpData);
		CString str="写数据文件完毕";
		Message(str);
	}
}

void CROMHashDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CROMHashDlg::OnOK() 
{
	UpdateData(TRUE);
	WriteProfileString("ROME","DataFileName",m_strDataFileName);
	CDialog::OnOK();
}
