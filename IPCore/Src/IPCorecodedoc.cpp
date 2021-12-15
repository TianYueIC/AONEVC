// IPCorecodedoc.cpp : implementation file
//

#include "stdafx.h"
#include "..\IPCore.h"
#include "..\include\IPCorecodedoc.h"

#include "..\..\Library\include\Utility.h"
#include "..\include\MainFrm.h"
/*
#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\IPCoreDoc.h"

#include "..\..\lex\include\Lex.h"
#include "..\..\lex\include\LALR.h"
#include "..\..\dspasm\include\DSPCode.h"
#include "..\..\dspasm\include\AsmLex.h"
#include "..\..\dspasm\include\masmparse.h"
#include "..\..\lex\include\TextSource.h"
//#include "..\..\lex\include\ErrorStack.h"

*/

#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\IPEmulator\Include\VHardware.h"
#include "..\..\IPEmulator\Include\IPCoreEmulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPCoreCodeDoc

IMPLEMENT_DYNCREATE(CIPCoreCodeDoc, CDocument)

CIPCoreCodeDoc::CIPCoreCodeDoc()
{
}

BOOL CIPCoreCodeDoc::OnNewDocument()
{
	return FALSE;
}

CIPCoreCodeDoc::~CIPCoreCodeDoc()
{
}


BEGIN_MESSAGE_MAP(CIPCoreCodeDoc, CDocument)
	//{{AFX_MSG_MAP(CIPCoreCodeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCoreCodeDoc diagnostics

#ifdef _DEBUG
void CIPCoreCodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIPCoreCodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIPCoreCodeDoc serialization

void CIPCoreCodeDoc::Serialize(CArchive& ar)
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
// CIPCoreCodeDoc commands

BOOL CIPCoreCodeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
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
		str.Format("���ļ�\"%s\"����",str);
		MessageBox(NULL,str,NULL,NULL);
		return FALSE;
	}
	if(fpdbg == NULL)
	{
		fclose(fpbin);
		str.Format("���ļ�\"%s\"����",debugFile);
		MessageBox(NULL,str,NULL,NULL);
		return FALSE;
	}

	g_pIPCoreEmulator->LoadFile(fpbin,fpdbg);
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

	g_pIPCoreEmulator->SetProjectName(str);
	g_pIPCoreEmulator->Reset();
	return FALSE;
}
