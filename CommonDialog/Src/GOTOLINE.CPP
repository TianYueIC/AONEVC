// gotoline.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\gotoline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoLine dialog


CGotoLine::CGotoLine(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoLine::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoLine)
	m_iLineNumber = 0;
	//}}AFX_DATA_INIT
}


void CGotoLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoLine)
	DDX_Text(pDX, IDC_LINENUMBER, m_iLineNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoLine, CDialog)
	//{{AFX_MSG_MAP(CGotoLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoLine message handlers

void CGotoLine::OnOK() 
{
	UpdateData(TRUE);
	CDialog::OnOK();
}

