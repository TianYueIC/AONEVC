// SSX16Bmake.cpp : implementation file
//

#include "stdafx.h"
#include "..\SSX16B.h"
#include "..\include\SSX16Bmake.h"
#include "..\include\MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX16BMake

IMPLEMENT_DYNCREATE(CSSX16BMake, CDocument)

CSSX16BMake::CSSX16BMake()
{
}

BOOL CSSX16BMake::OnNewDocument()
{
	return FALSE;
}

CSSX16BMake::~CSSX16BMake()
{
}


BEGIN_MESSAGE_MAP(CSSX16BMake, CDocument)
	//{{AFX_MSG_MAP(CSSX16BMake)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX16BMake diagnostics

#ifdef _DEBUG
void CSSX16BMake::AssertValid() const
{
	CDocument::AssertValid();
}

void CSSX16BMake::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX16BMake serialization

void CSSX16BMake::Serialize(CArchive& ar)
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
// CSSX16BMake commands

BOOL CSSX16BMake::OnOpenDocument(LPCTSTR lpszPathName) 
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
