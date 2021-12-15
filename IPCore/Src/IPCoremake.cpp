// IPCoremake.cpp : implementation file
//

#include "stdafx.h"
#include "..\IPCore.h"
#include "..\include\IPCoremake.h"
#include "..\include\MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPCoreMake

IMPLEMENT_DYNCREATE(CIPCoreMake, CDocument)

CIPCoreMake::CIPCoreMake()
{
}

BOOL CIPCoreMake::OnNewDocument()
{
	return FALSE;
}

CIPCoreMake::~CIPCoreMake()
{
}


BEGIN_MESSAGE_MAP(CIPCoreMake, CDocument)
	//{{AFX_MSG_MAP(CIPCoreMake)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCoreMake diagnostics

#ifdef _DEBUG
void CIPCoreMake::AssertValid() const
{
	CDocument::AssertValid();
}

void CIPCoreMake::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIPCoreMake serialization

void CIPCoreMake::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CIPCoreMake commands

BOOL CIPCoreMake::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	CString str;
	FILE * fp = fopen(lpszPathName,"rt");
	if(fp == NULL)
	{
		str.Format("读文件\"%s\"错误",lpszPathName);
		MessageBox(NULL,str,NULL,NULL);
		return FALSE;
	}
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->UpdateProjectName(lpszPathName);
	char buffer[200];
	while(fgets(buffer,200,fp))
	{
		char *pCh = buffer;
		while(*pCh != 0 && *pCh != '\n') pCh++;
		str = buffer;
		str.TrimLeft();
		str.TrimRight();
		if(str.IsEmpty()) continue;
		CDocument* pDoc = AfxGetApp()->OpenDocumentFile(str);
		if(pDoc == NULL)
		{
			str.Format("读文件\"%s\"错误",buffer);
			MessageBox(NULL,str,NULL,NULL);
		}
	}
	return FALSE;
}
