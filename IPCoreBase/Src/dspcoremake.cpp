// dspcoremake.cpp : implementation file
//

#include "stdafx.h"
#include "..\DSPCore.h"
#include "..\include\dspcoremake.h"
#include "..\include\MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreMake

IMPLEMENT_DYNCREATE(CDSPCoreMake, CDocument)

CDSPCoreMake::CDSPCoreMake()
{
}

BOOL CDSPCoreMake::OnNewDocument()
{
	return FALSE;
}

CDSPCoreMake::~CDSPCoreMake()
{
}


BEGIN_MESSAGE_MAP(CDSPCoreMake, CDocument)
	//{{AFX_MSG_MAP(CDSPCoreMake)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreMake diagnostics

#ifdef _DEBUG
void CDSPCoreMake::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSPCoreMake::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreMake serialization

void CDSPCoreMake::Serialize(CArchive& ar)
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
// CDSPCoreMake commands

BOOL CDSPCoreMake::OnOpenDocument(LPCTSTR lpszPathName) 
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
