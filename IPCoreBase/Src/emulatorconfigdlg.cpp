// emulatorconfigdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\DSPCore.h"
#include "..\include\emulatorconfigdlg.h"

#include "..\..\common\Include\xpthread.h"
#include "..\..\common\Include\corethread.h"
#include "..\..\emulatorcore\Include\emulatorcore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmulatorConfigDlg dialog

static char *pDescriptions[] = {
			"DES 端口共占用五个，从指定端口开始依次为\r\n"
			"    DES_K0(写)   : 设置密钥低32位 \r\n"
			"    DES_K1(写)   : 设置密钥高32位 \r\n"
			"    DES_P0(读/写): 读写加解密数据低32位\r\n"
			"    DES_P1(读/写): 读写加解密数据高32位\r\n"
			"    DES_OP(写)   : 执行密钥左、右移动及一轮函数运算",
};

CEmulatorConfigDlg::CEmulatorConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmulatorConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmulatorConfigDlg)
	m_strDescription = pDescriptions[0];
	m_iConfig = 0;
	m_bRegDump = FALSE;
	m_iAddr = 0;
	m_iValue = 0;
	m_bBreakPoint = FALSE;
	//}}AFX_DATA_INIT
}


void CEmulatorConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmulatorConfigDlg)
	DDX_Text(pDX, IDC_DESCRIPTION, m_strDescription);
	DDX_CBIndex(pDX, IDC_CONFIG, m_iConfig);
	DDX_Check(pDX, IDC_REG_DUMP, m_bRegDump);
	DDX_Text(pDX, IDC_RAMADDR, m_iAddr);
	DDX_Text(pDX, IDC_RAMCONT, m_iValue);
	DDX_Check(pDX, IDC_BREAKPOINT, m_bBreakPoint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmulatorConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CEmulatorConfigDlg)
	ON_CBN_CLOSEUP(IDC_RP_LIST, OnCloseupRpList)
	ON_CBN_CLOSEUP(IDC_CONFIG, OnCloseupConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmulatorConfigDlg message handlers

void CEmulatorConfigDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	g_pEmulator->m_bRegDump = m_bRegDump;
	if(m_bBreakPoint) 
		g_pEmulator->SetRAMBreakPoint(m_iAddr,m_iValue);
	else 
		g_pEmulator->SetRAMBreakPoint(-1,0);
	CDialog::OnOK();
}

void CEmulatorConfigDlg::OnCloseupRpList() 
{
	// TODO: Add your control notification handler code here
	
}

void CEmulatorConfigDlg::OnCloseupConfig() 
{
	UpdateData(TRUE);
	m_strDescription = pDescriptions[m_iConfig];
	UpdateData(FALSE);
}
