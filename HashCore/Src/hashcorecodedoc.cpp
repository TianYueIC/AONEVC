// hashcorecodedoc.cpp : implementation file
//

#include "stdafx.h"
#include "..\HashCore.h"
#include "..\include\hashcorecodedoc.h"

#include "..\..\Library\include\Utility.h"
#include "..\include\MainFrm.h"

#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\HashcoreEmulate\Include\HashcoreEmulate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHashCoreCodeDoc

IMPLEMENT_DYNCREATE(CHashCoreCodeDoc, CDocument)

CHashCoreCodeDoc::CHashCoreCodeDoc()
{
}

BOOL CHashCoreCodeDoc::OnNewDocument()
{
	return FALSE;
}

CHashCoreCodeDoc::~CHashCoreCodeDoc()
{
}


BEGIN_MESSAGE_MAP(CHashCoreCodeDoc, CDocument)
	//{{AFX_MSG_MAP(CHashCoreCodeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHashCoreCodeDoc diagnostics

#ifdef _DEBUG
void CHashCoreCodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHashCoreCodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHashCoreCodeDoc serialization

void CHashCoreCodeDoc::Serialize(CArchive& ar)
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
// CHashCoreCodeDoc commands

BOOL CHashCoreCodeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	CString str,debugFile;
	str = lpszPathName;
	GetFileNamePrefix(debugFile,str);
	debugFile += ".dbg";
	FILE * fpbin = fopen(str,"rb");
	FILE * fpdbg = fopen(debugFile,"rb");
	if(fpbin == NULL)
	{
		str.Format("读文件\"%s\"错误",str);
		MessageBox(NULL,str,NULL,NULL);
		return FALSE;
	}
	if(fpdbg == NULL)
	{
		fclose(fpbin);
		str.Format("读文件\"%s\"错误",debugFile);
		MessageBox(NULL,str,NULL,NULL);
		return FALSE;
	}

	g_pHashEmulator->LoadFile(fpbin,fpdbg);
	fclose(fpbin);
	fclose(fpdbg);
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->OpenAllFiles();
	Sleep(100);
	pMainFrame->UpdateProjectName(lpszPathName);
	pMainFrame->UpdateTitle();

	str = pMainFrame->m_strPathName;
	str +='\\';
	str +=pMainFrame->m_strProjectName;
	g_pHashEmulator->SetProjectName(str);
	g_pHashEmulator->Reset();
	return FALSE;
}
