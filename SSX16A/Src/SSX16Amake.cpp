// SSX16Amake.cpp : implementation file
//

#include "stdafx.h"
#include "..\SSX16A.h"
#include "..\include\SSX16Amake.h"
#include "..\include\MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX16AMake

IMPLEMENT_DYNCREATE(CSSX16AMake, CDocument)

CSSX16AMake::CSSX16AMake()
{
}

BOOL CSSX16AMake::OnNewDocument()
{
	return FALSE;
}

CSSX16AMake::~CSSX16AMake()
{
}


BEGIN_MESSAGE_MAP(CSSX16AMake, CDocument)
	//{{AFX_MSG_MAP(CSSX16AMake)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX16AMake diagnostics

#ifdef _DEBUG
void CSSX16AMake::AssertValid() const
{
	CDocument::AssertValid();
}

void CSSX16AMake::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX16AMake serialization

void CSSX16AMake::Serialize(CArchive& ar)
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
// CSSX16AMake commands

BOOL CSSX16AMake::OnOpenDocument(LPCTSTR lpszPathName) 
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
